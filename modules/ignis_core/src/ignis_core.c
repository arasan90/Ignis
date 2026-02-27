/**
 ********************************************************************************
 * @file    ignis_core.c
 * @author  Massimiliano Ianniello
 * @date    28/01/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "ignis_core.h"

#include <stdio.h>
#include <string.h>

#include "ignis_core_priv.h"
#include "ignis_display.h"
#include "ignis_keymap.h"

/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
const size_t ignis_core_thread_sleep_time_ms = 50;

/* Variables -----------------------------------------------------------------*/
ignis_core_context_t ignis_core_context = IGNIS_CORE_CONTEXT_INIT();

/* Function Definitions ------------------------------------------------------*/
void ignis_core_start(void)
{
    k_osal_signal_create(&ignis_core_context.signal);
    k_osal_thread_create(&ignis_core_context.thread, "ignis_core", K_OSAL_THREAD_PRIORITY_MEDIUM, 4096, ignis_core_thread_function, &ignis_core_context);
}

void ignis_core_thread_function(void *param)
{
    const ignis_core_context_t *const ignis_core_context_p = param;
    ignis_keymap_register_callback(ignis_core_keymap_callback);
    // ReSharper disable once CppDFAEndlessLoop
    while (1)
    {
        size_t received_signals = 0;
        if (k_osal_signal_wait(ignis_core_context_p->signal, 1, &received_signals, 1, 1, K_OSAL_SIGNAL_NO_WAIT) > 0)
        {
            printf("RECEIVED SIGNALS: %zu\n\r", received_signals);
        }
        switch (ignis_core_context_p->state)
        {
            case IGNIS_CORE_STATE_IDLE:
                break;
            case IGNIS_CORE_STATE_PROGRAMMING_TOTAL_TIME:
                break;
            case IGNIS_CORE_STATE_PROGRAMMING_BUZZER_TIME:
                break;
            case IGNIS_CORE_STATE_PROGRAMMING_CODE:
                break;
            case IGNIS_CORE_STATE_READY_TO_BE_ARMED:
                break;
            case IGNIS_CORE_STATE_ARMED:
                break;
        }
        k_osal_thread_sleep(ignis_core_thread_sleep_time_ms);
    }
}

void ignis_core_keymap_callback(const ignis_keymap_key_t key)
{
    k_osal_signal_set(ignis_core_context.signal, 1);
    switch (key)
    {
        case IGNIS_KEYMAP_KEY_0:
        case IGNIS_KEYMAP_KEY_1:
        case IGNIS_KEYMAP_KEY_2:
        case IGNIS_KEYMAP_KEY_3:
        case IGNIS_KEYMAP_KEY_4:
        case IGNIS_KEYMAP_KEY_5:
        case IGNIS_KEYMAP_KEY_6:
        case IGNIS_KEYMAP_KEY_7:
        case IGNIS_KEYMAP_KEY_8:
        case IGNIS_KEYMAP_KEY_9:
            if (IGNIS_CORE_STATE_READY_TO_BE_ARMED != ignis_core_context.state && IGNIS_CORE_STATE_IDLE != ignis_core_context.state)
            {
                ignis_core_add_digit_to_display_buffer(key);
                ignis_display_send_data(ignis_core_context.display_digits);
            }
            break;
        case IGNIS_KEYMAP_KEY_ENTER:
            // Move on with state
            switch (ignis_core_context.state)
            {
                case IGNIS_CORE_STATE_IDLE:
                    ignis_core_context.state = IGNIS_CORE_STATE_PROGRAMMING_TOTAL_TIME;
                    break;
                case IGNIS_CORE_STATE_PROGRAMMING_TOTAL_TIME:
                    ignis_core_context.total_time_sec = ignis_core_calculate_time_sec(ignis_core_context.display_digits);
                    ignis_core_context.state          = IGNIS_CORE_STATE_PROGRAMMING_BUZZER_TIME;
                    break;
                case IGNIS_CORE_STATE_PROGRAMMING_BUZZER_TIME:
                    ignis_core_context.buzzing_time_sec = ignis_core_calculate_time_sec(ignis_core_context.display_digits);
                    ignis_core_context.state            = IGNIS_CORE_STATE_PROGRAMMING_CODE;
                    break;
                case IGNIS_CORE_STATE_PROGRAMMING_CODE:
                    memcpy(ignis_core_context.defuse_code, ignis_core_context.display_digits, sizeof(ignis_core_context.defuse_code));
                    ignis_core_context.state = IGNIS_CORE_STATE_READY_TO_BE_ARMED;
                    break;
                case IGNIS_CORE_STATE_READY_TO_BE_ARMED:
                    ignis_core_context.state = IGNIS_CORE_STATE_ARMED;
                    break;
                case IGNIS_CORE_STATE_ARMED:
                    if (0 == memcmp(ignis_core_context.defuse_code, ignis_core_context.display_digits, sizeof(ignis_core_context.defuse_code)))
                    {
                        ignis_core_reset_display_buffer();
                        ignis_display_send_data(ignis_core_context.display_digits);
                        ignis_core_context.state = IGNIS_CORE_STATE_IDLE;
                        memset(ignis_core_context.defuse_code, 0, sizeof(ignis_core_context.defuse_code));
                        ignis_core_context.total_time_sec = ignis_core_context.buzzing_time_sec = 0;
                    }
                    break;
                default:
                    break;
            }
            ignis_core_reset_display_buffer();
            break;
        case IGNIS_KEYMAP_KEY_ESC:
            if (IGNIS_CORE_IS_DIGITS_BUFFER_EMPTY())
            {
                ignis_core_context.state = IGNIS_CORE_STATE_IDLE;
            }
            ignis_core_reset_display_buffer();
            break;
        default:
            break;
    }
}

void ignis_core_add_digit_to_display_buffer(const int8_t digit)
{
    for (size_t i = 0; i < sizeof(ignis_core_context.display_digits) / sizeof(int8_t) - 1; i++)
    {
        ignis_core_context.display_digits[i] = ignis_core_context.display_digits[i + 1];
    }
    ignis_core_context.display_digits[3] = digit;
}

void ignis_core_reset_display_buffer(void) { memset(ignis_core_context.display_digits, -1, sizeof(ignis_core_context.display_digits)); }

size_t ignis_core_calculate_time_sec(const uint8_t digits[4])
{
    /*
     * data[0] hours * 10
     * data[1] hours
     * data[2] minutes * 10
     * data[3] minutes
     */
    size_t time_sec = 0;
    time_sec += digits[3] * 60;
    time_sec += digits[2] * 60 * 10;
    time_sec += digits[1] * 3600;
    time_sec += digits[0] * 3600 * 10;
    return time_sec;
}
