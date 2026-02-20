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
    uint8_t ready                        = 1;
    uint8_t write_data[2]                = {0};
    write_data[IGNIS_KEYMAP_ROW_PORT]    = 0xFF;
    write_data[IGNIS_KEYMAP_COLUMN_PORT] = ~IGNIS_KEYMAP_COLUMNS_BITS;
    ignis_pcf8575_set_status(write_data);
    //  ReSharper disable once CppDFAEndlessLoop
    while (1)
    {
        uint8_t data[2] = {0};
        ignis_pcf8575_get_status(data);
        if ((data[IGNIS_KEYMAP_ROW_PORT] & IGNIS_KEYMAP_ROWS_BITS) != IGNIS_KEYMAP_ROWS_BITS)
        {
            if (ready)
            {
                printf("BUTTON PRESSED\n\r");
                ready = 0;
            }
        }
        else
        {
            ready = 1;
        }
        // printf("Port status is %X:%X\n\r", data[0], data[1]);
        k_osal_thread_sleep(100);
    }
}
