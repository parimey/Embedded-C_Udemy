/*
 * main.c
 *
 *  Created on: Apr 20, 2025
 *      Author: parimeydpatil
 */


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//This consumes 10 bytes of data instead of 4 bytes which is the size of the packet
//Structure bit fields

struct packet
{
	uint8_t  addr_mode;
	uint8_t  short_addr;
	uint8_t  long_addr;
	uint8_t  sensor;
	uint8_t  bat;
	uint16_t  payload;
	uint8_t  status;
	uint8_t  crc;
};

//Use bit fields
//Order of the definition do not matter

struct packetBitField
{
	uint32_t crc			:2;
	uint32_t status			:1;
	uint32_t payload		:12;
	uint32_t bat			:3;
	uint32_t sensor			:3;
	uint32_t long_addr		:8;
	uint32_t short_addr		:2;
	uint32_t addr_mode		:1;
};

int main()
{
	uint32_t packetValue;

	printf("Enter the 32 bit packet value: ");
	scanf("%X",&packetValue);

	struct packet packet;
	struct packetBitField packetBitField;

	packet.crc = (uint8_t) (packetValue & 0x3);
	packet.status = (uint8_t) ((packetValue >> 2) & 0x1);
	packet.payload = (uint16_t) ((packetValue >> 3) & 0b111111111111) ;
	packet.bat = (uint8_t) ((packetValue >> 15) & 0b111);
	packet.sensor = (uint8_t) ((packetValue >> 18) & 0b111);
	packet.long_addr = (uint8_t) ((packetValue >> 21) & 0xFF);
	packet.short_addr = (uint8_t) ((packetValue >> 29) & 0b11);
	packet.addr_mode = (uint8_t) ((packetValue >> 31) & 1);

	printf("addr_mode:	%#x\n",packet.addr_mode);
	printf("short_addr:	%#x\n",packet.short_addr);
	printf("long_addr:	%#x\n",packet.long_addr);
	printf("sensor:		%#x\n",packet.sensor);
	printf("bat:		%#x\n",packet.bat);
	printf("payload:	%#x\n",packet.payload);
	printf("status: 	%#x\n",packet.status);
	printf("crc: 		%#x\n",packet.crc);

	packetBitField.crc = (uint8_t) (packetValue & 0x3);
	packetBitField.status = (uint8_t) ((packetValue >> 2) & 0x1);
	packetBitField.payload = (uint16_t) ((packetValue >> 3) & 0b111111111111) ;
	packetBitField.bat = (uint8_t) ((packetValue >> 15) & 0b111);
	packetBitField.sensor = (uint8_t) ((packetValue >> 18) & 0b111);
	packetBitField.long_addr = (uint8_t) ((packetValue >> 21) & 0xFF);
	packetBitField.short_addr = (uint8_t) ((packetValue >> 29) & 0b11);
	packetBitField.addr_mode = (uint8_t) ((packetValue >> 31) & 1);

	printf("addr_mode:	%#x\n",packetBitField.addr_mode);
	printf("short_addr:	%#x\n",packetBitField.short_addr);
	printf("long_addr:	%#x\n",packetBitField.long_addr);
	printf("sensor:		%#x\n",packetBitField.sensor);
	printf("bat:		%#x\n",packetBitField.bat);
	printf("payload:	%#x\n",packetBitField.payload);
	printf("status: 	%#x\n",packetBitField.status);
	printf("crc: 		%#x\n",packetBitField.crc);

	printf("Size of struct packet %lu\n",sizeof(packet));
	printf("Size of struct packetBitField %lu\n",sizeof(packetBitField));


	return 0;
}
