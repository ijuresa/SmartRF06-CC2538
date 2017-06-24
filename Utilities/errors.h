
#ifndef UTILITIES_ERRORS_H_
#define UTILITIES_ERRORS_H_

//!< Error enumerator
typedef enum RF06_error_ENUM {
  ERR_OK,
  ERR_AOA_WRONG_PORT,
  ERR_AOA_WRONG_GPIO,
  ERR_AOA_WRONG_GPIO_MODE,
  ERR_AOA_WRONG_GPIO_WRITE,
  ERR_AOA_WRONG_CHANNEL,
  ERR_AOA_NOT_INITIALIZED,
  ERR_AOA_DEG_FAIL,
  ERR_AOA_FLOAT_FAIL,
  ERR_AOA_INT_FAIL = 63000,

} RF06_error_E;


#endif /* UTILITIES_ERRORS_H_ */

/*********************************************************************************************************
 *                       END OF FILE
 ********************************************************************************************************/
