#ifndef AOA_DRIVER_C
#define AOA_DRIVER_C

/*******************************************************************************
 *                       INCLUDE FILES
 ******************************************************************************/
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
    if(value > SET_HIGH) {
        *err = ERR_AOA_WRONG_GPIO_WRITE;
        return;
    }

    // Check if we want to write to wrong PORT
    else if((portNumber == 0) || (portNumber > AOA_PORT1)) {
        *err = ERR_AOA_WRONG_PORT;
        return;
    }

    // Write to PORT1
    else if (portNumber == AOA_PORT1) {
        GPIOPinWrite(AOA_PORTS_GPIO_BASE, AOA_PORT1_PDIO, value);
    }

//    // Write to PORT2
//    else {
//        GPIOPinWrite(AOA_PORTS_GPIO_BASE, AOA_PORT2_PDIO, value);
//    }
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
    GPIOPinTypeGPIOOutput(AOA_PORTS_GPIO_BASE, AOA_PORT1_PDIO);

    // PORT2
//    GPIOPinTypeGPIOOutput(AOA_PORTS_GPIO_BASE, AOA_PORT2_PDIO);

    // Initialize Analog GPIO
    // AOA -> PIN5 on RF2.5 PIN
    GPIOPinTypeGPIOOutput(ADC_PIN_BASE, ADC_PIN);

    // Configure ADC
    SOCADCSingleConfigure(SOCADC_10_BIT, SOCADC_REF_INTERNAL);
}

/*******************************************************************************
* @brief    Set GPIO as INPUT
********************************************************************************
* @param    gpioPin:       GPIO Pin to be set (0 -7)
* @param    gpioPort:      GPIO PORT to be set (A, B, C, D)
* @param    *err:           Pointer to error return code
* @return   Nothing
********************************************************************************
* @date     2017-06-02
*******************************************************************************/
static inline void setGpioModeInput(uint8_t gpioPin, uint32_t gpioPort,
                                    RF06_error_E *err) {
    GPIOPinTypeGPIOInput((uint32_t)gpioPort, gpioPin);
}

/*******************************************************************************
* @brief    Sets values to be used in get_aoa methods
********************************************************************************
* @param    *aoaPlug:       Pointer to AOA data structure
* @param    *err:           Pointer to error return code
* @return   Nothing
********************************************************************************
* @date     2017-06-05
*******************************************************************************/
static inline void AOA_setValues(AOA_plug_S *aoaPlug, RF06_error_E *err) {
    uint16_t diff = 0;
    uint8_t i;

    AOA_readInputs(aoaPlug, aoaPlug->values, err);

    for(i = 0; i < AOA_INPUTS_NUM; i ++) {
        diff = aoaPlug->values[i] - aoaPlug->interf[i];
        aoaPlug->values[i] = (diff > aoaPlug->threshold) ? (uint16_t)diff : 0;
    }
}

/*******************************************************************************
* @brief    Return MAX value in AOA values
********************************************************************************
* @param    *aoaPlug:       Pointer to AOA data structure
* @return   max
********************************************************************************
* @date     2017-06-05
*******************************************************************************/
static inline uint16_t AOA_getMaxValue(AOA_plug_S *aoaPlug) {
    uint16_t max = aoaPlug->values[0];
    uint8_t i;

    for(i = 1; i < AOA_INPUTS_NUM; ++ i) {
        if(aoaPlug->values[i] > max) max = aoaPlug->values[i];
    }
    return max;
}

