/**
 ********************************************************************************
 * @file    timer_priv.h
 * @author  Massimiliano Ianniello
 * @date    12/03/26
 ********************************************************************************
 */
#ifndef TIMER_PRIV_H
#define TIMER_PRIV_H

/* Includes ------------------------------------------------------------------*/
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "k_osal/timer.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
typedef struct k_osal_timer_priv_s
{
    TimerHandle_t           timer_handle;
    k_osal_timer_callback_t callback;
    void                   *params;
} k_osal_timer_priv_t;

/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
void k_osal_timer_callback_func(TimerHandle_t timer_handle);

#ifdef __cplusplus
}
#endif
#endif  // TIMER_PRIV_H
