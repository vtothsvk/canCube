#ifndef CAN_CUBE_TYPES_H__
#define CAN_CUBE_TYPES_H__

#include <cstdlib>
#include "mbed.h"
#include "drivers/CAN.h"
#include <iostream>

/* *///CAN id macros///* */
#define CUBE_PUMP_STATE_ID      0x00
#define DEFAULT_CANCUBE_ADDR    0x0000
#define CUBE_DEV_TYPE           0x0011
#define CAN_ID_MASK             0x3FF800

/* *///Cube control macros///* */
#define CUBE_DIR_RIGHT  true
#define CUBE_DIR_LEFT   false

#define CUBE_START      true
#define CUBE_STOP       false

#ifndef CANCUBE_DEF_CAL
#define CANCUBE_DEF_CAL 1000
#endif

#ifndef CANCUBE_DEF_PUMPV
#define CANCUBE_DEF_PUMPV 20
#endif

/**
 * @brief Cube return codes
 */
typedef enum cube_status{
    CUBE_OK,            /**< operation completed successfully */
    CUBE_NO_DATA,       /**< no data received */
    CUBE_TX_ERROR,      /**< data transmission error */
    CUBE_RX_ERROR,      /**< data recepiton error */
    CUBE_TX_TIMEOUT,    /**< timeout during data transmission */
    CUBE_RX_TIMEOUT,    /**< timeout during data recepiton */
    CUBE_ERR            /**< feature not yed implemented */
}cube_status_t;

#endif//CAN_CUBE_TYPES_H__
