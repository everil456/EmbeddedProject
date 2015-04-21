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
		case 0:
			break;

		//Mode 1: 0x01
		case 1:
			break;

		//Mode 2: 0x02
		case 2:
			break;

		//Mode 3: 0x03
		case 3:
			break;

		//Mode 4: 0x04
		case 4:
			break;

		//Mode 5: 0x05
		case 5:
			break;

		//Mode 6: 0x06
		case 6:
			break;

		//Mode 7: 0x07
		case 7:
			break;

		//Mode 8: 0x08
		case 8:
			break;

		//Mode 9: 0x09
		case 9:
			break;

		//Mode 10: 0x10
		case 10:
			break;

		//Mode 11: 0x11
		case 11:
			break;

		//Mode 12: 0x12
		case 12:
			break;

		//Mode 13: 0x13
		case 13:
			break;

		//Mode 14: 0x14
		case 14:
			break;

		//Mode 15: 0x15
		case 15:
			break;

		//Status: 0x16
		case 16:
			break;

		//Start Capture: 0x17
		case 17:
			break;

		//Stop Capture: 0x18
		case 18:
			break;

		//Capture Length: 0x19
		case 19:
			break;

		//Send Data: 0x20
		case 20:
			break;

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
		case 29:
			break;

		default:
			break;
	}
	// increment the address command for next chip in the line
	if((Command > 20)&(Command < 29))
	{
		Command = Command + 1;
	}

}

