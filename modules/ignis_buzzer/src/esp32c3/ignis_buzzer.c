/**
 ********************************************************************************
 * @file    ignis_buzzer.c
 * @author  Massimiliano Ianniello
 * @date    20/03/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "ignis_buzzer.h"
#include "ignis_buzzer_priv.h"
#include <stdio.h>
#include <stdlib.h>

/* Macros --------------------------------------------------------------------*/
#define IGNIS_BUZZER_GPIO_NUM (7)

/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
ignis_buzzer_context_t ignis_buzzer_context = {0};

/* Function Definitions ------------------------------------------------------*/
void ignis_buzzer_start(void)
{
    if (!ignis_buzzer_context.initialized)
    {
        k_osal_timer_create(&ignis_buzzer_context.timer, 500, false, false, ignis_buzzer_timer_elapsed_cb, NULL);
        k_hal_gpio_create(&ignis_buzzer_context.buzzer_gpio, IGNIS_BUZZER_GPIO_NUM, K_HAL_GPIO_DIRECTION_OUTPUT,
                          K_HAL_GPIO_LEVEL_LOW, false, true);
        ignis_buzzer_context.initialized = true;
    }
}

void ignis_buzzer_sound_short_alarm(void)
{
    k_hal_gpio_set_level(&ignis_buzzer_context.buzzer_gpio, K_HAL_GPIO_LEVEL_HIGH);
    k_osal_timer_start(ignis_buzzer_context.timer);
}

void ignis_buzzer_sound_long_alarm(void)
{
    k_hal_gpio_set_level(&ignis_buzzer_context.buzzer_gpio, K_HAL_GPIO_LEVEL_HIGH);
}

void ignis_buzzer_alarm_shutoff(void)
{
    k_hal_gpio_set_level(&ignis_buzzer_context.buzzer_gpio, K_HAL_GPIO_LEVEL_LOW);
    k_osal_timer_stop(ignis_buzzer_context.timer);
}

void ignis_buzzer_timer_elapsed_cb(void* param)
{
    (void)param;
    k_hal_gpio_set_level(&ignis_buzzer_context.buzzer_gpio, K_HAL_GPIO_LEVEL_LOW);
}
