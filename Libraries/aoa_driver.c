

#ifndef AOA_DRIVER_C
#define AOA_DRIVER_C

/* Includes */
#include "aoa_driver.h"

/*******************************************************************************
* PRIVATE FUNCTIONS
*******************************************************************************/

/*******************************************************************************
* @brief    Set pins as high or low
********************************************************************************
* @param    portNumber: Number of port on AOA sensor
* @param    value:      0 or 1
* @param    *err:       error return code
********************************************************************************
* @return   Nothing
********************************************************************************
* @date     2017-06-02
*******************************************************************************/
static inline void digitalWrite(uint8_t portNumber, uint8_t value,
                                RF06_error_E *err) {

    // Check if value is anything else than 0 or 1
    if((value != 0) || (value != 1)) {
        *err = ERR_AOA_WRONG_GPIO_WRITE;
        return;
    }

    // Check if we want to write to wrong PORT
    else if((portNumber != AOA_PORT1) || (portNumber != AOA_PORT1)) {
        *err = ERR_AOA_WRONG_PORT;
        return;
    }

    // Write to PORT1
    else if (portNumber == AOA_PORT1) {
        GPIOPinWrite(MULTIPLEXER_COMMUNICATION_PIN_BASE,
                         MULTIPLEXER_COMMUNICATION_PIN_PORT1,
                         value);
    }

    // Write to PORT2
    else {
        GPIOPinWrite(MULTIPLEXER_COMMUNICATION_PIN_BASE,
                 MULTIPLEXER_COMMUNICATION_PIN_PORT2,
                 value);
    }
}

/*******************************************************************************
* @brief    Initialize GPIO pins for AOA PORT1 and PORT2
********************************************************************************
* @return   Nothing
********************************************************************************
* @date     2017-06-02
*******************************************************************************/
static inline void INIT_Gpio() {
    // PORT1
    GPIOPinTypeGPIOOutput(MULTIPLEXER_COMMUNICATION_PIN_BASE,
                          MULTIPLEXER_COMMUNICATION_PIN_PORT1);

    // PORT2
    GPIOPinTypeGPIOOutput(MULTIPLEXER_COMMUNICATION_PIN_BASE,
                          MULTIPLEXER_COMMUNICATION_PIN_PORT2);
}

/*******************************************************************************
* @brief    Set GPIO as INPUT
********************************************************************************
* @return   Nothing
********************************************************************************
* @date     2017-06-02
*******************************************************************************/
static inline void setGpioModeInput(uint8_t gpioPin, RF06_error_E *err) {
    GPIOPinTypeGPIOInput(MULTIPLEXER_COMMUNICATION_PIN_BASE, gpioPin);
}

/*******************************************************************************
* @brief
********************************************************************************
* @param    :
* @return   Nothing
********************************************************************************
* @date
*******************************************************************************/
void AOA_setThreshold(AOA_plug_S *aoaPlug) {

}

/*******************************************************************************
* @brief
********************************************************************************
* @param    :
* @return   Nothing
********************************************************************************
* @date
*******************************************************************************/
static inline void AOA_setValues(AOA_plug_S *aoaPlug) {

}


/*******************************************************************************
* PUBLIC FUNCTIONS
*******************************************************************************/

/*******************************************************************************
* @brief    Initialize AOA port1 or port2
********************************************************************************
* @param    *aoaPlug:       AOA data structure
* @param    aoaPortNumber:  AOA Port Number, can be 1 or 2
* @param    *err:           error return code
* @return   Nothing
********************************************************************************
* @date     2017-06-01
*******************************************************************************/
void INIT_aoaPlug(AOA_plug_S *aoaPlug, uint8_t aoaPortNumber,
                  RF06_error_E *err) {
    int8_t i;

    *err = ERR_OK;
    INIT_Gpio();

    // TODO: Write EEPROM read function
    /*          Pinout on AOA
     * SDI          PB0
     * SII          PB1
     * SCI          PB3
     *
     * PB0, PB1, PB2 - connected on ISP but also on multiplexer
     *
     * ATtiny45     IC1A
     *    PB0       A - pin 10
     *    PB1       B - pin 11
     *    PB2       C - pin 12
     *
     * More on ATtiny45 datasheet page 159
     *
     */

    if((aoaPortNumber != 1) || (aoaPortNumber != 2)) {
        *err = ERR_AOA_WRONG_PORT;
        return;
    }

    aoaPlug->led = (aoaPortNumber == 1) ? 4 : 3;
    aoaPlug->threshold = 40;
    aoaPlug->portNumber = aoaPortNumber;

    // led.mode(OUTPUT) -> TODO: write wrapper for multiplexer

    // Calibration Data
    aoaPlug->P1I    = 0.0714173;
    float PII_temp[5] = { -0.00004773,
                          -0.00045021,
                           0.01777579,
                           0.29978508,
                           1.52901584
                         };
    memcpy(aoaPlug->PII, PII_temp, sizeof(aoaPlug->PII));

    aoaPlug->P1III  = -0.046489;

    float P0I_temp[AOA_INPUTS_NUM] = { 2.1091110368414916,
                                       2.2355774983709034,
                                       2.1609641590766451,
                                       2.1609641590766451,
                                       2.1919046170290821,
                                       2.1814950749328847,
                                       2.1297408369438244,
                                       2.0104331504209814,
                                       2.0858827952948205,
                                       2.2724596495853122,
                                       1.8477844290539249
                                    };
    memcpy(aoaPlug->P0I, P0I_temp, sizeof(aoaPlug->P0I));

    float P0III_temp[AOA_INPUTS_NUM] = { 1.4291038129149067,
                                         1.6394898887997251,
                                         1.4992743308804475,
                                         1.5152024080966249,
                                         1.5011817478765821,
                                         1.5492095865283322,
                                         1.5894212628519365,
                                         1.4769705670599229,
                                         1.4769705670599229,
                                         1.4769705670599229,
                                         1.5176944908435044
                                    };
    memcpy(aoaPlug->P0III, P0III_temp, sizeof(aoaPlug->P0III));

    for(i = -15; i < 16; i ++) {
        aoaPlug->CW_CCW[i + 15] = aoaPlug->PII[0] * pow(i, 4)
                                + aoaPlug->PII[1] * pow(i, 3)
                                + aoaPlug->PII[2] * pow(i, 2)
                                + aoaPlug->PII[3] * i + aoaPlug->PII[4];
    }
}

