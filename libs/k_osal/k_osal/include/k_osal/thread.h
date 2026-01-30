/**
 ********************************************************************************
 * @file    thread.h
 * @author  Massimiliano Ianniello
 * @date    28/01/26
 ********************************************************************************
 */
#ifndef THREAD_H
#define THREAD_H

/* Includes ------------------------------------------------------------------*/
#include <stddef.h>

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
typedef struct k_osal_thread_s
{
    void *thread_handle;  //!< Opaque, platform-dependant
} k_osal_thread_t;        //!< Thread object

typedef enum k_osal_thread_priority_e
{
    K_OSAL_THREAD_PRIORITY_LOW = 0,  //!< Low priority
    K_OSAL_THREAD_PRIORITY_MEDIUM,   //!< Medium priority
    K_OSAL_THREAD_PRIORITY_HIGH,     //!< High priority
} k_osal_thread_priority_t;          //!< Thread priority

/**
 * @brief Function signature for thread
 *
 * @param param Parameter to pass to thread function
 */
typedef void (*k_osal_thread_func_t)(void *param);
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/**
 * @brief Create and start a new thread
 * @param thread_handle Pointer to store a thread object
 * @param thread_name Thread name
 * @param priority Thread priority
 * @param stack_size Thread stack size in bytes
 * @param thread_func First function called from a thread
 * @param param Parameter to pass to @ref thread_func
 * @return 0 in case of success, -1 otherwise
 */
int k_osal_thread_create(k_osal_thread_t *thread_handle, const char *thread_name, k_osal_thread_priority_t priority, size_t stack_size,
                         k_osal_thread_func_t thread_func, void *param);

/**
 * @brief Put the current thread to sleep
 * @param timeout_ms Sleep time in milliseconds
 */
void k_osal_thread_sleep(size_t timeout_ms);

#ifdef __cplusplus
}
#endif
#endif  // THREAD_H
