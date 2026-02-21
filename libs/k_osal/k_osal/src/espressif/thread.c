/**
 ********************************************************************************
 * @file    thread.c
 * @author  Massimiliano Ianniello
 * @date    28/01/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "k_osal/thread.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Definitions ------------------------------------------------------*/
int k_osal_thread_create(k_osal_thread_t *const thread_handle, const char *const thread_name, const k_osal_thread_priority_t priority, const size_t stack_size,
                         const k_osal_thread_func_t thread_func, void *const param)
{
    const UBaseType_t freeRTOS_priority = (configMAX_PRIORITIES / 3) * ((uint8_t)priority + 1);
    return pdPASS == xTaskCreate(thread_func, thread_name, stack_size, param, freeRTOS_priority, thread_handle->thread_handle) ? 0 : -1;
}
void k_osal_thread_sleep(const size_t timeout_ms) { vTaskDelay(timeout_ms / portTICK_PERIOD_MS); }