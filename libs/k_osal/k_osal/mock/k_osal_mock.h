/**
 ********************************************************************************
 * @file    k_osal_mock.h
 * @author  Massimiliano Ianniello
 * @date    20/02/26
 ********************************************************************************
 */
#ifndef K_OSAL_MOCK_H
#define K_OSAL_MOCK_H

/* Includes ------------------------------------------------------------------*/
#include "fff.h"
#include "k_osal/mutex.h"
#include "k_osal/thread.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
DECLARE_FAKE_VALUE_FUNC(int, k_osal_thread_create, k_osal_thread_t *, const char *, k_osal_thread_priority_t,  size_t,  k_osal_thread_func_t, void *)
DECLARE_FAKE_VOID_FUNC(k_osal_thread_sleep, size_t)
DECLARE_FAKE_VALUE_FUNC(int, k_osal_mutex_create, k_osal_mutex_t *)
DECLARE_FAKE_VOID_FUNC(k_osal_mutex_lock, k_osal_mutex_t )
DECLARE_FAKE_VOID_FUNC(k_osal_mutex_unlock, k_osal_mutex_t )

inline void k_osal_mock_reset(void)
{
    RESET_FAKE(k_osal_thread_create);
    RESET_FAKE(k_osal_thread_sleep);
    RESET_FAKE(k_osal_mutex_create);
    RESET_FAKE(k_osal_mutex_lock);
    RESET_FAKE(k_osal_mutex_unlock);
}

#ifdef __cplusplus
}
#endif
#endif  // K_OSAL_MOCK_H
