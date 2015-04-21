/**************************************************************************//**
 * @file
 * @brief Empty Project
 * @author Energy Micro AS
 * @version 3.20.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs Software License Agreement. See 
 * "http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt"  
 * for details. Before using this software for any purpose, you must agree to the 
 * terms of that agreement.
 *
 ******************************************************************************/
#include "em_device.h"
#include "em_system.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "config.h"
#include "usart.h"
#include "sl.h"


#define COM_PORT 2 // PORTC
#define TX_PIN   0
#define RX_PIN   1

int main () {

  CHIP_Init();

  uint8_t i;
  const char test_string[] = "\n\rHello World!\n\r";
  char rx_char = 0;

  //Setup the internal RC oscillator to 28MHz
  initClocks();

  /* Setup pins for USART */
  CONFIG_UsartsGpioSetup();

  /* Initialize the UARTs to 115200 */
  USART_init();
  /* I2S initialize */
  I2S_Setup();

  /* Initialize LED driver */
  unsigned int out = 0;
  GPIO_PinModeSet(1,11,_GPIO_P_MODEL_MODE0_PUSHPULL,out);

//  CMU_TypeDef *cmu = CMU;
//
//	/* Turning on HFXO to increase frequency accuracy. */
//	/* Waiting until oscillator is stable */
//	CMU->OSCENCMD |= CMU_OSCENCMD_HFXOEN;
//
//	while (!(cmu->STATUS && CMU_STATUS_HFXORDY)) ;
//
//	/* Switching the CPU clock source to HFXO */
//	CMU->CMD = CMU_CMD_HFCLKSEL_HFXO;
//
//	/* Turning off the high frequency RC Oscillator (HFRCO) */
//	/* GENERATL WARNING! Make sure not to disable the current
//	 * source of the HFCLK. */
//	CMU->OSCENCMD = CMU_OSCENCMD_HFRCODIS;

//
//  CMU->OSCENCMD |= 0x4;                          // enable XTAL oscillator
//  while(!(CMU->STATUS & 0x8));                   // wait for XTAL osc to stabilize
//  CMU->CMD = 0x2;                                // select HF XTAL osc as system clock source (24MHz)

//  CMU->HFPERCLKEN0 = (1 << 7) | (1 << 3);        // enable GPIO and USART1 peripheral clocks
//
//  /* Enable LE and DMA interface */
//  CMU->HFCORECLKEN0 = CMU_HFCORECLKEN0_LE | CMU_HFCORECLKEN0_DMA;
//
//  /* Enable LFRCO for RTC */
//  CMU->OSCENCMD = CMU_OSCENCMD_LFRCOEN;
//  /* Setup LFA to use LFRCRO */
//  CMU->LFCLKSEL = CMU_LFCLKSEL_LFA_LFRCO | CMU_LFCLKSEL_LFB_HFCORECLKLEDIV2;
//
//  /* Enable RTC */
//  CMU->LFACLKEN0 = CMU_LFACLKEN0_RTC;
//
//
//  USART1->CLKDIV = (48 << 6);                                // 115200 baud
//  USART1->CMD = (1 << 11) | (1 << 10) | (1 << 2) | (1 << 0); // clear buffers, enable transmitter and receiver
//  USART1->IFC = 0x1FF9;                                      // clear all USART interrupt flags
//  USART1->ROUTE = 0x3;                                       // enable RX/TX pins









  for(i=0; i<sizeof(test_string); i++) {
    while(!(USART1->STATUS & (1 << 6))); // wait for TX buffer to empty
    USART1->TXDATA = test_string[i];     // send character
  }
  uint8_t I2SData[8];
  while(1) {

	CollectI2S(I2SData);

    if(USART1->STATUS & (1 << 7)) {      // if RX buffer contains valid data
      rx_char = USART1->RXDATA;          // store the data
    }
    if(rx_char) {                        // if we have a valid character
      if(USART1->STATUS & (1 << 6)) {    // check if TX buffer is empty
        USART1->TXDATA = rx_char;        // echo received character
        rx_char = 0;                     // reset temp variable
    	out = !out;
    	GPIO_PinModeSet(1,11,_GPIO_P_MODEL_MODE0_PUSHPULL,out);
      }
    }
  }
}


