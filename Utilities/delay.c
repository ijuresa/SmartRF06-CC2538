
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
void Timer0BIntHandler(void) {
    // Clear Timer interrupt flag
    TimerIntClear(GPTIMER0_BASE, GPTIMER_TIMB_TIMEOUT);
}

/*******************************************************************************
* @brief
********************************************************************************
* @retval   Nothing
*******************************************************************************/
void delay_SysCtrlDelay(uint32_t delay) {
    SysCtrlDelay(delay);
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
    TimerLoadSet(timerBase, timer, SysCtrlClockGet() / RATE);

    // Register handler
    TimerIntRegister(timerBase, timer, Timer0BIntHandler);

    // Enable processor interrupts
    IntMasterEnable();

    // Set interrupt as timer timeout
    TimerIntEnable(timerBase, GPTIMER_TIMB_TIMEOUT);
    IntEnable(INT_TIMER0B);

    // Enable
    TimerEnable(timerBase, timer);

    //while(!tBIntFlag);

}

#endif // delay_c_

/*******************************************************************************
 *                       END OF FILE
 ******************************************************************************/
