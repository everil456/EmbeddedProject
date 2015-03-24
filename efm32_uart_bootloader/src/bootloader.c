/**************************************************************************//**
 * @file bootloader.c
 * @brief EFM32 Bootloader. Preinstalled on all new EFM32 devices
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

#include <stdbool.h>
#include "em_device.h"
#include "usart.h"
#include "xmodem.h"
#include "boot.h"
#include "debuglock.h"
#include "crc.h"
#include "config.h"
#include "flash.h"

#ifndef NDEBUG
#include "debug.h"
#include <stdio.h>
#endif

/** Version string, used when the user connects */
#define BOOTLOADER_VERSION_STRING "0.1.5"

/* Vector table in RAM. We construct a new vector table to conserve space in
 * flash as it is sparsly populated. */
#if defined (__ICCARM__)
#pragma location=0x20000D00
__no_init uint32_t vectorTable[47];
#elif defined (__CC_ARM)
uint32_t vectorTable[47] __attribute__((at(0x20000200)));
#elif defined (__GNUC__)
uint32_t vectorTable[47] __attribute__((aligned(512)));
#else
#error Undefined toolkit, need to define alignment
#endif


/* If this flag is set the bootloader will be boot into the program
 * This is set to false if a space charater is recieved on either UART Port
 * within one second.
 */
volatile bool bootEFM32 = false;

//UARTID for the UART that sends a space charatcter before the RTC timeout
//default to port A
uint8_t mainUARTID = BOOTLOADER_USART_A_ID;

//flashSize is the size of the flash in Bytes
#pragma location=0x2000003C
volatile uint32_t flashSize;

/**************************************************************************//**
 * Strings.
 *****************************************************************************/
const uint8_t crcString[]     = "\r\nCRC: ";
const uint8_t newLineString[] = "\r\n";
const uint8_t readyString[]   = "\r\nReady\r\n";
const uint8_t okString[]      = "\r\nOK\r\n";
const uint8_t failString[]    = "\r\nFail\r\n";
const uint8_t unknownString[] = "\r\n?\r\n";
const uint8_t rebootString[] = "\r\nREBOOTING\r\n";
/**************************************************************************//**
 * @brief RTC IRQ Handler
 *   The RTC is used to keep the power consumption of the bootloader down while
 *   waiting for the pins to settle, or work as a watchdog in the autobaud
 *   sequence.
 *****************************************************************************/
void RTC_IRQHandler(void)
{
  /* Clear interrupt flag */
  RTC->IFC = RTC_IFC_COMP1 | RTC_IFC_COMP0 | RTC_IFC_OF;
  /* Check if EFM should be reset on timeout */
  bootEFM32 = true;
}

/**************************************************************************//**
 * @brief
 *   This function is an infinite loop. It actively waits for one of the
 *   following conditions to be true:
 *   1) The SWDClk Debug pins is not asserted and a valid application is
 *      loaded into flash.
 *      In this case the application is booted.
 *   OR:
 *   2) The SWD Clk pin is asserted and there is an incoming packet
 *      on the USART RX line
 *      In this case we start sensing to measure the baudrate of incoming packets.
 *
 *   If none of these conditions are met, the EFM32G is put to EM2 sleep for
 *   250 ms.
 *****************************************************************************/
