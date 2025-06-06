/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


//global shared variable between main code and ISR
uint8_t volatile g_button_pressed = 0;

uint32_t g_button_press_count =0;

void button_init(void);

//EXTI: External interrupt Pending register (EXTI_PR)
uint32_t volatile *pEXTTIPendReg			= (uint32_t*) (0x40013C00 + 0x14);
//RCC AHB1 peripheral clock register (RCC_AHB1ENR) (for GPIOA I think)
uint32_t volatile *pClkCtrlReg				= (uint32_t*) (0x40023800 + 0x30);
//RCC APB2 peripheral clock enable register (RCC_APB2ENR), for EXTI (it is on bus APB2)
uint32_t volatile *pClkCtrlRegApb2			= (uint32_t*) (0x40023800 + 0x44);
//The wake-up button is connected through PA0, hence GPIOA mode register (same for all GPIOs)
uint32_t volatile *pGPIOAModeReg 			= (uint32_t*) (0x40020000 + 0x00);
//EXTI Interrupt Mask Register
uint32_t volatile *pEXTIMaskReg 			= (uint32_t*) (0x40013C00 + 0x00);
//EXTI Rising trigger selection register (EXTI_RTSR)
uint32_t volatile *pEXTTIEdgeCtrlReg		= (uint32_t*) (0x40013C00 + 0x08);
//Need to find what this is????
uint32_t volatile *pNVICIRQEnReg 			= (uint32_t*) 0xE000E100;


int main(void)
{
	button_init();

	while(1)
	{
		//Disable interrupt (bit 0 is kept 0, MR0 = 0)
		*pEXTIMaskReg &= ~( 1 << 0);

		if(g_button_pressed){
			//Some delay until button debouncing gets over
			for(uint32_t volatile i=0;i<500000/2;i++);
			g_button_press_count++;
			printf("Button is pressed : %lu\n",g_button_press_count);
			g_button_pressed = 0;
		}

		//Enable interrupt (MR0 = 1)
		*pEXTIMaskReg |= ( 1 << 0);
	}


}


void button_init(void)
{
  //GPIOA enable (bit 0 = 1)
  *pClkCtrlReg |= ( 1 << 0);
  //System configuration controller clock enable
  *pClkCtrlRegApb2 |= ( 1 << 14);
  //Rising trigger enabled (for Event and Interrupt) for input line 0
  *pEXTTIEdgeCtrlReg |= ( 1 << 0);
  //Interrupt request from line 0 is not masked
  *pEXTIMaskReg |= ( 1 << 0);
  //No idea
  *pNVICIRQEnReg |= ( 1 << 6);

}

/* This is button interrupt handler*/
void EXTI0_IRQHandler(void)
{
	//Make this flag SET . if button pressed
  g_button_pressed = 1;

  *pEXTTIPendReg |= ( 1 << 0);
}


