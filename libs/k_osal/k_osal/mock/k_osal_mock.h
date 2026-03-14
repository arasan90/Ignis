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
#include "k_osal/signals.h"
#include "k_osal/thread.h"
#include "k_osal/timer.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
DECLARE_FAKE_VALUE_FUNC(int, k_osal_thread_create, k_osal_thread_t *, const char *, k_osal_thread_priority_t, size_t, k_osal_thread_func_t, void *)
DECLARE_FAKE_VOID_FUNC(k_osal_thread_sleep, size_t)
DECLARE_FAKE_VALUE_FUNC(int, k_osal_mutex_create, k_osal_mutex_t *)
DECLARE_FAKE_VOID_FUNC(k_osal_mutex_lock, k_osal_mutex_t)
DECLARE_FAKE_VOID_FUNC(k_osal_mutex_unlock, k_osal_mutex_t)
DECLARE_FAKE_VALUE_FUNC(int, k_osal_signal_create, k_osal_signal_t *)
DECLARE_FAKE_VALUE_FUNC(int, k_osal_signal_wait, k_osal_signal_t, size_t, size_t *, uint8_t, uint8_t, size_t)
DECLARE_FAKE_VALUE_FUNC(int, k_osal_signal_set, k_osal_signal_t, size_t)
DECLARE_FAKE_VALUE_FUNC(int, k_osal_timer_create, k_osal_timer_t *, uint32_t, bool, bool, k_osal_timer_callback_t, void *)
DECLARE_FAKE_VALUE_FUNC(int, k_osal_timer_start, k_osal_timer_t)
DECLARE_FAKE_VALUE_FUNC(int, k_osal_timer_stop, k_osal_timer_t)
DECLARE_FAKE_VALUE_FUNC(int, k_osal_timer_delete, k_osal_timer_t)

inline void k_osal_mock_reset(void)
{
    RESET_FAKE(k_osal_thread_create);
    RESET_FAKE(k_osal_thread_sleep);
    RESET_FAKE(k_osal_mutex_create);
    RESET_FAKE(k_osal_mutex_lock);
    RESET_FAKE(k_osal_mutex_unlock);
    RESET_FAKE(k_osal_signal_create);
    RESET_FAKE(k_osal_signal_wait)
    RESET_FAKE(k_osal_signal_set);
    RESET_FAKE(k_osal_timer_create);
    RESET_FAKE(k_osal_timer_start);
    RESET_FAKE(k_osal_timer_stop);
    RESET_FAKE(k_osal_timer_delete);
}

#ifdef __cplusplus
}
#endif
#endif  // K_OSAL_MOCK_H
