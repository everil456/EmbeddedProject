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
#include "config.h"
#include "usart.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_cmu.h"

#define I2S_PORTE     gpioPortE // USART1 (location #3) MISO and MOSI are on PORTD
#define I2S_PORTC     gpioPortC // USART1 (location #3) SS and SCLK are on PORTC
#define I2S_PORTD     gpioPortD
#define I2S_PORTB     gpioPortB
#define I2S_MISO_PIN  12 	// PE12
#define I2S_MOSI_PIN  13 	// PE13
#define I2S_WS_PIN    14 	// PC14
#define I2S_SCLK_PIN  15 	// PC15
#define I2S_PWR_PIN    7 	// PD7
#define I2S_LR_PIN     6 	// PD6
#define I2S_EN_PIN     8 	// PB8


#define COM_PORT 2 // PORTC
#define TX_PIN   0
#define RX_PIN   1

#define RX_BUFFER_SIZE 4	// 4 bytes

main () {

  CHIP_Init();

  uint16_t i;
  uint16_t j;
  uint16_t x;

  const char test_string[] = "\n\rSonic Locator!\n\r";
  const char enter[] = "\n\r";
  char rx_char = 0;

  initClocks();

  /* Setup pins for USART */
  CONFIG_UsartsGpioSetup();

  /* Initialize the UARTs to 115200 */
  USART_init();

  /* Initialize I2S   */
  I2S_init();

  /* Initialize LED driver */
  unsigned int out = 0;
  GPIO_PinModeSet(1,11,_GPIO_P_MODEL_MODE0_PUSHPULL,out);


	uint8_t rx_buffer[RX_BUFFER_SIZE];

	// Clear software buffer (optional)
	for(i=0; i<RX_BUFFER_SIZE; i++) {
	rx_buffer[i] = 0;
	}

	/*Set up collection variables */
	uint8_t sample1[4];
	uint8_t sample2[800];

  for(i=0; i<sizeof(test_string); i++) {
    while(!(USART1->STATUS & (1 << 6))); // wait for TX buffer to empty
    USART1->TXDATA = test_string[i];     // send character
  }

  while(1) {

    if(USART1->STATUS & (1 << 7)) {      // if RX buffer contains valid data
      rx_char = USART1->RXDATA;          // store the data
    }

                           // if we have a valid character

      if(rx_char == 'g'){

    	  rx_char = 0;                     // reset temp variable

    	  out = !out;
		  GPIO_PinModeSet(1,11,_GPIO_P_MODEL_MODE0_PUSHPULL,out);

    		for(j=0; j<5; j++){
    			for(i=0; i<200; i+=4){
    				WS_pin_set();
    				sample1[0] = USART_SpiTransfer(USART0, 0xFA);
    				sample1[1] = USART_SpiTransfer(USART0, 0xFA);
    				sample1[2] = USART_SpiTransfer(USART0, 0xFA);
    				sample1[3] = USART_SpiTransfer(USART0, 0xFA);

    				WS_pin_clr();
    				sample2[i] = USART_SpiTransfer(USART0, 0xFA);
    				sample2[i+1] = USART_SpiTransfer(USART0, 0xFA);
    				sample2[i+2] = USART_SpiTransfer(USART0, 0xFA);
    				sample2[i+3] = USART_SpiTransfer(USART0, 0xFA);
    			}
    		}

    		for(i=0; i<800; i++) {
    				while(!(USART1->STATUS & (1 << 6))); // wait for TX buffer to empty
    			    hexTrans(sample2[i]);     // send character
    			  }

//    		for(i=0; i<800; i++) {
//    		    			while(!(USART1->STATUS & (1 << 6))); // wait for TX buffer to empty
//    		    		    USART1->TXDATA = 'x';     // send character
//    		    		  }


//    		for(i=0; i<sizeof(test_string); i++) {
//    			while(!(USART1->STATUS & (1 << 6))); // wait for TX buffer to empty
//    		    USART1->TXDATA = test_string[i];     // send character
//    		  }

      }


      if(rx_char) {
    	  if(USART1->STATUS & (1 << 6)) {    // check if TX buffer is empty
			USART1->TXDATA = rx_char;        // echo received character
			rx_char = 0;                     // reset temp variable

		  }
      }
  }
}


