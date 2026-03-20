/**
 ********************************************************************************
 * @file    timer.c
 * @author  Massimiliano Ianniello
 * @date    12/03/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "k_osal/timer.h"

#include "dispatch/dispatch.h"
#include "timer_priv.h"

/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
static dispatch_queue_t timer_queue = NULL;

/* Function Definitions ------------------------------------------------------*/

int k_osal_timer_create(k_osal_timer_t* const timer, const uint32_t timer_period, const bool periodic,
                        const bool auto_start,
                        const k_osal_timer_callback_t callback, void* const params)
{
    int ret_code = -1;
    if (!timer_queue)
    {
        timer_queue = dispatch_queue_create("k_timer_queue", DISPATCH_QUEUE_SERIAL);
    }
    if (timer && callback)
    {
        timer->timer_handle = calloc(1, sizeof(k_osal_timer_priv_t));
        if (timer->timer_handle)
        {
            k_osal_timer_priv_t* timer_priv = timer->timer_handle;
            timer_priv->period_ms = timer_period;
            timer_priv->periodic = periodic;
            timer_priv->params = params;
            timer_priv->callback = callback;
            timer_priv->timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, timer_queue);
            if (timer_priv->timer)
            {
                dispatch_source_set_event_handler_f(timer_priv->timer, (dispatch_function_t)callback);
                if (auto_start)
                {
                    const uint64_t interval_ns = (uint64_t)timer_period * 1000000ULL;
                    dispatch_source_set_timer(timer_priv->timer, dispatch_time(DISPATCH_TIME_NOW, (int64_t)interval_ns),
                                              periodic ? interval_ns : DISPATCH_TIME_FOREVER, 0);
                    dispatch_resume((struct _os_object_s*)timer_priv->timer);
                    timer_priv->started = true;
                }
                ret_code = 0;
            }
        }
    }
    return ret_code;
}

int k_osal_timer_start(const k_osal_timer_t timer)
{
    k_osal_timer_priv_t* timer_priv = timer.timer_handle;
    if (!timer_priv->started)
    {
        const uint64_t interval_ns = (uint64_t)timer_priv->period_ms * 1000000ULL;
        dispatch_source_set_timer(timer_priv->timer, dispatch_time(DISPATCH_TIME_NOW, (int64_t)interval_ns),
                                  timer_priv->periodic ? interval_ns : DISPATCH_TIME_FOREVER, 0);
        dispatch_resume((struct _os_object_s*)timer_priv->timer);
        timer_priv->started = true;
    }
    return 0;
}

int k_osal_timer_stop(const k_osal_timer_t timer)
{
    k_osal_timer_priv_t* timer_priv = timer.timer_handle;
    if (timer_priv->started)
    {
        dispatch_suspend((struct _os_object_s*)timer_priv->timer);
        timer_priv->started = false;
    }
    return 0;
}

int k_osal_timer_set_period(const k_osal_timer_t timer, const uint32_t period_ms)
{
    k_osal_timer_priv_t* timer_priv = timer.timer_handle;
    k_osal_timer_stop(timer);
    timer_priv->period_ms = period_ms;
    return 0;
}

int k_osal_timer_delete(k_osal_timer_t timer)
{
    k_osal_timer_priv_t* timer_priv = timer.timer_handle;
    if (timer_priv->started)
    {
        dispatch_suspend((struct _os_object_s*)timer_priv->timer);
    }
    dispatch_release((struct _os_object_s*)timer_priv->timer);
    free(timer_priv);
    return 0;
}

void k_osal_timer_callback_func(void* const param)
{
    const k_osal_timer_t* context = param;
    if (context)
    {
        const k_osal_timer_priv_t* timer_priv = context->timer_handle;
        if (timer_priv && timer_priv->callback)
        {
            timer_priv->callback(timer_priv->params);
        }
    }
}
