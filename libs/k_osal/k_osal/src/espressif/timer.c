/**
 ********************************************************************************
 * @file    timer.c
 * @author  Massimiliano Ianniello
 * @date    14/03/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "k_osal/timer.h"

#include "timer_priv.h"

/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Definitions ------------------------------------------------------*/
int k_osal_timer_create(k_osal_timer_t* const timer, const uint32_t timer_period, const bool periodic,
                        const bool auto_start,
                        const k_osal_timer_callback_t callback, void* const params)
{
    int ret_code = -1;
    if (timer && callback)
    {
        timer->timer_handle = calloc(1, sizeof(k_osal_timer_priv_t));
        if (timer->timer_handle)
        {
            k_osal_timer_priv_t* timer_priv = timer->timer_handle;
            timer_priv->timer_handle = xTimerCreate("", pdMS_TO_TICKS(timer_period), periodic ? pdTRUE : pdFALSE,
                                                    timer_priv, k_osal_timer_callback_func);
            if (timer_priv->timer_handle)
            {
                timer_priv->callback = callback;
                timer_priv->params = params;
                ret_code = 0;
                if (auto_start)
                {
                    if (pdPASS != xTimerStart(timer_priv->timer_handle, 0))
                    {
                        ret_code = -1;
                    }
                }
            }
        }
    }
    return ret_code;
}

int k_osal_timer_start(const k_osal_timer_t timer)
{
    int ret_code = 0;

    const k_osal_timer_priv_t* timer_priv = timer.timer_handle;
    if (pdFALSE == xTimerIsTimerActive(timer_priv->timer_handle))
    {
        if (pdFAIL == xTimerStart(timer_priv->timer_handle, 0))
        {
            ret_code = -1;
        }
    }
    return ret_code;
}

int k_osal_timer_stop(const k_osal_timer_t timer)
{
    int ret_code = 0;

    const k_osal_timer_priv_t* timer_priv = timer.timer_handle;
    if (pdTRUE == xTimerIsTimerActive(timer_priv->timer_handle))
    {
        if (pdFAIL == xTimerStop(timer_priv->timer_handle, 0))
        {
            ret_code = -1;
        }
    }
    return ret_code;
}

int k_osal_timer_set_period(const k_osal_timer_t timer, const uint32_t period_ms)
{
    int ret_code = -1;
    k_osal_timer_priv_t* timer_priv = timer.timer_handle;
    if (ESP_OK == xTimerStop(timer_priv->timer_handle, 0) && ESP_OK == xTimerChangePeriod(
        timer_priv->timer_handle, pdMS_TO_TICKS(period_ms), 0) && ESP_OK == xTimerStop(timer_priv->timer_handle, 0))
    {
        ret_code = 0;
    }
    return ret_code;
}

int k_osal_timer_delete(const k_osal_timer_t timer)
{
    int ret_code = -1;

    k_osal_timer_priv_t* timer_priv = timer.timer_handle;
    if (pdTRUE == xTimerDelete(timer_priv->timer_handle, 0))
    {
        free(timer_priv);
        ret_code = 0;
    }
    return ret_code;
}

void k_osal_timer_callback_func(TimerHandle_t timer_handle)
{
    const k_osal_timer_priv_t* timer_priv = pvTimerGetTimerID(timer_handle);
    if (timer_priv->callback)
    {
        timer_priv->callback(timer_priv->params);
    }
}