uint8_t nib2hex(uint8_t nib){
	uint8_t hex;

	//Encode hex numbers with ascii characters
	switch(nib){
	default: hex = 42;break;
	case  0: hex = 42;break;
	case  1: hex = 49;break;
	case  2: hex = 50;break;
	case  3: hex = 51;break;
	case  4: hex = 52;break;
	case  5: hex = 53;break;
	case  6: hex = 54;break;
	case  7: hex = 55;break;
	case  8: hex = 56;break;
	case  9: hex = 57;break;
	case 10: hex = 65;break;
	case 11: hex = 66;break;
	case 12: hex = 67;break;
	case 13: hex = 68;break;
	case 14: hex = 69;break;
	case 15: hex = 70;break;
	}

	return hex;
}

void hexTrans(uint8_t num){

	uint8_t numLow = num & 0x0F;
	uint8_t numHigh = num >> 4;

	uint8_t nibbleLow = nib2hex(numLow);
	uint8_t nibbleHigh = nib2hex(numHigh);

//	nibbleHigh = nibbleHigh <<4;

//	uint8_t byte = nibbleHigh & nibbleLow;



	while(!(USART1->STATUS & (1 << 6))); // wait for TX buffer to empty
	USART1->TXDATA = nibbleHigh;

	while(!(USART1->STATUS & (1 << 6))); // wait for TX buffer to empty
	USART1->TXDATA = nibbleLow;


}



void I2S_init(void){
  /* Configure SPI Port (USART0 in sync mode) */
  USART_InitSync_TypeDef spi_init = {
	.enable = usartEnable,        // enable bidirectional data (TX and RX)
	.refFreq = 0,                 // measure source clock
	.baudrate = 8000*64,         // 12Mbps is max data rate with 24MHz clock source
	.databits = usartDatabits8,   // 8 data bits per frame
	.master = true,               // configure as SPI master
	.msbf = true,                 // transmit msb first (requirement of W25X40CL)
	.clockMode = usartClockMode0, // clock idles low, data setup on rising edge, sampled on falling edge
  };

  CMU_ClockEnable(cmuClock_USART0, true);

  /*Initialize Communications Pins*/
  GPIO_PinModeSet(gpioPortE, 13, gpioModePushPull, 0);	//Tx
  GPIO_PinModeSet(gpioPortE, 12, gpioModeInputPull, 0);	//Rx
  GPIO_PinModeSet(gpioPortC, 15, gpioModePushPull, 0); 	//CLK
  GPIO_PinModeSet(gpioPortC, 14, gpioModePushPull, 0);	//CS

  /*Microphone Setup Pins*/
	GPIO_PinModeSet(I2S_PORTD, I2S_PWR_PIN, gpioModePushPull, 1);    // configure PWR pin as output, initialize high
	GPIO_PinModeSet(I2S_PORTD, I2S_LR_PIN, gpioModePushPull, 0);     // configure LR pin as output, initialize low
	GPIO_PinModeSet(I2S_PORTB, I2S_EN_PIN, gpioModePushPull, 1);     // configure EN pin as output, initialize high


  USART_IntClear(USART1, 0x1FF9);                 // clear interrupt flags (optional)
  USART_InitI2s(USART0, &spi_init);

  /* Enable pins at location 1 */
  USART0->ROUTE = USART_ROUTE_TXPEN |
				  USART_ROUTE_RXPEN |
				  USART_ROUTE_CLKPEN |
				  USART_ROUTE_LOCATION_LOC3;

}

// This function drives the CS pin low
void WS_pin_clr(void) {
  GPIO_PinOutClear(I2S_PORTC, I2S_WS_PIN);
//	GPIO_PinModeSet(I2S_PORTC, I2S_WS_PIN, gpioModePushPull, 0);      // configure WS pin as output, initialize high
}

// This function drives the CS pin high
void WS_pin_set(void) {
  GPIO_PinOutSet(I2S_PORTC, I2S_WS_PIN);
//	GPIO_PinModeSet(I2S_PORTC, I2S_WS_PIN, gpioModePushPull, 1);      // configure WS pin as output, initialize high
}


//initialize the clocks for the peripherals
void initClocks(void)
{
  uint32_t tuning;
    /* Enable clocks for peripherals. */
  CMU->HFPERCLKDIV = CMU_HFPERCLKDIV_HFPERCLKEN;
  CMU->HFPERCLKEN0 = CMU_HFPERCLKEN0_GPIO | BOOTLOADER_USART_A_HFCLOCK | CMU_HFPERCLKEN0_USART0;
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
