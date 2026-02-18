/**
 ********************************************************************************
 * @file    k_hal_i2c_master.c
 * @author  Massimiliano Ianniello
 * @date    18/02/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "k_hal/k_hal_i2c_master.h"

#include "k_hal_i2c_master_priv.h"

/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
#define K_HAL_I2C_MASTER_SDA_PIN (8)
#define K_HAL_I2C_MASTER_SCL_PIN (9)

/* Variables -----------------------------------------------------------------*/
k_hal_i2c_master_ctx_t k_hal_i2c_master_ctx = {0};

/* Function Definitions ------------------------------------------------------*/
void k_hal_i2c_master_init(void)
{
    if (!k_hal_i2c_master_ctx.initialized)
    {
        const i2c_master_bus_config_t i2c_mst_config = {
            .clk_source                   = I2C_CLK_SRC_DEFAULT,
            .i2c_port                     = -1,
            .scl_io_num                   = K_HAL_I2C_MASTER_SCL_PIN,
            .sda_io_num                   = K_HAL_I2C_MASTER_SDA_PIN,
            .glitch_ignore_cnt            = 7,
            .flags.enable_internal_pullup = true,
        };
        ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &k_hal_i2c_master_ctx.bus_handle));
        k_hal_i2c_master_ctx.initialized = true;
    }
}

int k_hal_i2c_master_add_device(k_hal_i2c_master_device_handle_t* const handle_p, const uint8_t address, const size_t speed_hz)
{
    int ret_code = -1;
    if (k_hal_i2c_master_ctx.initialized)
    {
        i2c_device_config_t dev_cfg = {
            .dev_addr_length = I2C_ADDR_BIT_LEN_7,
            .device_address  = address,
            .scl_speed_hz    = speed_hz,
        };
        esp_err_t error = i2c_master_probe(k_hal_i2c_master_ctx.bus_handle, address, 1000);
        if (ESP_OK == error)
        {
            handle_p->handle = calloc(sizeof(i2c_master_dev_handle_t), 1);
            error            = i2c_master_bus_add_device(k_hal_i2c_master_ctx.bus_handle, &dev_cfg, handle_p->handle);
        }
        if (ESP_OK == error)
        {
            ret_code = 0;
        }
    }
    return ret_code;
}

int k_hal_i2c_master_read(const k_hal_i2c_master_device_handle_t handle, uint8_t* const data_p, const size_t length)
{
    int ret_code = -1;
    if (handle.handle && data_p && length > 0)
    {
        const i2c_master_dev_handle_t* dev_handle = (i2c_master_dev_handle_t*)handle.handle;
        if (ESP_OK == i2c_master_receive(*dev_handle, data_p, length, 1000))
        {
            ret_code = 0;
        }
    }
    return ret_code;
}

int k_hal_i2c_master_write(const k_hal_i2c_master_device_handle_t handle, const uint8_t* const data_p, const size_t length)
{
    int ret_code = -1;
    if (handle.handle && data_p && length > 0)
    {
        const i2c_master_dev_handle_t* dev_handle = (i2c_master_dev_handle_t*)handle.handle;
        if (ESP_OK == i2c_master_transmit(*dev_handle, data_p, length, 1000))
        {
            ret_code = 0;
        }
    }
    return ret_code;
}