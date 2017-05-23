

#ifndef UTILITIES_DELAY_H_
#define UTILITIES_DELAY_H_

/*******************************************************************************
 *                       INCLUDE FILES
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

//! Drivers libraries
#include "sys_ctrl.h"
#include "gptimer.h"
#include "interrupt.h"

/*******************************************************************************
 *                       CONSTANTS
 ******************************************************************************/
#define TICK_RATE   1000u


/*******************************************************************************
 *                       PUBLIC FUNCTION PROTOTYPES
 ******************************************************************************/
void INIT_delay(uint32_t timer, uint32_t timerPeripheral, uint32_t timerBase,
                uint32_t timerConfiguration);


#endif /* UTILITIES_DELAY_H_ */

/*******************************************************************************
 *                       END OF FILE
 ******************************************************************************/
