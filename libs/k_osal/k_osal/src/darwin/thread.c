/**
 ********************************************************************************
 * @file    thread.c
 * @author  Massimiliano Ianniello
 * @date    28/01/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "k_osal/thread.h"

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "thread_priv.h"
/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Definitions ------------------------------------------------------*/
int k_osal_thread_create(k_osal_thread_t *const thread_handle, const char *const thread_name, const k_osal_thread_priority_t priority, const size_t stack_size,
                         const k_osal_thread_func_t thread_func, void *const param)
{
    int ret_code = -1;
    if (thread_handle && stack_size && thread_func)
    {
        thread_handle->thread_handle = calloc(1, sizeof(k_osal_thread_context_t));
        if (thread_handle->thread_handle)
        {
            k_osal_thread_context_t *k_osal_thread_context = thread_handle->thread_handle;
            k_osal_thread_context->thread_func             = thread_func;
            k_osal_thread_context->param                   = param;
            k_osal_thread_context->thread_name             = thread_name;
            k_osal_thread_context->thread_priority         = priority;
            if (0 == pthread_create(&k_osal_thread_context->thread_handle, NULL, k_osal_thread_func_generic, k_osal_thread_context))
            {
                ret_code = 0;
            }
        }
    }
    return ret_code;
}

void k_osal_thread_sleep(const size_t timeout_ms) { usleep(1000 * timeout_ms); }

void *k_osal_thread_func_generic(void *param)
{
    const k_osal_thread_context_t *ctx = param;
    if (ctx->thread_func)
    {
        printf("Starting thread function\n\r");
        ctx->thread_func(ctx->param);
        printf("Exited from thread function\n\r");
    }
    return NULL;
}
