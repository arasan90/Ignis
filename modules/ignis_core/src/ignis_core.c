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
#include "ignis_buzzer.h"

/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
ignis_core_context_t ignis_core_context = IGNIS_CORE_CONTEXT_INIT();

/* Function Definitions ------------------------------------------------------*/
void ignis_core_start(void)
{
    if (!ignis_core_context.timer.timer_handle)
    {
        k_osal_timer_create(&ignis_core_context.timer, 1000 * 60, true, false, ignis_core_timer_callback, NULL);
    }
    ignis_keymap_register_callback(ignis_core_keymap_callback);
    ignis_display_send_string("safe");
}

void ignis_core_keymap_callback(const ignis_keymap_key_t key)
{
    /* Code to be always executed */
    if (IGNIS_CORE_STATE_EXPLODED == ignis_core_context.state)
    {
        ignis_buzzer_alarm_shutoff();
        ignis_core_context.state = IGNIS_CORE_STATE_IDLE;
        memset(ignis_core_context.defuse_code, 0, sizeof(ignis_core_context.defuse_code));
        ignis_core_context.total_time_min = ignis_core_context.buzzing_time_min = 0;
        ignis_display_send_string("safe");
        return;
    }
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
        if (IGNIS_CORE_STATE_READY_TO_BE_ARMED != ignis_core_context.state && IGNIS_CORE_STATE_IDLE !=
            ignis_core_context.state)
        {
            ignis_core_add_digit_to_display_buffer(key);
            bool is_time =
                IGNIS_CORE_STATE_PROGRAMMING_BUZZER_TIME == ignis_core_context.state ||
                IGNIS_CORE_STATE_PROGRAMMING_TOTAL_TIME == ignis_core_context.state;
            ignis_display_send_numeric_data(ignis_core_context.display_digits, is_time);
        }
        break;
    case IGNIS_KEYMAP_KEY_ENTER:
        // Move on with state
        switch (ignis_core_context.state)
        {
        case IGNIS_CORE_STATE_IDLE:
            ignis_core_context.elapsed_time_min = 0;
            ignis_core_reset_display_buffer();
            ignis_core_context.state = IGNIS_CORE_STATE_PROGRAMMING_TOTAL_TIME;
            ignis_display_send_string("cnt");
            break;
        case IGNIS_CORE_STATE_PROGRAMMING_TOTAL_TIME:

            ignis_core_context.total_time_min = ignis_core_calculate_time_min(ignis_core_context.display_digits);
            ignis_core_reset_display_buffer();
            if (ignis_core_context.total_time_min > 0)
            {
                ignis_core_context.state = IGNIS_CORE_STATE_PROGRAMMING_BUZZER_TIME;
                ignis_display_send_string("buzz");
            }
            break;
        case IGNIS_CORE_STATE_PROGRAMMING_BUZZER_TIME:
            ignis_core_context.buzzing_time_min = ignis_core_calculate_time_min(ignis_core_context.display_digits);
            ignis_core_reset_display_buffer();
            ignis_core_context.state = IGNIS_CORE_STATE_PROGRAMMING_CODE;
            ignis_display_send_string("code");
            break;
        case IGNIS_CORE_STATE_PROGRAMMING_CODE:
            memcpy(ignis_core_context.defuse_code, ignis_core_context.display_digits,
                   sizeof(ignis_core_context.defuse_code));
            ignis_core_reset_display_buffer();
            ignis_core_context.state = IGNIS_CORE_STATE_READY_TO_BE_ARMED;
            ignis_display_send_string("rdy");
            break;
        case IGNIS_CORE_STATE_READY_TO_BE_ARMED:
            {
                uint8_t digits[4] = {0};
                ignis_core_calculate_digits(digits, ignis_core_context.total_time_min);
                ignis_display_send_numeric_data(digits, true);
                ignis_core_context.state = IGNIS_CORE_STATE_ARMED;
                k_osal_timer_start(ignis_core_context.timer);
            }
            break;
        case IGNIS_CORE_STATE_ARMED:
            if (0 == memcmp(ignis_core_context.defuse_code, ignis_core_context.display_digits,
                            sizeof(ignis_core_context.defuse_code)))
            {
                ignis_buzzer_alarm_shutoff();
                ignis_core_reset_display_buffer();
                ignis_core_context.state = IGNIS_CORE_STATE_IDLE;
                memset(ignis_core_context.defuse_code, 0, sizeof(ignis_core_context.defuse_code));
                ignis_core_context.total_time_min = ignis_core_context.buzzing_time_min = 0;
                ignis_display_send_string("safe");
                k_osal_timer_stop(ignis_core_context.timer);
            }
            else
            {
                /* Wrong code */
                ignis_core_reset_display_buffer();
                ignis_display_send_string("err");
            }
            break;
        default:
            break;
        }
        break;
    case IGNIS_KEYMAP_KEY_ESC:
        if (IGNIS_CORE_STATE_ARMED != ignis_core_context.state && IGNIS_CORE_IS_DIGITS_BUFFER_EMPTY())
        {
            ignis_core_context.state = IGNIS_CORE_STATE_IDLE;
            ignis_display_send_string("safe");
        }
        else
        {
            ignis_core_reset_display_buffer();
            if (IGNIS_CORE_STATE_ARMED == ignis_core_context.state)
            {
                uint8_t digits[4] = {0};
                ignis_core_calculate_digits(
                    digits, ignis_core_context.total_time_min - ignis_core_context.elapsed_time_min);
                ignis_display_send_numeric_data(digits, true);
            }
            else
            {
                ignis_display_send_numeric_data(ignis_core_context.display_digits, 0);
            }
        }
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

void ignis_core_reset_display_buffer(void)
{
    memset(ignis_core_context.display_digits, 0, sizeof(ignis_core_context.display_digits));
}

size_t ignis_core_calculate_time_min(const uint8_t digits[4])
{
    /*
     * data[0] hours * 10
     * data[1] hours
     * data[2] minutes * 10
     * data[3] minutes
     */
    size_t time_min = 0;
    time_min += digits[3];
    time_min += digits[2] * 10;
    time_min += digits[1] * 60;
    time_min += digits[0] * 60 * 10;
    return time_min;
}

void ignis_core_calculate_digits(uint8_t digits[4], size_t time_min)
{
    digits[0] = time_min / 600;
    time_min %= 600;
    digits[1] = time_min / 60;
    time_min %= 60;
    digits[2] = time_min / 10;
    time_min %= 10;
    digits[3] = time_min;
}

void ignis_core_timer_callback(void* params)
{
    (void)params;
    uint8_t digits[4] = {0};
    ignis_core_context.elapsed_time_min++;
    size_t remaining_time_min = ignis_core_context.total_time_min - ignis_core_context.elapsed_time_min;
    ignis_core_calculate_digits(digits, remaining_time_min);
    ignis_display_send_numeric_data(digits, true);
    if (ignis_core_context.elapsed_time_min == ignis_core_context.total_time_min)
    {
        ignis_buzzer_sound_long_alarm();
        ignis_core_context.state = IGNIS_CORE_STATE_EXPLODED;
        k_osal_timer_stop(ignis_core_context.timer);
    }
    else if (0 != ignis_core_context.buzzing_time_min && 0 == ignis_core_context.elapsed_time_min % ignis_core_context.
        buzzing_time_min)
    {
        ignis_buzzer_sound_short_alarm();
    }
}
