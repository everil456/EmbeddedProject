/*
 * sl.c
 *
 *  Created on: Apr 13, 2015
 *      Author: matthew
 */

#include "sl.h"
#include "em_usart.h"
#include "em_gpio.h"
#include "em_device.h"
#include "em_cmu.h"





void I2S_Setup(void)
{
  USART_InitI2s_TypeDef init = USART_INITI2S_SL;

  CMU_ClockEnable(cmuClock_USART0, true);

  /* Use location 1: TX  - Pin D0, (RX - Pin D1) */
  /*                 CLK - Pin D2, CS - Pin D3   */

  GPIO_PinModeSet(gpioPortE, 13, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 12, gpioModeInput, 0);
  GPIO_PinModeSet(gpioPortC, 14, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortC, 15, gpioModePushPull, 0);

  /* Configure USART for basic I2S operation */
  init.sync.baudrate = 10000*64;//wavHeader.frequency * 32;

  USART_InitI2s(USART0, &init);

  /* Enable pins at location 1 */
  USART0->ROUTE = USART_ROUTE_TXPEN |
                  USART_ROUTE_CSPEN |
                  USART_ROUTE_CLKPEN |
                  USART_ROUTE_LOCATION_LOC1;
}

uint8_t I2C_ReadByte(void) {
  while(! (USART0->STATUS & (1 << 7)) ); // wait for valid RX data
  return(USART0->RXDATA);                // clear RX buffer
}

void I2S_WriteByte(uint8_t byte) {
  while( !(USART0->STATUS & (1 << 6)) ); // wait for tx buffer to empty
  USART0->TXDATA = byte;


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


  //initialize the clocks for the peripherals// transmit data byte
}
