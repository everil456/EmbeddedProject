/**************************************************************************//**
 * @file config.h
 * @brief Bootloader Configuration.
 *    This file defines how the bootloader is set up.
 *    This configuration file describes the TG210 parts and larger. (Eg. USART1)
 *    is available.
 * @author Silicon Labs
 * @version 1.68
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Labs has no
 * obligation to support this Software. Silicon Labs is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Silicon Labs will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

//#define ORIGINAL_BOOTLOADER

//UART types
#define LEUART 0
#define USART 1
   
#include "em_device.h"

/** Frequency of the LF clock */
#define LFRCO_FREQ           (32768)

/** Number of milliseconds between each consecutive polling of the SWD pins */
#define USART_LOOP_INTERVAL   20

/** The size of the bootloader flash image */
#define BOOTLOADER_SIZE      0xC00

/** USART Port A used for communication. */
#define BOOTLOADER_USART_A_ID 0
   
#define BOOTLOADER_USART_A           USART1
#define BOOTLOADER_USART_A_TYPE      USART
#define BOOTLOADER_USART_A_HFCLOCK     CMU_HFPERCLKEN0_USART1
#define BOOTLOADER_USART_A_LFCLOCK     0
#define BOOTLOADER_USART_A_LOCATION  USART_ROUTE_LOCATION_LOC0

#define BOOTLOADER_USART_A_PORT_TX 2
#define BOOTLOADER_USART_A_PIN_TX 0
#define BOOTLOADER_USART_A_PORT_RX 2
#define BOOTLOADER_USART_A_PIN_RX 1
#define BOOTLOADER_USART_A_TX_MODE GPIO_P_MODEL_MODE0_WIREDANDPULLUP
#define BOOTLOADER_USART_A_RX_MODE GPIO_P_MODEL_MODE1_WIREDANDPULLUP
#define BOOTLOADER_USART_A_MODE MODEL

//USART CLKDIV for 115200
//28MHZ 3634 | 21MHZ 2661 | 14MHZ 1688
#define BOOTLOADER_USART_A_CLKDIV 3634
#define BOOTLOADER_USART_A_STATUS_RXDATAV USART_STATUS_RXDATAV
#define BOOTLOADER_USART_A_STATUS_TXBL USART_STATUS_TXBL
#define BOOTLOADER_USART_A_ROUTE USART_ROUTE_RXPEN | USART_ROUTE_TXPEN
#define BOOTLOADER_USART_A_CLEAR USART_CMD_CLEARRX | USART_CMD_CLEARTX
#define BOOTLOADER_USART_A_ENABLE USART_CMD_RXEN | USART_CMD_TXEN

/** USART Port B used for communication. */
#define BOOTLOADER_USART_B_ID 1

#define BOOTLOADER_USART_B           LEUART0
#define BOOTLOADER_USART_B_TYPE      LEUART
#define BOOTLOADER_USART_B_HFCLOCK     0
#define BOOTLOADER_USART_B_LFCLOCK     CMU_LFBCLKEN0_LEUART0
#define BOOTLOADER_USART_B_LOCATION  USART_ROUTE_LOCATION_LOC1

#define BOOTLOADER_USART_B_PORT_TX 1
#define BOOTLOADER_USART_B_PIN_TX 13
#define BOOTLOADER_USART_B_PORT_RX 1
#define BOOTLOADER_USART_B_PIN_RX 14
#define BOOTLOADER_USART_B_TX_MODE GPIO_P_MODEH_MODE13_WIREDANDPULLUP
#define BOOTLOADER_USART_B_RX_MODE GPIO_P_MODEH_MODE14_WIREDANDPULLUP
#define BOOTLOADER_USART_B_MODE MODEH

//LEUART CLKDIV for 115200
//28 MHZ 0x77C0 | 14MHZ 0x3be0
#define BOOTLOADER_USART_B_CLKDIV 0x77C0
#define BOOTLOADER_USART_B_STATUS_RXDATAV LEUART_STATUS_RXDATAV
#define BOOTLOADER_USART_B_STATUS_TXBL LEUART_STATUS_TXBL
#define BOOTLOADER_USART_B_ROUTE LEUART_ROUTE_RXPEN | LEUART_ROUTE_TXPEN
#define BOOTLOADER_USART_B_CLEAR LEUART_CMD_CLEARRX | LEUART_CMD_CLEARTX
#define BOOTLOADER_USART_B_ENABLE LEUART_CMD_RXEN | LEUART_CMD_TXEN

/** USART used for debugging. */
#define DEBUG_USART                USART1
#define DEBUG_USART_CLOCK          CMU_HFPERCLKEN0_USART1
#define DEBUG_USART_LOCATION       USART_ROUTE_LOCATION_LOC0



/** This function sets up the GPIO setting for the debug output. */
static __INLINE void CONFIG_DebugGpioSetup(void)
{
  /* Avoid false start by setting output as high */
  GPIO->P[2].DOUT  = (1 << 0);
  GPIO->P[2].MODEL = GPIO_P_MODEL_MODE0_PUSHPULL | GPIO_P_MODEL_MODE1_INPUT;
}

/** This function sets up GPIO for the USARTs used in the bootloader. */
static __INLINE void CONFIG_UsartsGpioSetup(void)
{
  /* Setup UART port A on the chip
   * To avoid false start, configure output as high
   */
  GPIO->P[BOOTLOADER_USART_A_PORT_TX].DOUT = (1 << BOOTLOADER_USART_A_PIN_TX);
  GPIO->P[BOOTLOADER_USART_A_PORT_TX].BOOTLOADER_USART_A_MODE = BOOTLOADER_USART_A_TX_MODE | BOOTLOADER_USART_A_RX_MODE;
  
  /* Setup UART port B on the chip
   * To avoid false start, configure output as high
   */
  GPIO->P[BOOTLOADER_USART_B_PORT_TX].DOUT = (1 << BOOTLOADER_USART_B_PIN_TX);
  GPIO->P[BOOTLOADER_USART_B_PORT_TX].BOOTLOADER_USART_B_MODE = BOOTLOADER_USART_B_TX_MODE | BOOTLOADER_USART_B_RX_MODE;
}



#endif
