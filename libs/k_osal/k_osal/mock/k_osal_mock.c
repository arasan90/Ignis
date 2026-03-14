/**
 ********************************************************************************
 * @file    k_osal_mock.c
 * @author  Massimiliano Ianniello
 * @date    20/02/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "k_osal_mock.h"

/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Definitions ------------------------------------------------------*/
DEFINE_FAKE_VALUE_FUNC(int, k_osal_thread_create, k_osal_thread_t *, const char *, k_osal_thread_priority_t, size_t, k_osal_thread_func_t, void *)
DEFINE_FAKE_VOID_FUNC(k_osal_thread_sleep, size_t)
DEFINE_FAKE_VALUE_FUNC(int, k_osal_mutex_create, k_osal_mutex_t *)
DEFINE_FAKE_VOID_FUNC(k_osal_mutex_lock, k_osal_mutex_t)
DEFINE_FAKE_VOID_FUNC(k_osal_mutex_unlock, k_osal_mutex_t)
DEFINE_FAKE_VALUE_FUNC(int, k_osal_signal_create, k_osal_signal_t *)
DEFINE_FAKE_VALUE_FUNC(int, k_osal_signal_wait, k_osal_signal_t, size_t, size_t *, uint8_t, uint8_t, size_t)
DEFINE_FAKE_VALUE_FUNC(int, k_osal_signal_set, k_osal_signal_t, size_t)
DEFINE_FAKE_VALUE_FUNC(int, k_osal_timer_create, k_osal_timer_t *, uint32_t, bool, bool, k_osal_timer_callback_t, void *)
DEFINE_FAKE_VALUE_FUNC(int, k_osal_timer_start, k_osal_timer_t)
DEFINE_FAKE_VALUE_FUNC(int, k_osal_timer_stop, k_osal_timer_t)
DEFINE_FAKE_VALUE_FUNC(int, k_osal_timer_delete, k_osal_timer_t)