static void waitForBootOrUSART(void)
{
#ifndef NDEBUG
  uint32_t oldPins = 0xf;
#endif
  /* Initialize RTC */
  /* Clear interrupt flags */
  RTC->IFC = RTC_IFC_COMP1 | RTC_IFC_COMP0 | RTC_IFC_OF;
  /* 250 ms wakeup time */
  RTC->COMP0 = (USART_LOOP_INTERVAL * LFRCO_FREQ);
  /* Enable Interrupts on COMP0 */
  RTC->IEN = RTC_IEN_COMP0;
  /* Enable RTC interrupts */
  NVIC_EnableIRQ(RTC_IRQn);
  /* Enable RTC */
  RTC->CTRL = RTC_CTRL_COMP0TOP | RTC_CTRL_DEBUGRUN | RTC_CTRL_EN;
  bootEFM32 = 0;
  //loop until either the RTC timeouts or one of the UART ports receives a ' '
  while (1)
  {
    //receive any characters on the UART's
    
    char uartAChar = 0;
    char uartBChar = 0;
    
    if(BOOTLOADER_USART_A->STATUS & BOOTLOADER_USART_A_STATUS_RXDATAV)
       uartAChar = USART_rxByte(0);
#ifdef BOOTLOADER_USART_B_ID 
    if(BOOTLOADER_USART_B->STATUS & BOOTLOADER_USART_B_STATUS_RXDATAV)
       uartBChar = USART_rxByte(1);
#endif
    
    if (uartAChar == ' ' || uartBChar == ' ')
    {
      //disable the RTC interrupt
      NVIC_DisableIRQ(RTC_IRQn);
      
      bootEFM32 = false;
      
      //check to see which port recieved the ' '
#ifdef BOOTLOADER_USART_B_ID 
      if(uartBChar == ' ')
      {
        mainUARTID = BOOTLOADER_USART_B_ID;
      }
#endif
      return;
    }
    
    //RTC interrupt was triggered before a ' ' was recieved so boot the porgram
    if(bootEFM32)
    {
       BOOT_boot();
    }
  }
}
/**************************************************************************//**
 * @brief  Create a new vector table in RAM.
 *         We generate it here to conserve space in flash.
 *****************************************************************************/
static void generateVectorTable(void)
{
  vectorTable[RTC_IRQn + 16]            = (uint32_t) RTC_IRQHandler;
  SCB->VTOR                             = (uint32_t) vectorTable;
}

//initialize the clocks for the peripherals
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
  FLASH_CalcPageSize();
  
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

/**************************************************************************//**
 * @brief
 *   Helper function to print flash write verification using CRC
 * @param start
 *   The start of the block to calculate CRC of.
 * @param end
 *   The end of the block. This byte is not included in the checksum.
 *****************************************************************************/
void verify(uint8_t uartID, uint32_t start, uint32_t end)
{
  USART_printString(uartID, crcString);
  
  /*for(uint32_t *i = (uint32_t *)start; i < (uint32_t *)(end); i++)
  {
    USART_printHex(uartID, *i);
    USART_printString(uartID, "\r\n");
  }*/
  
  USART_printHex(uartID, CRC_calc((void *) start, (void *) end));
  USART_printString(uartID, newLineString);
}

typedef void (*i_func_uc_ui_ui)(uint8_t, uint32_t, uint32_t);

//FIXED functions are setup so that the main application can call them still.
//      This is done by creating a funciton pointer in a small reserved area of the RAM
//      currently 0x20000000-0x20000040
//      Then in the application there are function double pointers that point to these pointers to call these functions.

//Upload Application and reset. Since an upload will override the current application,
//      the processor is reset so there is not undefined behavoir by returning back into different code.
void FIXED_uploadAppAndReset(uint8_t uartID)
{ 
  
  initClocks();
  
  FLASH_init();
  
  //disable intterupts so they don't go off durring the flash write operations.
  SysTick->CTRL  = 0; 
  
  for(IRQn_Type i = DMA_IRQn; i < 32; i++)
  {
    NVIC_DisableIRQ(i);
  }
  
  USART_printString(uartID, readyString);
  
  XMODEM_download(uartID, BOOTLOADER_SIZE, flashSize);

  USART_printString(uartID, rebootString);
  for(volatile int i = 0; i < 100000; i++);
  /* Write to the Application Interrupt/Reset Command Register to reset
   * the EFM32. See section 9.3.7 in the reference manual. */
  SCB->AIRCR = 0x05FA0004;
  //there is nowhere to jump back to if this is called from the application so loop forever in case the reset command is not immediete
  while(0){}
}
#pragma location=0x20000000
void (*FIXED_uploadAppAndReset_ptr)(uint8_t uartID) = FIXED_uploadAppAndReset;

