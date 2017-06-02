

#ifndef UTILITIES_DELAY_H_
#define UTILITIES_DELAY_H_

/*******************************************************************************
 *                       INCLUDE FILES
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

//! Low lvl
#include "hw_ints.h"
#include "hw_memmap.h"

//! Drivers libraries
#include "sys_ctrl.h"
#include "gptimer.h"
#include "interrupt.h"

//! Local
#include "def_app.h"

/*******************************************************************************
 *                       CONSTANTS
 ******************************************************************************/
#define RATE   10u

#if defined USE_ENABLE_TIMER_B
    #define USE_DISABLE_TIMER_A
#elif defined USE_ENABLE_TIMER_A
    #define USE_DISABLE_TIMER_B
#else
    #error "Enable Timer0A or Timer0B in app layer"
#endif // Timers


#if defined USE_ENABLE_TIMER_B
    #define GP_TIMER_TIMEOUT    GPTIMER_TIMB_TIMEOUT
    #define INT_TIMER           INT_TIMER0B
#elif defined USE_ENABLE_TIMER_A
    #define GP_TIMER_TIMEOUT    GPTIMER_TIMB_TIMEOUT
    #define INT_TIMER           INT_TIMER0B
#endif // Timer properties

/*******************************************************************************
 *                       PUBLIC FUNCTION PROTOTYPES
 ******************************************************************************/
void INIT_delay(uint32_t timer, uint32_t timerPeripheral, uint32_t timerBase,
                uint32_t timerConfiguration);

void delay_SysCtrlDelay(uint32_t delay);

#endif /* UTILITIES_DELAY_H_ */

/*******************************************************************************
 *                       END OF FILE
 ******************************************************************************/
