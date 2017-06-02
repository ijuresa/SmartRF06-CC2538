
/*******************************************************************************
 *                       INCLUDE FILES
 ******************************************************************************/
#include "main.h"

/*******************************************************************************
 *                       GLOBAL AND STATIC VARIABLES
 ******************************************************************************/
static AOA_plug_S aoaPlug;


/*******************************************************************************
* @brief    Program start
*           Initialize clock, various peripherals
********************************************************************************
* @return   Nothing
********************************************************************************
* @date   2017-05-15
*******************************************************************************/
int main(void) {
    // Clock
    SysCtrlClockSet(false, false, SYS_CTRL_SYSDIV_32MHZ);

    // I/O clock
    SysCtrlIOClockSet(SYS_CTRL_SYSDIV_32MHZ);

    // Initialize UART
    INIT_uart();

#if SERIAL_DEBUG
    UARTprintf("Start");
#endif

    // Initialize delay
    INIT_delay(GPTIMER_B ,SYS_CTRL_PERIPH_GPT0, GPTIMER0_BASE,
               TIMER_0B_CONFIGURATION);

    // GPIO_PIN_1 is connected to LED1 (orange) -> Used only for testing
    // GPIO_PIN_0 is connected to LED0 (red)
    //      |
    //      --> Removed jumper, used for AOA
    // For reference: swru321b.pdf and swrr143.pdf

   GPIOPinWrite(GPIO_C_BASE, GPIO_PIN_1, 0);
//
    GPIOPinWrite(GPIO_C_BASE, GPIO_PIN_1, GPIO_PIN_1);

    RF06_error_E err = ERR_OK;
    INIT_aoaPlug(&aoaPlug, AOA_PORT_NUMBER, &err);

    for(;;) {

    }
}

/*******************************************************************************
* @brief    Set UART0 interface for console usage
********************************************************************************
* @return   Nothing
********************************************************************************
* @date   2017-05-15
*******************************************************************************/
void INIT_uart(void) {
    // Transmit
    IOCPinConfigPeriphOutput(GPIO_UART_BASE, UART_PIN_TX,
                             IOC_MUX_OUT_SEL_UART0_TXD);

    GPIOPinTypeUARTOutput(GPIO_UART_BASE, UART_PIN_TX);

    // Receive
    IOCPinConfigPeriphInput(GPIO_UART_BASE, UART_PIN_RX, IOC_UARTRXD_UART0);
    GPIOPinTypeUARTInput(GPIO_UART_BASE, UART_PIN_RX);

    // UART0
    UARTStdioInit(0);
}

/*******************************************************************************
 *                       END OF FILE
 ******************************************************************************/
