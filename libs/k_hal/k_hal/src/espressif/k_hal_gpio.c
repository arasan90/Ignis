/**
 ********************************************************************************
 * @file    k_hal_gpio.c
 * @author  Massimiliano Ianniello
 * @date    20/03/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "k_hal/k_hal_gpio.h"
#include "driver/gpio.h"

/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Definitions ------------------------------------------------------*/
int k_hal_gpio_create(k_hal_gpio_t* const gpio_handle_p, const uint8_t gpio_num, const k_hal_gpio_direction_t direction,
                      const k_hal_gpio_level_t initial_level,
                      const bool pullup_enable, const bool pulldown_enable)
{
    int ret_code = -1;
    if (gpio_handle_p)
    {
        gpio_config_t io_conf = {0};
        io_conf.intr_type = GPIO_INTR_DISABLE;
        io_conf.mode = K_HAL_GPIO_DIRECTION_OUTPUT == direction ? GPIO_MODE_OUTPUT : GPIO_MODE_INPUT;
        io_conf.pin_bit_mask = 1 << gpio_num;
        io_conf.pull_down_en = pulldown_enable;
        io_conf.pull_up_en = pullup_enable;
        if (ESP_OK == gpio_config(&io_conf))
        {
            gpio_set_level(gpio_num, initial_level);
            gpio_handle_p->direction = direction;
            gpio_handle_p->gpio_num = gpio_num;
            gpio_handle_p->level = initial_level;
            ret_code = 0;
        }
    }
    return ret_code;
}

void k_hal_gpio_set_level(k_hal_gpio_t* const gpio_handle_p, const k_hal_gpio_level_t gpio_level)
{
    if (ESP_OK == gpio_set_level(gpio_handle_p->gpio_num, gpio_level))
    {
        gpio_handle_p->level = gpio_level;
    }
}