//Destructive Upload
//Currently this does not work. In order to get the regular upload to work from the application, 
// the ram functions had to be moved back to the rom but destructive uploads require code in RAM...
void FIXED_destructiveUploadAndReset(uint8_t uartID)
{
  initClocks();
  
  FLASH_init();
  
  //disable intterupts so they don't go off durring the flash write operations.
  SysTick->CTRL  = 0; 
  
  for(IRQn_Type i = DMA_IRQn; i < 32; i++)
  {
    NVIC_DisableIRQ(i);
  }
  
  {
    volatile char *dst = (char*)0x20000100;
    char *src = (char*)0x00000000;
    for(int i = 0; i < 0x900; i++)
    {
      dst[i] = src[i];
    }
    
    USART_printString(uartID, readyString);
    
    {
      i_func_uc_ui_ui XMODEM_downloadAndReset_ptr = (i_func_uc_ui_ui)((int)XMODEM_downloadAndReset + 0x20000100 - 0x000);
      
      XMODEM_downloadAndReset_ptr(uartID, 0, flashSize);
    }
  }
}
#pragma location=0x20000004
void (*FIXED_destructiveUploadAndReset_ptr)(uint8_t uartID) = FIXED_destructiveUploadAndReset;

//User Page Write
void FIXED_writeUserPageAndReset(uint8_t uartID)
{
  
  initClocks();
  
  FLASH_init();
  
  //disable intterupts so they don't go off durring the flash write operations.
  SysTick->CTRL  = 0; 
  
  for(IRQn_Type i = DMA_IRQn; i <= 31; i++)
  {
    NVIC_DisableIRQ(i);
  }
  
  USART_printString(uartID, readyString);
  XMODEM_download(uartID, XMODEM_USER_PAGE_START, XMODEM_USER_PAGE_END);
  
  USART_printString(uartID, rebootString);
  for(volatile int i = 0; i < 100000; i++);
  /* Write to the Application Interrupt/Reset Command Register to reset
   * the EFM32. See section 9.3.7 in the reference manual. */
  SCB->AIRCR = 0x05FA0004;
  //there is nowhere to jump back to if this is called from the application so loop forever in case the reset command is not immediete
  while(0){}
}
#pragma location=0x20000008
void (*FIXED_writeUserPageAndReset_ptr)(uint8_t uartID) = FIXED_writeUserPageAndReset;

//Debug Lock Write
void FIXED_writeLockPageAndReset(uint8_t uartID)
{
  initClocks();
  
  FLASH_init();
  
  //disable intterupts so they don't go off durring the flash write operations.
  SysTick->CTRL  = 0; 
  
  for(IRQn_Type i = DMA_IRQn; i <= 31; i++)
  {
    NVIC_DisableIRQ(i);
  }
  
#if !defined(_EFM32_ZERO_FAMILY)
  DEBUGLOCK_startDebugInterface();
#endif
  USART_printString(uartID, readyString);
#if defined(USART_OVERLAPS_WITH_BOOTLOADER) && !defined(_EFM32_ZERO_FAMILY)
  /* Since the UART overlaps, the bit-banging in DEBUGLOCK_startDebugInterface()
   * Will generate some traffic. To avoid interpreting this as UART communication,
   * we need to flush the LEUART data buffers. */
  BOOTLOADER_USART->CMD = LEUART_CMD_CLEARRX;
#endif
  XMODEM_download(uartID, XMODEM_LOCK_PAGE_START, XMODEM_LOCK_PAGE_END);
      
  USART_printString(uartID, rebootString);
  for(volatile int i = 0; i < 100000; i++);
  /* Write to the Application Interrupt/Reset Command Register to reset
   * the EFM32. See section 9.3.7 in the reference manual. */
  SCB->AIRCR = 0x05FA0004;
  //there is nowhere to jump back to if this is called from the application so loop forever in case the reset command is not immediete
  while(0){}
}
#pragma location=0x2000000C
void (*FIXED_writeLockPageAndReset_ptr)(uint8_t uartID) = FIXED_writeLockPageAndReset;

