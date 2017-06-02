
#ifndef LIBRARIES_AOA_DRIVER_H_
#define LIBRARIES_AOA_DRIVER_H_

/*******************************************************************************
 *                       INCLUDE FILES
 ******************************************************************************/
// Standard
#include <stdint.h>
#include <math.h>

// Drivers
#include "gpio.h"

// Local
#include "errors.h"
#include "delay.h"


/*******************************************************************************
 *                       CONSTANTS
 ******************************************************************************/
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

// Pin used to communicate with multiplexer
#define MULTIPLEXER_COMMUNICATION_PIN       GPIO_PIN_0
#define MULTIPLEXER_COMMUNICATION_PIN_BASE  GPIO_C_BASE
#define ZERO_VALUE                          0u
/*******************************************************************************
 *                       DATA STRUCTURES
 ******************************************************************************/
typedef struct AOA_plug_STRUCT {
    uint8_t led;
    uint8_t portNumber;

    //!< Calibration params - float not supported - check for overflow
    float P1I;
    float P1III;
    float PII[5];           //< For convenient calculation of cw_ccw
    float CW_CCW[31];

    //!< Bias for section I and III
    float P0I[AOA_INPUTS_NUM];
    float P0III[AOA_INPUTS_NUM];

    //!< Minimum value of maximum incident light accepted as reliable measurement
    uint16_t MAX_VAL_THRESHOLD;

    //!< Values of each photo detector reading
    uint16_t values[AOA_INPUTS_NUM];

    //!< Interference caused by exterior light on each photo detector
    uint16_t interf[AOA_INPUTS_NUM];
    uint16_t interf2[AOA_INPUTS_NUM];

    uint16_t threshold; //TODO: Changed from int - check for overflow
} AOA_plug_S;


/*******************************************************************************
 *                       MACROS
 ******************************************************************************/
#define bitRead(value, bit) (((value) >> (bit)) & 0x01u)

/*******************************************************************************
 *                       GLOBAL AND STATIC VARIABLES
 ******************************************************************************/
#ifdef AOA_DRIVER_C



    static void AOA_setValues(AOA_plug_S *aoaPlug);

    // Output functions - need to be changed when porting to another MCU
    static void digitalWrite();


#endif

/*******************************************************************************
 *                       PUBLIC FUNCTION PROTOTYPES
 ******************************************************************************/
void INIT_aoaPlug(AOA_plug_S *aoaPlug, uint8_t aoaPortNumber, RF06_error_E *err);
void AOA_select(AOA_plug_S *aoaPlug, uint8_t channel);
void AOA_readInputs(AOA_plug_S *aoaPlug, uint8_t *outputArray);
void AOA_setThreshold(AOA_plug_S *aoaPlug);






// TODO: The rest

/*
 * Sensor number 6. TODO: Find out corresponding values
 *
 * [[[0.074001446093514736, 2.1091110368414916], [0.074001446093514736, 2.2355774983709034], [0.074001446093514736, 2.1609641590766451],
 * [0.074001446093514736, 2.0966530458394756], [0.074001446093514736, 2.1919046170290821], [0.074001446093514736, 2.1814950749328847],
 * [0.074001446093514736, 2.1297408369438244], [0.074001446093514736, 2.0104331504209814], [0.074001446093514736, 2.0858827952948205],
 * [0.074001446093514736, 2.5062560549434765], [0.074001446093514736, 2.2724596495853122], [0.074001446093514736, 1.8477844290539249]],
 * [array([ -4.77345334e-05,  -4.50211632e-04,   1.77757912e-02,
 *        2.99785083e-01,   1.52901584e+00]), array([ -4.77345334e-05,  -4.50211632e-04,   1.77757912e-02,
 *        2.99785083e-01,   1.52901584e+00]), array([ -4.77345334e-05,  -4.50211632e-04,   1.77757912e-02,
 *        2.99785083e-01,   1.52901584e+00]), array([ -4.77345334e-05,  -4.50211632e-04,   1.77757912e-02,
 *        2.99785083e-01,   1.52901584e+00]), array([ -4.77345334e-05,  -4.50211632e-04,   1.77757912e-02,
 *        2.99785083e-01,   1.52901584e+00]), array([ -4.77345334e-05,  -4.50211632e-04,   1.77757912e-02,
 *        2.99785083e-01,   1.52901584e+00]), array([ -4.77345334e-05,  -4.50211632e-04,   1.77757912e-02,
 *        2.99785083e-01,   1.52901584e+00]), array([ -4.77345334e-05,  -4.50211632e-04,   1.77757912e-02,
 *        2.99785083e-01,   1.52901584e+00]), array([ -4.77345334e-05,  -4.50211632e-04,   1.77757912e-02,
 *        2.99785083e-01,   1.52901584e+00]), array([ -4.77345334e-05,  -4.50211632e-04,   1.77757912e-02,
 *        2.99785083e-01,   1.52901584e+00]), array([ -4.77345334e-05,  -4.50211632e-04,   1.77757912e-02,
 *        2.99785083e-01,   1.52901584e+00]), array([ -4.77345334e-05,  -4.50211632e-04,   1.77757912e-02,
 *        2.99785083e-01,   1.52901584e+00])], [[-0.04089447744762293, 1.4291038129149067], [-0.04089447744762293, 1.6394898887997251],
 *        [-0.04089447744762293, 1.4992743308804475], [-0.04089447744762293, 1.5152024080966249], [-0.04089447744762293, 1.5011817478765821],
 *        [-0.04089447744762293, 1.5492095865283322], [-0.04089447744762293, 1.589421262851936], [-0.04089447744762293, 1.4769705670599229],
 *        [-0.04089447744762293, 1.5215779618069172], [-0.04089447744762293, 1.4054248824421982], [-0.04089447744762293, 1.8098479832435357],
 *        [-0.04089447744762293, 1.5176944908435044]]]
 *
 */
#endif /* LIBRARIES_AOA_DRIVER_H_ */

/*******************************************************************************
 *                       END OF FILE
 ******************************************************************************/
