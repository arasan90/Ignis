/**
 ********************************************************************************
 * @file    ignis_keymap.c
 * @author  Massimiliano Ianniello
 * @date    29/01/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "ignis_keymap.h"

#include <stdio.h>
#include <string.h>

#include "ignis_keymap_priv.h"
#include "ignis_pcf8575.h"
#include "k_hal/k_hal_i2c_master.h"
#include "k_osal/thread.h"

/* Macros --------------------------------------------------------------------*/
#define IGNIS_KEYMAP_ROW_1_PIN    (0)
#define IGNIS_KEYMAP_ROW_2_PIN    (1)
#define IGNIS_KEYMAP_ROW_3_PIN    (2)
#define IGNIS_KEYMAP_ROW_4_PIN    (3)
#define IGNIS_KEYMAP_COLUMN_1_PIN (8)
#define IGNIS_KEYMAP_COLUMN_2_PIN (9)
#define IGNIS_KEYMAP_COLUMN_3_PIN (10)

/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
ignis_keymap_ctx_t ignis_keymap_ctx = {0};

/* Function Definitions ------------------------------------------------------*/
void ignis_keymap_start(void)
{
    k_osal_thread_create(&ignis_keymap_ctx.thread_handle, "ignis_keymap", K_OSAL_THREAD_PRIORITY_MEDIUM, 4096, ignis_keymap_thread_function, NULL);
}
void ignis_keymap_register_callback(const ignis_keymap_callback_t callback) { ignis_keymap_ctx.generic_ctx.callback = callback; }

void ignis_keymap_thread_function(void *param)
{
    (void)param;
    k_hal_i2c_master_init();
    uint8_t ready = 1;
    ignis_keymap_reset_state();
    //  ReSharper disable once CppDFAEndlessLoop
    while (1)
    {
        ignis_pcf8575_pin_level_t pin_data[] = {{IGNIS_KEYMAP_ROW_1_PIN, -1},
                                                {IGNIS_KEYMAP_ROW_2_PIN, -1},
                                                {IGNIS_KEYMAP_ROW_3_PIN, -1},
                                                {IGNIS_KEYMAP_ROW_4_PIN, -1}};
        ignis_pcf8575_get_pin_level(pin_data, sizeof(pin_data) / sizeof(ignis_pcf8575_pin_level_t));
        if (1 == pin_data[0].level && 1 == pin_data[1].level && 1 == pin_data[2].level && 1 == pin_data[3].level && !ready)
        {
            ready = 1;
        }
        else if (ready)
        {
            for (int i = 0; i < sizeof(pin_data) / sizeof(ignis_pcf8575_pin_level_t); i++)
            {
                if (0 == pin_data[i].level)
                {
                    ready = 0;
                    ignis_keymap_find_button(pin_data[i].pin);
                    break;
                }
            }
        }
        k_osal_thread_sleep(100);
    }
}

void ignis_keymap_find_button(const uint8_t row_pin)
{
    uint8_t       found         = 0;
    uint8_t       column        = 0;
    const uint8_t column_pins[] = {IGNIS_KEYMAP_COLUMN_1_PIN, IGNIS_KEYMAP_COLUMN_2_PIN, IGNIS_KEYMAP_COLUMN_3_PIN};
    for (int i = 0; i < sizeof(column_pins) / sizeof(uint8_t); i++)
    {
        ignis_pcf8575_pin_level_t pin_level = {column_pins[i], 1};
        ignis_pcf8575_set_pin_level(&pin_level, 1);
        pin_level.pin   = row_pin;
        pin_level.level = -1;
        ignis_pcf8575_get_pin_level(&pin_level, 1);
        if (1 == pin_level.level)
        {
            column = i;
            found  = 1;
            break;
        }
        else
        {
            pin_level.pin   = column_pins[i];
            pin_level.level = 0;
            ignis_pcf8575_set_pin_level(&pin_level, 1);
        }
    }
    if (found)
    {
        const char keys[4][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}, {'*', '0', '#'}};
        ignis_keymap_ctx.generic_ctx.callback(ignis_keymap_translate_key(keys[row_pin][column]));
    }
    ignis_keymap_reset_state();
}

ignis_keymap_key_t ignis_keymap_translate_key(char key)
{
    ignis_keymap_key_t translated_key;
    switch (key)
    {
        case '1':
            translated_key = IGNIS_KEYMAP_KEY_1;
            break;
        case '2':
            translated_key = IGNIS_KEYMAP_KEY_2;
            break;
        case '3':
            translated_key = IGNIS_KEYMAP_KEY_3;
            break;
        case '4':
            translated_key = IGNIS_KEYMAP_KEY_4;
            break;
        case '5':
            translated_key = IGNIS_KEYMAP_KEY_5;
            break;
        case '6':
            translated_key = IGNIS_KEYMAP_KEY_6;
            break;
        case '7':
            translated_key = IGNIS_KEYMAP_KEY_7;
            break;
        case '8':
            translated_key = IGNIS_KEYMAP_KEY_8;
            break;
        case '9':
            translated_key = IGNIS_KEYMAP_KEY_9;
            break;
        case '*':
            translated_key = IGNIS_KEYMAP_KEY_ESC;
            break;
        case '0':
            translated_key = IGNIS_KEYMAP_KEY_0;
            break;
        case '#':
            translated_key = IGNIS_KEYMAP_KEY_ENTER;
            break;
        default:
            translated_key = IGNIS_KEYMAP_KEY_INVALID;
            break;
    }
    return translated_key;
}

void ignis_keymap_reset_state(void)
{
    const ignis_pcf8575_pin_level_t pin_data[] = {{IGNIS_KEYMAP_COLUMN_1_PIN, 0}, {IGNIS_KEYMAP_COLUMN_2_PIN, 0}, {IGNIS_KEYMAP_COLUMN_3_PIN, 0}};
    ignis_pcf8575_set_pin_level(pin_data, sizeof(pin_data) / sizeof(ignis_pcf8575_pin_level_t));
}