void initClocks(void)
{
  uint32_t tuning;
    /* Enable clocks for peripherals. */
  CMU->HFPERCLKDIV = CMU_HFPERCLKDIV_HFPERCLKEN;
  CMU->HFPERCLKEN0 = CMU_HFPERCLKEN0_GPIO | BOOTLOADER_USART_A_HFCLOCK;
#ifdef BOOTLOADER_USART_B_ID
  CMU->HFPERCLKEN0 |= BOOTLOADER_USART_B_HFCLOCK;
#endif


  /* Enable LE and DMA interface */
  CMU->HFCORECLKEN0 = CMU_HFCORECLKEN0_LE | CMU_HFCORECLKEN0_DMA;

  /* Enable LFRCO for RTC */
  CMU->OSCENCMD = CMU_OSCENCMD_LFRCOEN;
  /* Setup LFA to use LFRCRO */
  CMU->LFCLKSEL = CMU_LFCLKSEL_LFA_LFRCO | CMU_LFCLKSEL_LFB_HFCORECLKLEDIV2;

  /* Enable RTC */
  CMU->LFACLKEN0 = CMU_LFACLKEN0_RTC;

  /* Figure out correct flash page size */
//  FLASH_CalcPageSize();

  /* Enable LEUART */
  CMU->LFBCLKEN0 = BOOTLOADER_USART_A_LFCLOCK;
#ifdef BOOTLOADER_USART_B_ID
  CMU->LFBCLKEN0 |= BOOTLOADER_USART_B_LFCLOCK;
#endif


#if defined(_EFM32_ZERO_FAMILY)
  /* Change to 21MHz internal osciallator to increase speed of
   * bootloader */
  tuning = ((DEVINFO->HFRCOCAL1 & _DEVINFO_HFRCOCAL1_BAND21_MASK)
           >> _DEVINFO_HFRCOCAL1_BAND21_SHIFT);

  CMU->HFRCOCTRL = CMU_HFRCOCTRL_BAND_21MHZ | tuning;
#else
  /* Change to 28MHz internal osciallator to increase speed of
   * bootloader */
  tuning = (DEVINFO->HFRCOCAL1 & _DEVINFO_HFRCOCAL1_BAND28_MASK)
           >> _DEVINFO_HFRCOCAL1_BAND28_SHIFT;

  CMU->HFRCOCTRL = CMU_HFRCOCTRL_BAND_28MHZ | tuning;
#endif
}

void CollectI2S(uint8_t *data)
  {

	  //set WS
	  WS_pin_set();
	  //Read 32 bits
	  I2S_WriteByte(0xFF);
	  data[0] = I2C_ReadByte();
	  I2S_WriteByte(0xFF);
	  data[1] = I2C_ReadByte();
	  I2S_WriteByte(0xFF);
	  data[2] = I2C_ReadByte();
	  I2S_WriteByte(0xFF);
	  data[3] = I2C_ReadByte();
	  //clr WS
	  WS_pin_clr();
	  //Read 32 bits
	  I2S_WriteByte(0xFF);
	  data[4] = I2C_ReadByte();
	  I2S_WriteByte(0xFF);
	  data[5] = I2C_ReadByte();
	  I2S_WriteByte(0xFF);
	  data[6] = I2C_ReadByte();
	  I2S_WriteByte(0xFF);
	  data[7] = I2C_ReadByte();

  }

// This function drives the CS pin low
void WS_pin_clr(void) {
  GPIO->P[gpioPortC].DOUTCLR = (1 << 14);
}

// This function drives the CS pin high
void WS_pin_set(void) {
  GPIO->P[gpioPortC].DOUTSET = (1 << 14);
}


