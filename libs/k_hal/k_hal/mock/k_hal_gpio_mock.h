/**
 ********************************************************************************
 * @file    k_hal_gpio_mock.h
 * @author  Massimiliano Ianniello
 * @date    20/03/26
 ********************************************************************************
 */
#ifndef K_HAL_GPIO_MOCK_H
#define K_HAL_GPIO_MOCK_H

/* Includes ------------------------------------------------------------------*/
#include "fff.h"
#include "k_hal/k_hal_gpio.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {



#endif
/* Typedefs ------------------------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
DECLARE_FAKE_VALUE_FUNC(int, k_hal_gpio_create, k_hal_gpio_t *, uint8_t, k_hal_gpio_direction_t, k_hal_gpio_level_t,
                        bool, bool)
DECLARE_FAKE_VOID_FUNC(k_hal_gpio_set_level, k_hal_gpio_t *, k_hal_gpio_level_t)

inline void k_hal_gpio_reset(void)
{
    RESET_FAKE(k_hal_gpio_create);
    RESET_FAKE(k_hal_gpio_set_level);
}
#ifdef __cplusplus
}
#endif
#endif //K_HAL_GPIO_MOCK_H
