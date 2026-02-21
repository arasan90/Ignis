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
#define IGNIS_KEYMAP_COLUMN_1_BIT (1 << 0)
#define IGNIS_KEYMAP_COLUMN_2_BIT (1 << 1)
#define IGNIS_KEYMAP_COLUMN_3_BIT (1 << 2)

#define IGNIS_KEYMAP_COLUMNS_BITS (IGNIS_KEYMAP_COLUMN_1_BIT | IGNIS_KEYMAP_COLUMN_2_BIT | IGNIS_KEYMAP_COLUMN_3_BIT)

#define IGNIS_KEYMAP_ROW_1_BIT (1 << 0)
#define IGNIS_KEYMAP_ROW_2_BIT (1 << 1)
#define IGNIS_KEYMAP_ROW_3_BIT (1 << 2)
#define IGNIS_KEYMAP_ROW_4_BIT (1 << 3)

#define IGNIS_KEYMAP_ROWS_BITS (IGNIS_KEYMAP_ROW_1_BIT | IGNIS_KEYMAP_ROW_2_BIT | IGNIS_KEYMAP_ROW_3_BIT | IGNIS_KEYMAP_ROW_4_BIT)

#define IGNIS_KEYMAP_ROW_PORT    (0)
#define IGNIS_KEYMAP_COLUMN_PORT (1)

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
        uint8_t data[2] = {0};
        ignis_pcf8575_get_status(data);
        if ((data[IGNIS_KEYMAP_ROW_PORT] & IGNIS_KEYMAP_ROWS_BITS) != IGNIS_KEYMAP_ROWS_BITS)
        {
            if (ready)
            {
                ignis_keymap_find_button(data);
                ready = 0;
            }
        }
        else
        {
            ready = 1;
        }
        k_osal_thread_sleep(100);
    }
}

void ignis_keymap_find_button(uint8_t data[2])
{
    const char keys[4][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}, {'*', '0', '#'}};
    uint8_t    found      = 0;
    uint8_t    row, column = 0;
    uint8_t    new_state[2] = {0xFF, 0xFF};
    if (!(data[IGNIS_KEYMAP_ROW_PORT] & IGNIS_KEYMAP_ROW_1_BIT))
    {
        row = 0;
    }
    else if (!(data[IGNIS_KEYMAP_ROW_PORT] & IGNIS_KEYMAP_ROW_2_BIT))
    {
        row = 1;
    }
    else if (!(data[IGNIS_KEYMAP_ROW_PORT] & IGNIS_KEYMAP_ROW_3_BIT))
    {
        row = 2;
    }
    else
    {
        row = 3;
    }
    new_state[IGNIS_KEYMAP_COLUMN_PORT] = ~IGNIS_KEYMAP_COLUMNS_BITS | IGNIS_KEYMAP_COLUMN_1_BIT;
    ignis_pcf8575_set_status(new_state);
    ignis_pcf8575_get_status(data);
    if (data[IGNIS_KEYMAP_ROW_PORT] & 1 << row)
    {
        column = 0;
        found  = 1;
    }
    if (!found)
    {
        new_state[IGNIS_KEYMAP_COLUMN_PORT] = ~IGNIS_KEYMAP_COLUMNS_BITS | IGNIS_KEYMAP_COLUMN_2_BIT;
        ignis_pcf8575_set_status(new_state);
        ignis_pcf8575_get_status(data);
        if (data[IGNIS_KEYMAP_ROW_PORT] & 1 << row)
        {
            column = 1;
            found  = 1;
        }
    }
    if (!found)
    {
        new_state[IGNIS_KEYMAP_COLUMN_PORT] = ~IGNIS_KEYMAP_COLUMNS_BITS | IGNIS_KEYMAP_COLUMN_3_BIT;
        ignis_pcf8575_set_status(new_state);
        ignis_pcf8575_get_status(data);
        if (data[IGNIS_KEYMAP_ROW_PORT] & 1 << row)
        {
            column = 2;
            found  = 1;
        }
    }
    if (found)
    {
        ignis_keymap_ctx.generic_ctx.callback(ignis_keymap_translate_key(keys[row][column]));
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
    uint8_t state[2]                = {0xFF, 0xFF};
    state[IGNIS_KEYMAP_COLUMN_PORT] = ~IGNIS_KEYMAP_COLUMNS_BITS;
    ignis_pcf8575_set_status(state);
}