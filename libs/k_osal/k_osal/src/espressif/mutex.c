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

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

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
        mutex_handle->mutex_handle = xSemaphoreCreateRecursiveMutex();
        ret_code                   = NULL != mutex_handle->mutex_handle ? 0 : -1;
    }
    return ret_code;
}

void k_osal_mutex_lock(const k_osal_mutex_t mutex_handle) { xSemaphoreTakeRecursive(mutex_handle.mutex_handle, portMAX_DELAY); }

void k_osal_mutex_unlock(const k_osal_mutex_t mutex_handle) { xSemaphoreGiveRecursive(mutex_handle.mutex_handle); }
