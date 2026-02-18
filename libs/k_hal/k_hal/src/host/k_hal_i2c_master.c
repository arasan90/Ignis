/**
 ********************************************************************************
 * @file    k_hal_i2c_master.c
 * @author  Massimiliano Ianniello
 * @date    18/02/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "k_hal/k_hal_i2c_master.h"
/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Definitions ------------------------------------------------------*/
void k_hal_i2c_master_init(void) {}

int k_hal_i2c_master_add_device(k_hal_i2c_master_device_handle_t *handle_p, uint8_t address, size_t speed_hz)
{
    (void)handle_p;
    (void)address;
    (void)speed_hz;
    return 0;
}

int k_hal_i2c_master_read(k_hal_i2c_master_device_handle_t handle, uint8_t *data_p, size_t length)
{
    (void)handle;
    (void)data_p;
    (void)length;
    return 0;
}

int k_hal_i2c_master_write(k_hal_i2c_master_device_handle_t handle, const uint8_t *data_p, size_t length)
{
    (void)handle;
    (void)data_p;
    (void)length;
    return 0;
}
