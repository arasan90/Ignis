/**
 ********************************************************************************
 * @file    k_hal_i2c_master_mock.c
 * @author  Massimiliano Ianniello
 * @date    19/02/26
 ********************************************************************************
 */
#include "k_hal_i2c_master_mock.h"

/* Includes ------------------------------------------------------------------*/
/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Definitions ------------------------------------------------------*/
DEFINE_FAKE_VOID_FUNC(k_hal_i2c_master_init)
DEFINE_FAKE_VALUE_FUNC(int, k_hal_i2c_master_add_device, k_hal_i2c_master_device_handle_t *, uint8_t, size_t)
DEFINE_FAKE_VALUE_FUNC(int, k_hal_i2c_master_read, k_hal_i2c_master_device_handle_t, uint8_t *, size_t)
DEFINE_FAKE_VALUE_FUNC(int, k_hal_i2c_master_write, k_hal_i2c_master_device_handle_t, const uint8_t *, size_t)