/*******************************************************************************
* @brief    Calculate AOA
********************************************************************************
* @param    *aoaPlug:       Pointer to AOA data structure
* @return   aoa
********************************************************************************
* @date     2017-06-06
*******************************************************************************/
static inline float AOA_calculateAoa(AOA_plug_S *aoaPlug) {
    uint8_t m   = 0;    //!
    uint8_t ccw = 0;    //!
    uint8_t cw  = 0;    //!
    uint8_t section;    //!
    uint8_t i;

    float v_m, v_ccw, v_cw, v_cw_ccw, aoa;

    for(i = 1; i < AOA_INPUTS_NUM; i ++) {
        if(aoaPlug->values[i] > aoaPlug->values[m]) m = i;
    }

    ccw     = (m + AOA_INPUTS_NUM - 1) % (AOA_INPUTS_NUM);
    cw      = (m + 1) % AOA_INPUTS_NUM;
    v_m     = aoaPlug->values[m];
    v_cw    = aoaPlug->values[cw];
    v_ccw   = aoaPlug->values[ccw];
    v_cw_ccw = (v_cw / v_ccw);

    // Interpolate
    for(i = 1; i < 31; i ++) {
        if(v_cw_ccw < aoaPlug->CW_CCW[i]) break;
    }

    // Calculate AOA relative to m, based on chosen section
    if(i < AOA_I_MARGIN) {
        section = 1;
        aoa = (v_m / (v_ccw - aoaPlug->P0I[ccw])) / aoaPlug->P1I;
    } else if(i > (30 - AOA_III_MARGIN)) {
        section = 3;
        aoa = (v_m / (v_cw - aoaPlug->P0III[ccw])) / aoaPlug->P1III;
    } else {
        section = 2;
        aoa = i - 16 + (v_cw_ccw - aoaPlug->CW_CCW[i - 1])
                / (aoaPlug->CW_CCW[i] - aoaPlug->CW_CCW[ i - 1]);
    }

    // Get absolute AOA and put it in 0 - 360 range
    aoa += m * 30.0;
    aoa = aoa < 0 ? aoa + 360 : aoa;

    return aoa;
}

/*******************************************************************************
* @brief    Get AOA
********************************************************************************
* @param    *aoaPlug:       Pointer to AOA data structure
* @param    *err:            Pointer to error return code
* @return
********************************************************************************
* @date     2017-06-06
*******************************************************************************/
static inline float AOA_getAoa(AOA_plug_S *aoaPlug, RF06_error_E *err) {
    float aoa = AOA_getAoaDeg(aoaPlug, err);
    if((*err != ERR_OK) || (*err == ERR_AOA_DEG_FAIL)) {
        *err = ERR_AOA_FLOAT_FAIL;
        return -1;
    }
    return aoa * PI / 180;
}

/*******************************************************************************
* @brief    Get AOA
********************************************************************************
* @param    *aoaPlug:       Pointer to AOA data structure
* @param    *err:           Pointer to error return code
* @return
********************************************************************************
* @date     2017-06-06
*******************************************************************************/
static inline float AOA_getAoaDeg(AOA_plug_S *aoaPlug, RF06_error_E *err) {
    AOA_setValues(aoaPlug, err);

    if(AOA_getMaxValue(aoaPlug) < aoaPlug->MAX_VAL_THRESHOLD) {
        *err = ERR_AOA_DEG_FAIL;
        return -1;
    }
    return AOA_calculateAoa(aoaPlug);
}