/*******************************************************************************
* @brief    Select channel from multiplexer
********************************************************************************
* @param    *aoaPlug:   AOA data structure
* @param    channel:    AOA channel for multiplexer
* @param    *err:       error return code
* @return   Nothing
********************************************************************************
* @date     2017-06-02
*******************************************************************************/
void AOA_select(AOA_plug_S *aoaPlug, uint8_t channel, RF06_error_E *err) {
    uint8_t i;
    *err = ERR_OK;

    // Check channel
    if(channel > 11) {
        *err = ERR_AOA_WRONG_CHANNEL;
        return;
    }

    // Check if AOA is initialized
    else if((aoaPlug->portNumber != AOA_PORT1)
                || (aoaPlug->portNumber != AOA_PORT2)) {
        *err = ERR_AOA_NOT_INITIALIZED;
        return;
    }

    // Set both PORT Pins to 0
    digitalWrite(AOA_PORT1, SET_LOW, err);
    if(*err != ERR_OK) return;

    digitalWrite(AOA_PORT1, SET_LOW, err);
    if(*err != ERR_OK) return;

    // 50 microseconds delay
    delay_SysCtrlDelay(533);

    // Select channel
    // 0x10 - ?
    uint8_t data = 0x10 | (channel & 0x0F);

    // Disable interrupts
    IntMasterDisable();

    for(i = 0; i < 5; ++ i) {
        // Return value will be used as delay
        // 96 - 9us and 32 - 3us
        uint8_t us = bitRead(data, 4 - i) ? 96 : 32;

        // Check on which PORT AOA structure is set
        if(aoaPlug->portNumber == 1) {
            digitalWrite(AOA_PORT1, SET_HIGH, err);
        } else digitalWrite(AOA_PORT2, SET_HIGH, err);

        delay_SysCtrlDelay(us);

        if(aoaPlug->portNumber == 1) {
            digitalWrite(AOA_PORT1, SET_LOW, err);
        } else digitalWrite(AOA_PORT2, SET_LOW, err);

        // 4 microseconds delay
        delay_SysCtrlDelay(43);
    }

    // Enable interrupts
    IntMasterEnable();
}

/*******************************************************************************
* @brief    Read and save values from channels
********************************************************************************
* @param    *aoaPlug:   AOA data structure
* @param    *outputArray:    array for data
* @param    *err:       error return code
* @return   Nothing
********************************************************************************
* @date     2017-06-02
*******************************************************************************/
void AOA_readInputs(AOA_plug_S *aoaPlug, uint8_t *outputArray,
                    RF06_error_E *err) {
    uint8_t i;
    setGpioModeInput(MULTIPLEXER_COMMUNICATION_PIN_PORT1, err);
    for(i = 0; i < AOA_INPUTS_NUM; i ++) {
        AOA_select(aoaPlug, i, err);
        //TODO: return error code

        // 1ms
        delay_SysCtrlDelay(10667);
        AOA_select(aoaPlug, i, err);
        // TODO: return error code

        delay_SysCtrlDelay(AOA_SWITCH_DELAY);

        //outputArray[i] =
        // Page 11. Analog pins
    }

}

#endif // AOA_DRIVER_C

/*******************************************************************************
 *                       END OF FILE
 ******************************************************************************/