//Boot Application
void FIXED_bootApplication()
{
  BOOT_boot();
}
#pragma location=0x20000010
void (*FIXED_bootApplication_ptr)() = FIXED_bootApplication;

//Verify flash checksum
void FIXED_debugLock(uint8_t uartID)
{
  uint8_t *returnString;
#if !defined(NDEBUG) && !defined(_EFM32_ZERO_FAMILY)
  /* We check if there is a debug session active in DHCSR. If there is we
   * abort the locking. This is because we wish to make sure that the debug
   * lock functionality works without a debugger attatched. */
  if ((CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk) != 0x0)
  {
    printf("\r\n\r\n **** WARNING: DEBUG SESSION ACTIVE. NOT LOCKING!  **** \r\n\r\n");
    USART_printString(uartID, "Debug active.\r\n");
  }
  else
  {
    printf("Starting debug lock sequence.\r\n");
#endif
    if (DEBUGLOCK_lock())
    {
      returnString = (uint8_t *)okString;
    }
    else
    {
      returnString = (uint8_t *)failString;
    }
    USART_printString(uartID, returnString);

#if !defined(NDEBUG) && !defined(_EFM32_ZERO_FAMILY)
    printf("Debug lock word: 0x%x \r\n", *((uint32_t *) DEBUG_LOCK_WORD));
  }
#endif
}
#pragma location=0x20000014
void (*FIXED_debugLock_ptr)(uint8_t uartID) = FIXED_debugLock;


//Verify flash checksum
void FIXED_flashChecksum(uint8_t uartID)
{
  verify(uartID, 0, flashSize);
}
#pragma location=0x20000018
void (*FIXED_flashChecksum_ptr)(uint8_t uartID) = FIXED_flashChecksum;

//Verify application checksum
void FIXED_appChecksum(uint8_t uartID)
{
  verify(uartID, BOOTLOADER_SIZE, flashSize);
}
#pragma location=0x2000001C
void (*FIXED_appChecksum_ptr)(uint8_t uartID) = FIXED_appChecksum;

//Verify user page checksum
void FIXED_userPageChecksum(uint8_t uartID)
{
  verify(uartID, XMODEM_USER_PAGE_START, XMODEM_USER_PAGE_END);
}
#pragma location=0x20000020
void (*FIXED_userPageChecksum_ptr)(uint8_t uartID) = FIXED_userPageChecksum;

//Verify lock page checksum
void FIXED_lockPageChecksum(uint8_t uartID)
{
  verify(uartID, XMODEM_LOCK_PAGE_START, XMODEM_LOCK_PAGE_END);
}
#pragma location=0x20000024
void (*FIXED_lockPageChecksum_ptr)(uint8_t uartID) = FIXED_lockPageChecksum;

//Reset the EFM32
void FIXED_reset()
{
  /* Write to the Application Interrupt/Reset Command Register to reset
   * the EFM32. See section 9.3.7 in the reference manual. */
  SCB->AIRCR = 0x05FA0004;
}
#pragma location=0x20000028
void (*FIXED_reset_ptr)() = FIXED_reset;


/**************************************************************************//**
 * @brief
 *   The main command line loop. Placed in Ram so that it can still run after
 *   a destructive write operation.
 *   NOTE: __ramfunc is a IAR specific instruction to put code into RAM.
 *   This allows the bootloader to survive a destructive upload.
 *****************************************************************************/
