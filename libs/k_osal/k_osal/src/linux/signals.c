/**
 ********************************************************************************
 * @file    signals.c
 * @author  Massimiliano Ianniello
 * @date    27/02/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "k_osal/signals.h"

#include <stdlib.h>
#include <sys/errno.h>
#include <sys/time.h>

#include "signals_priv.h"

/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Definitions ------------------------------------------------------*/
int k_osal_signal_create(k_osal_signal_t* signal_handle)
{
    int ret_code = -1;
    if (signal_handle)
    {
        signal_handle->handle = calloc(sizeof(k_osal_signal_context_t), 1);
        if (signal_handle->handle)
        {
            k_osal_signal_context_t* handle = signal_handle->handle;
            pthread_mutex_init(&handle->mutex, NULL);
            pthread_cond_init(&handle->cond, NULL);
            handle->signals = 0;
            ret_code        = 0;
        }
    }
    return ret_code;
}

int k_osal_signal_wait(k_osal_signal_t signal_handle, size_t mask, size_t* received_signals, uint8_t wait_all, uint8_t clear, size_t timeout_ms)
{
#define CHECK_COND() (wait_all ? ((signal->signals & mask) == mask) : (signal->signals & mask))
    if (!received_signals || !signal_handle.handle)
    {
        return -1;
    }
    k_osal_signal_context_t* signal   = signal_handle.handle;
    int                      ret_code = 0;
    struct timespec          ts;

    if (timeout_ms != K_OSAL_SIGNAL_WAIT_FOREVER && timeout_ms != K_OSAL_SIGNAL_NO_WAIT)
    {
        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += timeout_ms / 1000;
        ts.tv_nsec += (timeout_ms % 1000) * 1000000;
        if (ts.tv_nsec >= 1000000000)
        {
            ts.tv_sec += 1;
            ts.tv_nsec -= 1000000000;
        }
    }

    pthread_mutex_lock(&signal->mutex);

    if (timeout_ms == K_OSAL_SIGNAL_NO_WAIT)
    {
        if (!CHECK_COND())
            ret_code = 0;
        else
            ret_code = 1;
    }
    else
    {
        while (!CHECK_COND())
        {
            if (timeout_ms == K_OSAL_SIGNAL_WAIT_FOREVER)
            {
                pthread_cond_wait(&signal->cond, &signal->mutex);
            }
            else
            {
                int err = pthread_cond_timedwait(&signal->cond, &signal->mutex, &ts);
                if (err != 0)
                {
                    ret_code = (err == ETIMEDOUT) ? 0 : -1;
                    goto exit;
                }
            }
        }
        ret_code = 1;
    }

exit:
    *received_signals = signal->signals & mask;
    if (ret_code > 0 && clear)
    {
        signal->signals &= ~(*received_signals);
    }

    pthread_mutex_unlock(&signal->mutex);
    return ret_code;
}

int k_osal_signal_set(k_osal_signal_t signal_handle, size_t mask)
{
    int ret_code = -1;
    if (signal_handle.handle)
    {
        k_osal_signal_context_t* signal = signal_handle.handle;
        pthread_mutex_lock(&signal->mutex);
        signal->signals |= mask;
        if (0 == pthread_cond_signal(&signal->cond))
        {
            ret_code = 0;
        }
        pthread_mutex_unlock(&signal->mutex);
    }
    return ret_code;
}
