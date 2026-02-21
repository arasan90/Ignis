/**
 ********************************************************************************
 * @file    k_hal_i2c_master_priv.h
 * @author  Massimiliano Ianniello
 * @date    18/02/26
 ********************************************************************************
 */
#ifndef K_HAL_I2C_MASTER_PRIV_H
#define K_HAL_I2C_MASTER_PRIV_H

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>

#include "driver/i2c_master.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
typedef struct k_hal_i2c_master_ctx_s
{
    bool                    initialized;
    i2c_master_bus_handle_t bus_handle;
} k_hal_i2c_master_ctx_t;

/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/

#ifdef __cplusplus
}
#endif
#endif  // K_HAL_I2C_MASTER_PRIV_H
