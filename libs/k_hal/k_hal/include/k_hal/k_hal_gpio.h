/**
 ********************************************************************************
 * @file    k_hal_gpio.h
 * @author  Massimiliano Ianniello
 * @date    20/03/26
 ********************************************************************************
 */
#ifndef K_HAL_GPIO_H
#define K_HAL_GPIO_H

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {



#endif
/* Typedefs ------------------------------------------------------------------*/
typedef enum k_hal_gpio_direction_e
{
    K_HAL_GPIO_DIRECTION_INPUT = 0,
    K_HAL_GPIO_DIRECTION_OUTPUT = 1,
} k_hal_gpio_direction_t;

typedef enum k_hal_gpio_level_e
{
    K_HAL_GPIO_LEVEL_LOW = 0,
    K_HAL_GPIO_LEVEL_HIGH = 1,
} k_hal_gpio_level_t;

typedef struct k_hal_gpio_s
{
    k_hal_gpio_direction_t direction;
    k_hal_gpio_level_t level;
    uint8_t gpio_num;
} k_hal_gpio_t;

/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
int k_hal_gpio_create(k_hal_gpio_t* gpio_handle_p, uint8_t gpio_num, k_hal_gpio_direction_t direction,
                      k_hal_gpio_level_t initial_level,
                      bool pullup_enable, bool pulldown_enable);
void k_hal_gpio_set_level(k_hal_gpio_t* gpio_handle_p, k_hal_gpio_level_t gpio_level);

#ifdef __cplusplus
}
#endif
#endif //K_HAL_GPIO_H
