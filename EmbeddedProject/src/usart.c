/**************************************************************************//**
 * @file usart.c
 * @brief USART code for the EFM32 bootloader
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

//This file has been modified to support both USARTs and LEUARTs
//Use config.h to pick the USARTs and/or LEUARTs to use.

#include "em_device.h"
#include "usart.h"
#include "config.h"

/***************************************************************************//**
 * @brief
 *   Prints an int in hex.
 *
 * @param integer
 *   The integer to be printed.
 ******************************************************************************/
void USART_printHex(uint8_t uartID, uint32_t integer)
{
  uint8_t c;
  int i, digit;

  for (i = 0; i <= 7; i++)
  {
    digit = integer >> 28;
    c = digit + 0x30;
    if (digit >= 10)
    {
      c += 7;
    }
    USART_txByte(uartID, c);
    integer <<= 4;
  }
}

/**************************************************************************//**
 * @brief Transmit single byte to BOOTLOADER_USART
 *****************************************************************************/
uint8_t USART_rxByte(uint8_t uartID)
{
  uint32_t timer = 100000;
  if(uartID == BOOTLOADER_USART_A_ID)
  {  
    while (!(BOOTLOADER_USART_A->STATUS & BOOTLOADER_USART_A_STATUS_RXDATAV) && --timer) ;
    if (timer > 0 && (BOOTLOADER_USART_A->STATUS & BOOTLOADER_USART_A_STATUS_RXDATAV))
    {
      return((uint8_t)(BOOTLOADER_USART_A->RXDATA & 0xFF));
    }
  }
#ifdef BOOTLOADER_USART_B_ID 
  else
  {
    while (!(BOOTLOADER_USART_B->STATUS & BOOTLOADER_USART_B_STATUS_RXDATAV) && --timer) ;
    if (timer > 0 && (BOOTLOADER_USART_B->STATUS & BOOTLOADER_USART_B_STATUS_RXDATAV))
    {
      return((uint8_t)(BOOTLOADER_USART_B->RXDATA & 0xFF));
    }
  }
#endif
  
  return 0;  
}


/**************************************************************************//**
 * @brief Transmit single byte to BOOTLOADER_USART
 *****************************************************************************/
void USART_txByte(uint8_t uartID, uint8_t data)
{
  //based on the uartID select the USART to transmit using
  if(uartID == BOOTLOADER_USART_A_ID)
  {
    /* Check that transmit buffer is empty */
    while (!(BOOTLOADER_USART_A->STATUS & BOOTLOADER_USART_A_STATUS_TXBL));
    BOOTLOADER_USART_A->TXDATA = (uint32_t) data;
  }
#ifdef BOOTLOADER_USART_B_ID 
  else
  {
    /* Check that transmit buffer is empty */
    while (!(BOOTLOADER_USART_B->STATUS & BOOTLOADER_USART_B_STATUS_TXBL));
    BOOTLOADER_USART_B->TXDATA = (uint32_t) data;
  }
#endif
}

/**************************************************************************//**
 * @brief Transmit null-terminated string to BOOTLOADER_USART
 *****************************************************************************/
void USART_printString(uint8_t uartID, const uint8_t *string)
{
  while (*string != 0)
  {
    USART_txByte(uartID, *string++);
  }
}

/**************************************************************************//**
 * @brief Intializes BOOTLOADER_USART
 *
 * @param clkdiv
 *   The clock divisor to use.
 *****************************************************************************/
void USART_init()
{
  /* Configure BOOTLOADER_USART_A */
  /* USART default to 1 stop bit, no parity, 8 data bits, so not
   * explicitly set */

  /* Set the clock division */
  BOOTLOADER_USART_A->CLKDIV = BOOTLOADER_USART_A_CLKDIV;


  /* Enable RX and TX pins and set location 0 */
  BOOTLOADER_USART_A->ROUTE = BOOTLOADER_USART_A_LOCATION |
                 BOOTLOADER_USART_A_ROUTE;

  /* Clear RX/TX buffers */
#if (BOOTLOADER_USART_A_TYPE != LEUART)
  BOOTLOADER_USART_A->CMD = BOOTLOADER_USART_A_CLEAR;
#endif
  
  /* Enable RX/TX */
  BOOTLOADER_USART_A->CMD = BOOTLOADER_USART_A_ENABLE;
#ifdef BOOTLOADER_USART_B_ID  
  /* Configure BOOTLOADER_USART_B */
  /* USART default to 1 stop bit, no parity, 8 data bits, so not
   * explicitly set */

  /* Set the clock division */
  BOOTLOADER_USART_B->CLKDIV = BOOTLOADER_USART_B_CLKDIV;


  /* Enable RX and TX pins and set location 0 */
  BOOTLOADER_USART_B->ROUTE = BOOTLOADER_USART_B_LOCATION |
                 BOOTLOADER_USART_B_ROUTE;

  /* Clear RX/TX buffers */
  
#if (BOOTLOADER_USART_B_TYPE != LEUART)
  BOOTLOADER_USART_B->CMD = BOOTLOADER_USART_B_CLEAR;
#endif
  /* Enable RX/TX */
  BOOTLOADER_USART_B->CMD = BOOTLOADER_USART_B_ENABLE;
#endif
}
