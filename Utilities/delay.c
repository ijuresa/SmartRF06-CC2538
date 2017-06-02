
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
* @brief    Interrupt handler for timer
********************************************************************************
* @return   Nothing
********************************************************************************
* @date     2017-05-28
*******************************************************************************/
void Timer0BIntHandler(void) {
    // Clear Timer interrupt flag
    TimerIntClear(GPTIMER0_BASE, GPTIMER_TIMB_TIMEOUT);
}

/*******************************************************************************
* @brief    Delay function using SYS clock
* @note     Usage:
*               1 loop           = 3 cycles
*               1 cycle          = 3.125 * 10^-8
*               1 microsecond    = 32 cycles
*
* @example  For 1 second delay:
*               (((1 * 1 000 000) * 32) / 3) = 10 666 667
* @example  For 50 microsecond delay:
*               ((50 * 32) / 3) = 533
********************************************************************************
* @return   Nothing
********************************************************************************
* @date     2017-05-29
*******************************************************************************/
void delay_SysCtrlDelay(uint32_t delay) {
    SysCtrlDelay(delay);
}

/*******************************************************************************
* @brief    Initialize Timer
********************************************************************************
* @return   Nothing
********************************************************************************
* @date     2017-05-28
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