/*******************************************************************************
* @brief    Select channel from multiplexer
********************************************************************************
* @param    *aoaPlug:   Pointer to AOA data structure
* @param    channel:    AOA channel for multiplexer
* @param    *err:       Pointer to error return code
* @return   Nothing
********************************************************************************
* @date     2017-06-02
*******************************************************************************/
static inline void AOA_select(AOA_plug_S *aoaPlug, uint8_t channel,
                              RF06_error_E *err) {
    uint8_t i;

    // Check channel
    if(channel > 11) {
        *err = ERR_AOA_WRONG_CHANNEL;
        return;
    }

    // Check if AOA is initialized
    else if((aoaPlug->portNumber == 0)
                || (aoaPlug->portNumber > AOA_PORT2)) {
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
        if(aoaPlug->portNumber == AOA_PORT1) {
            digitalWrite(AOA_PORT1, SET_HIGH, err);
        } else digitalWrite(AOA_PORT2, SET_HIGH, err);

        delay_SysCtrlDelay(us);

        if(aoaPlug->portNumber == AOA_PORT1) {
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
* @param    *aoaPlug:        Pointer to AOA data structure
* @param    *outputArray:    array for data
* @param    *err:            Pointer to error return code
* @return   Nothing
********************************************************************************
* @date     2017-06-02
*******************************************************************************/
static void AOA_readInputs(AOA_plug_S *aoaPlug, uint16_t *outputArray,
                    RF06_error_E *err) {
    uint8_t i;
    // Set ADC Pin as INPUT
    setGpioModeInput(ADC_PIN, ADC_PIN_BASE, err);
    for(i = 0; i < AOA_INPUTS_NUM; i ++) {
        AOA_select(aoaPlug, i, err);
        //TODO: return error code

        // 1ms
        delay_SysCtrlDelay(10667);
        AOA_select(aoaPlug, i, err);
        // TODO: return error code

        delay_SysCtrlDelay(AOA_SWITCH_DELAY);

        // Page 11. Analog pins driver doc
        // Trigger single conversion on PA6
        SOCADCSingleStart(SOCADC_AIN6);

        // Wait until conversion is completed
        while(!SOCADCEndOfCOnversionGet()) { }

        // Get data and shift
        outputArray[i] = SOCADCDataGet() >> SOCADC_10_BIT_RSHIFT;
    }
}

/*******************************************************************************
* PUBLIC FUNCTIONS
*******************************************************************************/

/*******************************************************************************
* @brief    Initialize AOA
********************************************************************************
* @param    *aoaPlug:       Pointer to AOA data structure
* @param    aoaPortNumber:  AOA Port Number [1 or 2]
* @param    *err:           Pointer to error return code
* @return   Nothing
********************************************************************************
* @date     2017-06-01
*******************************************************************************/
void INIT_aoaPlug(AOA_plug_S *aoaPlug, uint8_t aoaPortNumber,
                  RF06_error_E *err) {
    int8_t i;

    // Initialize GPIO
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

    // Check PortNumber
    if((aoaPortNumber == 0) || (aoaPortNumber > AOA_PORT2)) {
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
* @brief    Get AOA
********************************************************************************
* @param    *aoaPlug:       Pointer to AOA data structure
* @param    *err:           Pointer to error return code
* @return   aoa
********************************************************************************
* @date     2017-06-06
*******************************************************************************/
uint16_t AOA_getAoaIntForce(AOA_plug_S *aoaPlug, RF06_error_E *err) {
    uint16_t tmp = aoaPlug->MAX_VAL_THRESHOLD;

    // Temporary remove threshold
    aoaPlug->MAX_VAL_THRESHOLD = 0;
    float aoa = AOA_getAoa(aoaPlug, err);

    aoaPlug->MAX_VAL_THRESHOLD = tmp;
    return (uint16_t)(aoa * 10000);
}

/*******************************************************************************
* @brief    Get AOA
********************************************************************************
* @param    *aoaPlug:       Pointer to AOA data structure
* @param    *err:           Pointer to error return code
* @return   aoa
********************************************************************************
* @date     2017-06-06
*******************************************************************************/
uint16_t AOA_getAoaInt(AOA_plug_S *aoaPlug, RF06_error_E *err) {
    float aoa = AOA_getAoa(aoaPlug, err);

    if((*err != ERR_OK) || (*err == ERR_AOA_FLOAT_FAIL)) {
        *err = ERR_AOA_INT_FAIL;
        return ERR_AOA_INT_FAIL;
    }
    return (uint16_t)(aoa * 10000);
}


/*******************************************************************************
* @brief
********************************************************************************
* @param    *aoaPlug:       Pointer to AOA data structure
* @param    *err:           Pointer to error return code
* @return   Nothing
********************************************************************************
* @date     2017-06-06
*******************************************************************************/
void AOA_setThreshold(AOA_plug_S *aoaPlug, RF06_error_E *err) {
    uint8_t noise = 0;
    uint8_t i;

    aoaPlug->threshold = AOA_NOISE_THRESHOLD;

    AOA_readInputs(aoaPlug, aoaPlug->interf, err);
    if(*err != ERR_OK) return;
    AOA_readInputs(aoaPlug, aoaPlug->interf2, err);
    if(*err != ERR_OK) return;

    for(i = 0; i < AOA_INPUTS_NUM; i ++) {
        noise = aoaPlug->interf2[i] - aoaPlug->interf[i];
        if(abs(noise) > aoaPlug->threshold) {
            aoaPlug->threshold = abs(noise) + AOA_NOISE_THRESHOLD;
        }
    }
}
#endif // AOA_DRIVER_C

/*******************************************************************************
 *                       END OF FILE
 ******************************************************************************/
