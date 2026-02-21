/**
 ********************************************************************************
 * @file    mutex.c
 * @author  Massimiliano Ianniello
 * @date    20/02/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "k_osal/mutex.h"

#include <stdlib.h>

#include "mutex_priv.h"

/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Definitions ------------------------------------------------------*/
int k_osal_mutex_create(k_osal_mutex_t *const mutex_handle)
{
    int ret_code = -1;
    if (mutex_handle)
    {
        mutex_handle->mutex_handle = calloc(sizeof(k_osal_mutex_context_t), 1);
        if (mutex_handle->mutex_handle)
        {
            k_osal_mutex_context_t *mutex_context = mutex_handle->mutex_handle;
            pthread_mutexattr_t     mutex_attr;
            pthread_mutexattr_init(&mutex_attr);
            pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_RECURSIVE);
            if (0 == pthread_mutex_init(&mutex_context->mutex, NULL))
            {
                ret_code = 0;
            }
            pthread_mutexattr_destroy(&mutex_attr);
        }
    }
    return ret_code;
}

void k_osal_mutex_lock(const k_osal_mutex_t mutex_handle) { pthread_mutex_lock(mutex_handle.mutex_handle); }

void k_osal_mutex_unlock(const k_osal_mutex_t mutex_handle) { pthread_mutex_unlock(mutex_handle.mutex_handle); }
