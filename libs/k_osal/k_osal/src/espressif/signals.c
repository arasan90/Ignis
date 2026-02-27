/**
 ********************************************************************************
 * @file    signals.c
 * @author  Massimiliano Ianniello
 * @date    27/02/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "k_osal/signals.h"

#include <signal.h>

#include "signals_priv.h"

/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Definitions ------------------------------------------------------*/
int k_osal_signal_create(k_osal_signal_t *signal_handle)
{
    int ret_code = -1;
    if (signal_handle)
    {
        signal_handle->handle = calloc(sizeof(k_osal_signal_context_t), 1);
        if (signal_handle->handle)
        {
            k_osal_signal_context_t *signal = signal_handle->handle;
            signal->event_group             = xEventGroupCreate();
            ret_code                        = signal->event_group ? 0 : -1;
        }
    }
    return ret_code;
}

int k_osal_signal_wait(k_osal_signal_t signal_handle, size_t mask, size_t *received_signals, uint8_t wait_all, uint8_t clear, size_t timeout_ms)
{
    int ret_code = -1;
    if (signal_handle.handle && received_signals)
    {
        TickType_t                     timeout_ticks = portMAX_DELAY;
        EventBits_t                    bits          = 0;
        const k_osal_signal_context_t *signal        = signal_handle.handle;
        if (K_OSAL_SIGNAL_WAIT_FOREVER != timeout_ms)
        {
            timeout_ticks = pdMS_TO_TICKS(timeout_ms);
        }
        bits = xEventGroupWaitBits(signal->event_group, mask, clear, wait_all, timeout_ticks);
        if ((wait_all && (bits == mask)) || (!wait_all && (bits & mask)))
        {
            ret_code = 1;
        }
        else
        {
            ret_code = 0;
        }
        *received_signals = bits;
    }
    return ret_code;
}

int k_osal_signal_set(k_osal_signal_t signal_handle, size_t mask)
{
    int ret_code = -1;
    if (signal_handle.handle)
    {
        const k_osal_signal_context_t *signal = signal_handle.handle;
        if (pdPASS == xEventGroupSetBits(signal->event_group, mask))
        {
            ret_code = 0;
        }
    }
    return ret_code;
}
