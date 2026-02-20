/**
 ********************************************************************************
 * @file    ignis_pcf8575.c
 * @author  Massimiliano Ianniello
 * @date    29/01/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "ignis_pcf8575.h"

#include <string.h>

/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
#define IGNIS_KEYMAP_I2C_ADDRESS (0x20)

/* Variables -----------------------------------------------------------------*/
ignis_pcf8575_ctx_t ignis_pcf8575_ctx = {0};

/* Function Definitions ------------------------------------------------------*/
void ignis_pcf8575_init(void)
{
    if (!ignis_pcf8575_ctx.initialized)
    {
        k_hal_i2c_master_init();
        k_osal_mutex_create(&ignis_pcf8575_ctx.mutex_handle);
        k_osal_mutex_lock(ignis_pcf8575_ctx.mutex_handle);
        if (0 == k_hal_i2c_master_add_device(&ignis_pcf8575_ctx.i2c_handle, IGNIS_KEYMAP_I2C_ADDRESS, 10000))
        {
            ignis_pcf8575_ctx.pins_state[0] = 0xFF;
            ignis_pcf8575_ctx.pins_state[1] = 0xFF;
            ignis_pcf8575_ctx.initialized   = true;
        }
        k_osal_mutex_unlock(ignis_pcf8575_ctx.mutex_handle);
    }
}

int ignis_pcf8575_get_status(uint8_t status[2])
{
    int ret_code = -1;
    k_osal_mutex_lock(ignis_pcf8575_ctx.mutex_handle);
    if (0 == k_hal_i2c_master_read(ignis_pcf8575_ctx.i2c_handle, status, 2))
    {
        ret_code = 0;
    }
    k_osal_mutex_unlock(ignis_pcf8575_ctx.mutex_handle);
    return ret_code;
}

int ignis_pcf8575_set_status(const uint8_t status[2])
{
    int ret_code = -1;
    k_osal_mutex_lock(ignis_pcf8575_ctx.mutex_handle);
    if (0 == k_hal_i2c_master_write(ignis_pcf8575_ctx.i2c_handle, status, 2))
    {
        memcpy(ignis_pcf8575_ctx.pins_state, status, 2);
        ret_code = 0;
    }
    k_osal_mutex_unlock(ignis_pcf8575_ctx.mutex_handle);
    return ret_code;
}