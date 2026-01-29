/**
 ********************************************************************************
 * @file    ignis_core_priv.h
 * @author  Massimiliano Ianniello
 * @date    29/01/26
 ********************************************************************************
 */
#ifndef IGNIS_CORE_PRIV_H
#define IGNIS_CORE_PRIV_H

/* Includes ------------------------------------------------------------------*/
#include <stddef.h>
#include <stdint.h>

#include "ignis_keymap.h"
#include "k_osal/thread.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
typedef enum ignis_core_state_e
{
    IGNIS_CORE_STATE_IDLE,
    IGNIS_CORE_STATE_PROGRAMMING_TOTAL_TIME,
    IGNIS_CORE_STATE_PROGRAMMING_BUZZER_TIME,
    IGNIS_CORE_STATE_PROGRAMMING_CODE,
    IGNIS_CORE_STATE_READY_TO_BE_ARMED,
    IGNIS_CORE_STATE_ARMED
} ignis_core_state_t;

typedef struct ignis_core_context_s
{
    k_osal_thread_t    thread;                 //!< Ignis core thread handle
    ignis_core_state_t state;                  //!< Ignis core current state
    size_t             total_time_sec;         //!< Total time
    size_t             buzzer_time_sec;        //!< Time for repetitive buzzer alarm
    size_t             code;                   //!< Code to set the prop off
    uint8_t            total_time_digits[4];   //!< @ref total_time_sec expressed in digits
    uint8_t            buzzer_time_digits[4];  //!< @ref buzzer_time_sec expressed in digits
    uint8_t            code_digits[4];         //!< @ref code expressed in digits
    uint8_t            current_digit;          //!< Current digit to set in the programming phase
} ignis_core_context_t;                        //!< Ignis core context

extern ignis_core_context_t ignis_core_context;

/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/**
 * @brief Ignis core thread function
 * @param param User context
 */
void ignis_core_thread_function(void *param);

/**
 * @brief Callback function for ignis_keymap module
 * @param key Pressed key
 */
void ignis_core_keymap_callback(ignis_keymap_key_t key);

#ifdef __cplusplus
}
#endif
#endif  // IGNIS_CORE_PRIV_H
