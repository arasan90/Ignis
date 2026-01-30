/**
 ********************************************************************************
 * @file    thread_priv.h
 * @author  Massimiliano Ianniello
 * @date    28/01/26
 ********************************************************************************
 */
#ifndef THREAD_PRIV_H
#define THREAD_PRIV_H

/* Includes ------------------------------------------------------------------*/
#include "k_osal/thread.h"
#include "pthread.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
typedef struct k_osal_thread_context_s
{
    k_osal_thread_func_t     thread_func;
    pthread_t                thread_handle;
    void                    *param;
    const char              *thread_name;
    k_osal_thread_priority_t thread_priority;
} k_osal_thread_context_t;

/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
void *k_osal_thread_func_generic(void *param);

#ifdef __cplusplus
}
#endif
#endif  // THREAD_PRIV_H
