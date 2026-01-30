/**
 ********************************************************************************
 * @file    ignis_core.cpp
 * @author  Massimiliano Ianniello
 * @date    28/01/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "ignis_core.h"

#include <stdio.h>
#include <string.h>

#include "ignis_core_priv.h"
#include "ignis_keymap.h"
/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
const size_t ignis_core_thread_sleep_time_ms = 50;

/* Variables -----------------------------------------------------------------*/
ignis_core_context_t ignis_core_context = {0};

/* Function Definitions ------------------------------------------------------*/
void ignis_core_start(void)
{
    ignis_core_context.current_digit = 3;
    k_osal_thread_create(&ignis_core_context.thread, "ignis_core", K_OSAL_THREAD_PRIORITY_MEDIUM, 4096, ignis_core_thread_function, &ignis_core_context);
}

void ignis_core_thread_function(void *param)
{
    const ignis_core_context_t *const ignis_core_context_p = param;

    // ReSharper disable once CppDFAEndlessLoop
    while (1)
    {
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
    int8_t   digit                  = -1;
    uint8_t  enter_pressed          = 0;
    uint8_t  esc_pressed            = 0;
    size_t  *value_to_set_p         = NULL;
    uint8_t *digits_values_to_set_p = NULL;
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
            digit = key;
            break;
        case IGNIS_KEYMAP_KEY_ENTER:
            enter_pressed = 1;
            break;
        case IGNIS_KEYMAP_KEY_ESC:
            esc_pressed = 1;
            break;
    }
    switch (ignis_core_context.state)
    {
        case IGNIS_CORE_STATE_PROGRAMMING_TOTAL_TIME:
            value_to_set_p         = &ignis_core_context.total_time_sec;
            digits_values_to_set_p = ignis_core_context.total_time_digits;
            break;
        case IGNIS_CORE_STATE_PROGRAMMING_BUZZER_TIME:
            value_to_set_p         = &ignis_core_context.buzzer_time_sec;
            digits_values_to_set_p = ignis_core_context.buzzer_time_digits;
            break;
        case IGNIS_CORE_STATE_PROGRAMMING_CODE:
            value_to_set_p         = &ignis_core_context.code;
            digits_values_to_set_p = ignis_core_context.code_digits;
            break;
        default:
            break;
    }
    if (-1 != digit)
    {
        if (value_to_set_p && digits_values_to_set_p)
        {
            digits_values_to_set_p[ignis_core_context.current_digit] = digit;
            if (&ignis_core_context.code != value_to_set_p)
            {
                *value_to_set_p = digits_values_to_set_p[3] * 3600 * 10 + digits_values_to_set_p[2] * 3600 + digits_values_to_set_p[1] * 60 * 10 +
                                  digits_values_to_set_p[0] * 60;
            }
            else
            {
                *value_to_set_p =
                    digits_values_to_set_p[3] * 1000 + digits_values_to_set_p[2] * 100 + digits_values_to_set_p[1] * 10 + digits_values_to_set_p[0];
            }
            if (0 == ignis_core_context.current_digit)
            {
                ignis_core_context.current_digit = 3;
            }
            else
            {
                ignis_core_context.current_digit--;
            }
        }
    }
    if (enter_pressed)
    {
        if (ignis_core_context.state > IGNIS_CORE_STATE_IDLE && ignis_core_context.state < IGNIS_CORE_STATE_READY_TO_BE_ARMED)
        {
            ignis_core_context.state++;
        }
    }
    if (esc_pressed && value_to_set_p)
    {
        *value_to_set_p = 0;
        memset(digits_values_to_set_p, 0, sizeof(ignis_core_context.code_digits));
        ignis_core_context.current_digit = 3;
    }
}
