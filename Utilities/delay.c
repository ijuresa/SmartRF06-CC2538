
#ifndef UTILITIES_DELAY_C_
#define UTILITIES_DELAY_C

/*******************************************************************************
 *                       INCLUDE FILES
 ******************************************************************************/
#include "delay.h"

/*******************************************************************************
 *                       GLOBAL AND STATIC VARIABLES
 ******************************************************************************/
static volatile bool tBIntFlag = false;


/*******************************************************************************
* @brief
********************************************************************************
* @retval   Nothing
*******************************************************************************/
void TimerIntHandler(void) {
    //TimerIntClear(, ui32IntFlags);
}


/*******************************************************************************
* @brief
********************************************************************************
* @retval   Nothing
*******************************************************************************/
void INIT_delay(uint32_t timer, uint32_t timerPeripheral, uint32_t timerBase,
                 uint32_t timerConfiguration) {

    // Enable Timer peripheral
    SysCtrlPeripheralEnable(timerPeripheral);

    // Configure Timer peripheral
    TimerConfigure(timerBase, timerConfiguration);

    // Set Timer load value to 1ms
    TimerLoadSet(timerBase, timer, SysCtrlClockGet() / TICK_RATE);

    // Register handler
    TimerIntRegister(timerBase, timer, TimerIntHandler);

    // Enable processor interrupts
    IntMasterEnable();

    // Check if timer A, B or both is used and set interrupt as timer timeout
    if(timer == GPTIMER_A) {
        TimerIntEnable(timerBase, GPTIMER_TIMA_TIMEOUT);
        IntEnable(INT_);
    }
    else if(timer == GPTIMER_B) {
        TimerIntEnable(timerBase, GPTIMER_TIMB_TIMEOUT);
    }
    else TimerIntEnable(timerBase, GPTIMER_TIMA_TIMEOUT | GPTIMER_TIMB_TIMEOUT);


}

#endif // delay_c_

/*******************************************************************************
 *                       END OF FILE
 ******************************************************************************/
