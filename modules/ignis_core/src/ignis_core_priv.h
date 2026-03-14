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
#include <stdint.h>

#include "ignis_keymap.h"
#include "k_osal/timer.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
#define IGNIS_CORE_CONTEXT_INIT()                     \
    {                                                 \
        .state            = IGNIS_CORE_STATE_IDLE,    \
        .display_digits   = {0xFF, 0xFF, 0xFF, 0xFF}, \
        .defuse_code      = {0xFF, 0xFF, 0xFF, 0xFF}, \
        .total_time_min   = 0,                        \
        .buzzing_time_min = 0,                        \
        .elapsed_time_min = 0,                        \
    }
#define IGNIS_CORE_IS_DIGITS_BUFFER_EMPTY()                                                                                                          \
    (ignis_core_context.display_digits[0] == 0xFF && ignis_core_context.display_digits[1] == 0xFF && ignis_core_context.display_digits[2] == 0xFF && \
     ignis_core_context.display_digits[3] == 0xFF)

/* Typedef -------------------------------------------------------------------*/
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
    k_osal_timer_t     timer;              //!< Timer to manage the playtime
    size_t             total_time_min;     //!< Total bomb time in minutes
    size_t             buzzing_time_min;   //!< Buzzing time in minutes
    size_t             elapsed_time_min;   //!< Elapsed time from when the prop has been armed in minutes
    ignis_core_state_t state;              //!< Ignis core current state
    uint8_t            display_digits[4];  //!< Ignis core display digits
    uint8_t            defuse_code[4];     //!< Code to defuse the bomb
} ignis_core_context_t;                    //!< Ignis core context

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

/**
 * @brief Adds a digit to the display buffer, shifting existing digits to the left.
 *
 * This function updates the display buffer managed by the Ignis core context by
 * inserting a new digit at the end of the buffer and shifting all other digits
 * one position to the left. This ensures the buffer always contains the most
 * recent digits, with older digits discarded when the buffer is full.
 *
 * @param digit The digit to add to the display buffer.
 */
void ignis_core_add_digit_to_display_buffer(int8_t digit);

/**
 * @brief Resets the display buffer by setting all elements to their default values.
 *
 * This method clears the display digits buffer by overwriting its contents with a predefined
 * value, typically used to indicate an empty state. It helps ensure the display buffer is in
 * a consistent state, usually after processing or when transitioning between states.
 */
void ignis_core_reset_display_buffer(void);

/**
 * Calculates the total time in minutes based on the input array of digits.
 * The digits array represents a time value in the following format:
 * - digits[3]: minutes (0-9)
 * - digits[2]: tens of minutes (0-9)
 * - digits[1]: hours (0-9)
 * - digits[0]: tens of hours (0-9)
 *
 * @param digits An array of 4 uint8_t values representing minutes and hours as described above.
 * @return The total time in minutes as a size_t value.
 */
size_t ignis_core_calculate_time_min(const uint8_t digits[4]);

#ifdef __cplusplus
}
#endif
#endif  // IGNIS_CORE_PRIV_H
