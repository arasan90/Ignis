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
#include <signal.h>

#include "k_osal/timer.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
typedef struct k_osal_timer_priv_s
{
    timer_t                 timer_id;
    uint32_t                period_ms;
    bool                    periodic;
    bool                    started;
    k_osal_timer_callback_t callback;
    void                   *params;
} k_osal_timer_priv_t;

/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
void k_osal_timer_callback_func(union sigval timer_data);

#ifdef __cplusplus
}
#endif
#endif  // TIMER_PRIV_H
