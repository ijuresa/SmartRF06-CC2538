
#ifndef MAIN_H_
#define MAIN_H_
/*******************************************************************************
 *                       INCLUDE FILES
 ******************************************************************************/
#include <stdint.h>

//! Low lvl
#include "hw_memmap.h"
#include "hw_ioc.h"
#include "hw_ints.h"

//! Driver includes
#include "sys_ctrl.h"
#include "gpio.h"
#include "uartstdio.h"
#include "ioc.h"

//! Local includes
#include "aoa_driver.h"
#include "delay.h"
#include "def_app.h"

/*******************************************************************************
 *                       CONSTANTS
 ******************************************************************************/
//! UART defines
#define UART_PIN_RX     GPIO_PIN_0
#define UART_PIN_TX     GPIO_PIN_1

#define GPIO_UART_BASE  GPIO_A_BASE

//! Timer
#define TIMER_0B_CONFIGURATION  GPTIMER_CFG_SPLIT_PAIR      \
                                | GPTIMER_CFG_A_ONE_SHOT    \
                                | GPTIMER_CFG_B_PERIODIC

//! AOA
#define AOA_PORT_NUMBER 1

/*******************************************************************************
 *                       PUBLIC FUNCTION PROTOTYPES
 ******************************************************************************/
void INIT_uart(void);

#endif /* MAIN_H_ */
/*******************************************************************************
 *                       END OF FILE
 ******************************************************************************/