void commandlineLoop(void)
{
  uint8_t  c;

  /* Find the size of the flash. DEVINFO->MSIZE is the
   * size in KB so left shift by 10. */
  flashSize = ((DEVINFO->MSIZE & _DEVINFO_MSIZE_FLASH_MASK) >> _DEVINFO_MSIZE_FLASH_SHIFT)
              << 10;
  
  /* The main command loop */
  while (1)
  {
    /* Retrieve new character */
    c = USART_rxByte(mainUARTID);
    /* Echo */
    if (c != 0)
    {
      USART_txByte(mainUARTID, c);
    }
    switch (c)
    {
    /* Upload command */
    case 'u':
      USART_printString(mainUARTID, readyString);
      USART_printHex(mainUARTID, BOOTLOADER_SIZE);
      XMODEM_download(mainUARTID, BOOTLOADER_SIZE, flashSize);
      break;
    case 'U':
      //need this to stay through the optimizations so I have to add it to the command loop commands.
      FIXED_uploadAppAndReset_ptr(mainUARTID);
      break;
    case 'd':
      USART_printString(mainUARTID, readyString);
      XMODEM_download(mainUARTID, 0, flashSize);
      break;
    /* Destructive upload command */
    case 'D':
      FIXED_destructiveUploadAndReset_ptr(mainUARTID);
      break;
    /* Write to user page */
    case 't':
      USART_printString(mainUARTID, readyString);
      XMODEM_download(mainUARTID, XMODEM_USER_PAGE_START, XMODEM_USER_PAGE_END);
      break;
    case 'T':
      FIXED_writeUserPageAndReset_ptr(mainUARTID);
      break;
    /* Write to lock bits */
    case 'p':
#if !defined(_EFM32_ZERO_FAMILY)
      DEBUGLOCK_startDebugInterface();
#endif
      USART_printString(mainUARTID, readyString);
#if defined(USART_OVERLAPS_WITH_BOOTLOADER) && !defined(_EFM32_ZERO_FAMILY)
      /* Since the UART overlaps, the bit-banging in DEBUGLOCK_startDebugInterface()
       * Will generate some traffic. To avoid interpreting this as UART communication,
       * we need to flush the LEUART data buffers. */
      BOOTLOADER_USART->CMD = LEUART_CMD_CLEARRX;
#endif
      XMODEM_download(mainUARTID, XMODEM_LOCK_PAGE_START, XMODEM_LOCK_PAGE_END);
      break;
    case 'P':
      FIXED_writeLockPageAndReset_ptr(mainUARTID);
      break;
    /* Boot into new program */
    case 'b':
      FIXED_bootApplication_ptr();
      break;
    /* Debug lock */
    case 'l':
      FIXED_debugLock_ptr(mainUARTID);
      break;
    /* Verify content by calculating CRC of entire flash */
    case 'v':
      FIXED_flashChecksum_ptr(mainUARTID);
      break;
    case 'V':
      verify(mainUARTID, 0, BOOTLOADER_SIZE - 1);
      break;
    /* Verify content by calculating CRC of application area */
    case 'c':
      FIXED_appChecksum_ptr(mainUARTID);
      break;
    /* Verify content by calculating CRC of user page.*/
    case 'n':
      FIXED_userPageChecksum_ptr(mainUARTID);
      break;
    /* Verify content by calculating CRC of lock page */
    case 'm':
      FIXED_lockPageChecksum_ptr(mainUARTID);
      break;
    /* Reset command */
    case 'r':
      FIXED_reset_ptr();
      break;
    /* Unknown command */
    case 0:
      /* Timeout waiting for RX - avoid printing the unknown string. */
      break;
    default:
      USART_printString(mainUARTID, unknownString);
    }
  }
}



/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  /* Handle potential chip errata */
  /* Uncomment the next line to enable chip erratas for engineering samples */
  /* CHIP_init(); */
  
  /* Generate a new vector table and place it in RAM */
  generateVectorTable();
  
  initClocks(); 
  
  /* Setup pins for USART */
  CONFIG_UsartsGpioSetup();
  
  /* Initialize the UARTs to 115200 */
  USART_init();
  
  /* Initialize flash for writing */
  FLASH_init();
 
  waitForBootOrUSART(); 
  
  /* Print a message to show that we are in bootloader mode */
  USART_printString(mainUARTID, "\r\n\r\nClearCore Bootloader V" BOOTLOADER_VERSION_STRING  "\r\nChipID: ");
  /* Print the chip ID. This is useful for production tracking */
  USART_printHex(mainUARTID, DEVINFO->UNIQUEH);
  USART_printHex(mainUARTID, DEVINFO->UNIQUEL);
  USART_printString(mainUARTID, "\r\n");
  
  /* Start executing command line */
  commandlineLoop();
}
