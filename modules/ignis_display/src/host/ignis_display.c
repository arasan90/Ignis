/**
********************************************************************************
* @file    ignis_display.c
* @author  Massimiliano Ianniello
* @date    27/02/26
********************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include "ignis_display.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ignis_display_priv.h"
#include "k_ghost_io.h"

/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
ignis_display_ctx_t ignis_display_ctx = {0};

/* Function Definitions ------------------------------------------------------*/
void ignis_display_init(void)
{
    if (!ignis_display_ctx.initialized)
    {
        memset(&ignis_display_ctx, '-', sizeof(ignis_display_ctx_t));
        k_ghost_io_init();
        k_ghost_io_register_interface("display", ignis_display_do_nothing, ignis_display_sync_cb, NULL);
        ignis_display_ctx.initialized = true;
    }
}
void ignis_display_send_data(const uint8_t data[4], const bool time)
{
    (void)time;
    for (int i = 0; i < 4; i++)
    {
        if (0xFF == data[i])
        {
            ignis_display_ctx.display_digits[i] = '-';
        }
        else
        {
            ignis_display_ctx.display_digits[i] = 0x30 + data[i];
        }
    }
    ignis_display_sync_cb();
}

void ignis_display_sync_cb(void)
{
    const size_t space_needed = snprintf(NULL, 0, "{\"value\":\"%c%c%c%c\"}", ignis_display_ctx.display_digits[0], ignis_display_ctx.display_digits[1],
                                         ignis_display_ctx.display_digits[2], ignis_display_ctx.display_digits[3]) +
                                1;
    char *event_data = calloc(space_needed, sizeof(char));
    if (event_data)
    {
        snprintf(event_data, space_needed, "{\"value\":\"%c%c%c%c\"}", ignis_display_ctx.display_digits[0], ignis_display_ctx.display_digits[1],
                 ignis_display_ctx.display_digits[2], ignis_display_ctx.display_digits[3]);
        k_ghost_io_send_event(event_data);
    }
    free(event_data);
}

int ignis_display_do_nothing(const cJSON *input_data_p, void *user_data_p)
{
    (void)input_data_p;
    (void)user_data_p;
    return 0;
}
