/*
 * CommProtocol.c
 *
 *  Created on: Apr 19, 2015
 *      Author: matthew
 */

#include "CommProtocol.h"
#include "em_usart.h"
#include "em_gpio.h"
#include "em_device.h"
#include "em_cmu.h"
#include "CommProtocol.h"

//AddressOrCommandFlag: this is to know if the data being recieved is an address or command, if it is 0 the next data is address
//if 1 the next data is a command. The flag will be change to address or command everytime it recieves data.
uint8_t AddressOrCommandFlag = 0;
int Command;
int Address;
void DoCommand()
{
	switch(Command)
	{
		//Mode 0: 0x00

		//Mode 1: 0x01

		//Mode 2: 0x02

		//Mode 3: 0x03

		//Mode 4: 0x04

		//Mode 5: 0x05

		//Mode 6: 0x06

		//Mode 7: 0x07

		//Mode 8: 0x08

		//Mode 9: 0x09

		//Mode 10: 0x10

		//Mode 11: 0x11

		//Mode 12: 0x12

		//Mode 13: 0x13

		//Mode 14: 0x14

		//Mode 15: 0x15

		//Status: 0x16

		//Start Capture: 0x17

		//Stop Capture: 0x18

		//Capture Length: 0x19

		//Send Data: 0x20

		//Readdress 1: 0x21
		case 21:
			Address = 1;
			break;

		//Readdress 2: 0x22
		case 22:
			Address = 2;
			break;

		//Readdress 3: 0x23
		case 23:
			Address = 3;
			break;

		//Readdress 4: 0x24
		case 24:
		 Address = 4;
		 break;


		//Readdress 5: 0x25
		case 25:
			Address = 5;
			break;


		//Readdress 6: 0x26
		case 26:
			Address = 6;
			break;


		//Readdress 7: 0x27
		case 27:
			Address = 7;
			break;


		//Readdress 8: 0x28
		case 28:
		Address = 8;
		break;


		//Is there another board: 0x29
	}

}

