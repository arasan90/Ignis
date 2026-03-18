/**
 ********************************************************************************
 * @file    timer.c
 * @author  Massimiliano Ianniello
 * @date    12/03/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "k_osal/timer.h"

#include <stdlib.h>
#include <time.h>

#include "timer_priv.h"

/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Definitions ------------------------------------------------------*/

int k_osal_timer_create(k_osal_timer_t *const timer, const uint32_t timer_period, const bool periodic, const bool auto_start,
                        const k_osal_timer_callback_t callback, void *const params)
{
    int ret_code = -1;
    if (timer && callback && timer_period > 0)
    {
        timer->timer_handle = calloc(1, sizeof(k_osal_timer_priv_t));
        if (timer->timer_handle)
        {
            k_osal_timer_priv_t *timer_priv = timer->timer_handle;
            struct sigevent      sev        = {0};
            timer_priv->period_ms           = timer_period;
            timer_priv->periodic            = periodic;
            timer_priv->params              = params;
            timer_priv->callback            = callback;
            sev.sigev_notify                = SIGEV_THREAD;
            sev.sigev_notify_function       = k_osal_timer_callback_func;
            sev.sigev_value.sival_ptr       = timer_priv;
            if (0 == timer_create(CLOCK_REALTIME, &sev, &timer_priv->timer_id))
            {
                if (auto_start)
                {
                    struct itimerspec its = {
                        .it_value.tv_sec     = timer_period / 1000,
                        .it_value.tv_nsec    = (timer_period % 1000) * 1000000,
                        .it_interval.tv_sec  = 0,
                        .it_interval.tv_nsec = 0,
                    };
                    if (periodic)
                    {
                        its.it_interval.tv_sec  = timer_period / 1000;
                        its.it_interval.tv_nsec = (timer_period % 1000) * 1000000;
                    }
                    if (0 == timer_settime(timer_priv->timer_id, 0, &its, NULL))
                    {
                        timer_priv->started = true;
                        ret_code            = 0;
                    }
                }
            }
        }
    }
    return ret_code;
}

int k_osal_timer_start(const k_osal_timer_t timer)
{
    k_osal_timer_priv_t *timer_priv = timer.timer_handle;
    int                  ret_code   = 0;
    if (!timer_priv->started)
    {
        ret_code              = -1;
        struct itimerspec its = {
            .it_value.tv_sec     = timer_priv->period_ms / 1000,
            .it_value.tv_nsec    = (timer_priv->period_ms % 1000) * 1000000,
            .it_interval.tv_sec  = 0,
            .it_interval.tv_nsec = 0,
        };
        if (timer_priv->periodic)
        {
            its.it_interval.tv_sec  = timer_priv->period_ms / 1000;
            its.it_interval.tv_nsec = (timer_priv->period_ms % 1000) * 1000000;
        }
        if (0 == timer_settime(timer_priv->timer_id, 0, &its, NULL))
        {
            ret_code            = 0;
            timer_priv->started = true;
        }
    }
    return ret_code;
}

int k_osal_timer_stop(const k_osal_timer_t timer)
{
    k_osal_timer_priv_t *timer_priv = timer.timer_handle;
    int                  ret_code   = 0;
    if (!timer_priv->started)
    {
        ret_code              = -1;
        struct itimerspec its = {
            .it_value.tv_sec     = 0,
            .it_value.tv_nsec    = 0,
            .it_interval.tv_sec  = 0,
            .it_interval.tv_nsec = 0,
        };
        if (0 == timer_settime(timer_priv->timer_id, 0, &its, NULL))
        {
            ret_code            = 0;
            timer_priv->started = false;
        }
    }
    return ret_code;
}

int k_osal_timer_delete(k_osal_timer_t timer)
{
    k_osal_timer_priv_t *timer_priv = timer.timer_handle;
    timer_delete(timer_priv->timer_id);
    free(timer_priv);
    return 0;
}

void k_osal_timer_callback_func(union sigval timer_data)
{
    const k_osal_timer_priv_t *timer_priv = timer_data.sival_ptr;
    if (timer_priv)
    {
        if (timer_priv && timer_priv->callback)
        {
            timer_priv->callback(timer_priv->params);
        }
    }
}
