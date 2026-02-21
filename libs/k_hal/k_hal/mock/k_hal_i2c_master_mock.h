/**
 ********************************************************************************
 * @file    k_hal_i2c_master_mock.h
 * @author  Massimiliano Ianniello
 * @date    19/02/26
 ********************************************************************************
 */
#ifndef K_HAL_I2C_MASTER_MOCK_H
#define K_HAL_I2C_MASTER_MOCK_H

/* Includes ------------------------------------------------------------------*/
#include "fff.h"
#include "k_hal/k_hal_i2c_master.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
DECLARE_FAKE_VOID_FUNC(k_hal_i2c_master_init)
DECLARE_FAKE_VALUE_FUNC(int, k_hal_i2c_master_add_device, k_hal_i2c_master_device_handle_t *, uint8_t, size_t)
DECLARE_FAKE_VALUE_FUNC(int, k_hal_i2c_master_read, k_hal_i2c_master_device_handle_t, uint8_t *, size_t)
DECLARE_FAKE_VALUE_FUNC(int, k_hal_i2c_master_write, k_hal_i2c_master_device_handle_t, const uint8_t *, size_t)

inline void k_hal_i2c_master_reset(void)
{
    RESET_FAKE(k_hal_i2c_master_init);
    RESET_FAKE(k_hal_i2c_master_add_device);
    RESET_FAKE(k_hal_i2c_master_read);
    RESET_FAKE(k_hal_i2c_master_write);
}

#ifdef __cplusplus
}
#endif
#endif  // K_HAL_I2C_MASTER_MOCK_H
