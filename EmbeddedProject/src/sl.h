/*
 * sl.h
 *
 *  Created on: Apr 13, 2015
 *      Author: matthew
 */

#ifndef SL_H_
#define SL_H_

#include "em_device.h"

#define USART_INITI2S_SL                                                                    \
  {                                                                                              \
    { usartEnableTx,      /* Enable TX when init completed. */                                   \
      0,                  /* Use current configured reference clock for configuring baudrate. */ \
      1000000,            /* Baudrate 1M bits/s. */                                              \
      usartDatabits16,    /* 16 databits. */                                                     \
      true,               /* Operate as I2S master. */                                           \
      true,               /* Most significant bit first. */                                      \
      usartClockMode0,    /* Clock idle low, sample on rising edge. */                           \
      true,              /* Enable USARTRx via PRS. */                                    \
      usartPrsRxCh0,      /* PRS channel selection (dummy). */                                   \
      false               /* Disable AUTOTX mode. */                                             \
    },                                                                                           \
    usartI2sFormatW32D32, /* 32-bit word, 32-bit data */                                         \
    true,                 /* Delay on I2S data. */                                               \
    false,                /* No DMA split. */                                                    \
    usartI2sJustifyLeft,  /* Data is left-justified within the frame */                          \
    false                 /* Stereo mode. */                                                     \
  }

/*
 *
 */
void I2S_Setup(void);

/*
 *
 */
uint8_t I2C_ReadByte(void);

/*
 *
 */
void I2S_WriteByte(uint8_t byte);

/*
 *
 */
void CollectI2S(uint8_t *data);

/*
 *
 */
void WS_pin_clr(void);

/*
 *
 */
void WS_pin_set(void);





#endif /* SL_H_ */
