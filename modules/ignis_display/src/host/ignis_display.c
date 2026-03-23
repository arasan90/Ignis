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
void ignis_display_send_numeric_data(const uint8_t *data, const bool time)
{
    for (int i = 0; i < 4; i++)
    {
        ignis_display_ctx.display_digits[i] = 0x30 + data[i];
    }
    ignis_display_ctx.time_representation = time;
    ignis_display_sync_cb();
}

void ignis_display_send_string(const char *text)
{
    const size_t string_len = strlen(text);
    memset(ignis_display_ctx.display_digits, 0, sizeof(ignis_display_ctx.display_digits));
    for (size_t i = 0; i <= string_len; i++)
    {
        ignis_display_ctx.display_digits[i] = text[i];
    }
    if (string_len < 4)
    {
        for (size_t i = string_len; i < 4; i++)
        {
            ignis_display_ctx.display_digits[i] = '\x1F';  // Blank char
        }
    }
    ignis_display_ctx.time_representation = false;
    ignis_display_sync_cb();
}

void ignis_display_sync_cb(void)
{
    const char  *string_template_no_time   = "{\"interface\":\"display\",\"value\":\"%c%c%c%c\"}";
    const char  *string_template_with_time = "{\"interface\":\"display\",\"value\":\"%c%c:%c%c\"}";
    const char  *string_template           = ignis_display_ctx.time_representation ? string_template_with_time : string_template_no_time;
    const size_t space_needed              = snprintf(NULL, 0, string_template, ignis_display_ctx.display_digits[0], ignis_display_ctx.display_digits[1],
                                                      ignis_display_ctx.display_digits[2], ignis_display_ctx.display_digits[3]) +
                                1;
    char *event_data = calloc(space_needed, sizeof(char));
    if (event_data)
    {
        snprintf(event_data, space_needed, string_template, ignis_display_ctx.display_digits[0], ignis_display_ctx.display_digits[1],
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
