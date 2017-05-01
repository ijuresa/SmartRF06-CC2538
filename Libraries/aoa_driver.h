
#ifndef LIBRARIES_AOA_DRIVER_H_
#define LIBRARIES_AOA_DRIVER_H_

/*********************************************************************************************************
 *                       INCLUDE FILES
 ********************************************************************************************************/
#include <stdint.h>
#include "errors.h"

/*********************************************************************************************************
 *                       CONSTANTS
 ********************************************************************************************************/
#define AOA_INPUTS_NUM      12  //< Number of phototransistors on aoa sensor
#define AOA_SWITCH_DELAY    5   //< Delay until next phototransistor is selected in ms
#define AOA_NOISE_THRESHOLD 2
#define AOA_I_MARGIN        8   //< Margin of section I when calculating aoa
#define AOA_III_MARGIN      8   //< Margin of section I when calculating aoa


/* EEPROM Addresses */
#define CALIBRATION_EEPROM_ADDR     ((uint8_t*) 0x100)
#define P1I_EEPROM_ADDR             (CALIBRATION_EEPROM_ADDR)
#define P1III_EEPROM_ADDR           (CALIBRATION_EEPROM_ADDR + 1)
#define PII_EEPROM_ADDR             (CALIBRATION_EEPROM_ADDR + 2)
#define P0I_EEPROM_ADDR             (CALIBRATION_EEPROM_ADDR + 7)
#define P0III_EEPROM_ADDR           (CALIBRATION_EEPROM_ADDR + 19)
#define MAXVALTHR_EEPROM_ADDR       (uint8_t*)(CALIBRATION_EEPROM_ADDR + 31)

/*********************************************************************************************************
 *                       DATA STRUCTURES
 ********************************************************************************************************/
typedef struct AOA_plug_STRUCT {
    uint8_t led;

    //!< Calibration params - float not supported - check for overflow
    float P1I;
    float P1III;
    float PII[5];           //< For convenient calculation of cw_ccw
    float CW_CCW[31];

    //!< Bias for section I and III //TODO: Changed from float check for overflow
    uint16_t P0I[AOA_INPUTS_NUM];
    uint16_t P0III[AOA_INPUTS_NUM];

    //!< Minimum value of maximum incident light accepted as reliable measurement
    uint16_t MAX_VAL_THRESHOLD;

    //!< Values of each photo detector reading
    uint16_t values[AOA_INPUTS_NUM];

    //!< Interference caused by exterior light on each photo detector
    uint16_t interf[AOA_INPUTS_NUM];
    uint16_t interf2[AOA_INPUTS_NUM];

    uint16_t threshold; //TODO: Changed from int - check for overflow
} AOA_plug_S;


/*********************************************************************************************************
 *                       GLOBAL AND STATIC VARIABLES
 ********************************************************************************************************/
#ifdef AOA_DRIVER_C
    static void AOA_setValues(AOA_plug_S *aoaPlug);
#endif
/*********************************************************************************************************
 *                       PUBLIC FUNCTION PROTOTYPES
 ********************************************************************************************************/
void INIT_aoaPlug(AOA_plug_S *aoaPlug, uint8_t number);
void AOA_select(AOA_plug_S *aoaPlug, uint8_t channel);
void AOA_readInputs(AOA_plug_S *aoaPlug, uint8_t *outputArray);
void AOA_setThreshold(AOA_plug_S *aoaPlug);


// TODO: The rest

#endif /* LIBRARIES_AOA_DRIVER_H_ */

/*********************************************************************************************************
 *                       END OF FILE
 ********************************************************************************************************/
