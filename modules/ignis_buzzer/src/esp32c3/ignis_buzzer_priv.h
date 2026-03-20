/**
 ********************************************************************************
 * @file    ignis_buzzer_priv.h
 * @author  Massimiliano Ianniello
 * @date    20/03/26
 ********************************************************************************
 */
#ifndef IGNIS_BUZZER_PRIV_H
#define IGNIS_BUZZER_PRIV_H

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "k_osal/timer.h"
#include "k_hal/k_hal_gpio.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {



#endif

/* Typedefs ------------------------------------------------------------------*/
typedef struct ignis_buzzer_context_s
{
    k_osal_timer_t timer;
    k_hal_gpio_t buzzer_gpio;
    bool initialized;
} ignis_buzzer_context_t;

/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/

void ignis_buzzer_timer_elapsed_cb(void* param);

#ifdef __cplusplus
}
#endif
#endif //IGNIS_BUZZER_PRIV_H
