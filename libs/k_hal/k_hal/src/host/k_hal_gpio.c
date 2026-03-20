/**
 ********************************************************************************
 * @file    k_hal_gpio.c
 * @author  Massimiliano Ianniello
 * @date    20/03/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "k_hal/k_hal_gpio.h"

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
    (void)gpio_handle_p;
    (void)gpio_num;
    (void)direction;
    (void)initial_level;
    (void)pullup_enable;
    (void)pulldown_enable;
    return 0;
}

void k_hal_gpio_set_level(k_hal_gpio_t* const gpio_handle_p, const k_hal_gpio_level_t gpio_level)
{
    (void)gpio_handle_p;
    (void)gpio_level;
}
