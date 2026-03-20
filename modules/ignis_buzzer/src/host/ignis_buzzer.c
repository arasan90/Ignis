/**
 ********************************************************************************
 * @file    ignis_buzzer.c
 * @author  Massimiliano Ianniello
 * @date    20/03/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "ignis_buzzer.h"
#include "ignis_buzzer_priv.h"
#include "k_ghost_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
ignis_buzzer_context_t ignis_buzzer_context = {0};

/* Function Definitions ------------------------------------------------------*/
void ignis_buzzer_start(void)
{
    if (!ignis_buzzer_context.initialized)
    {
        k_ghost_io_init();
        assert(0 == k_osal_timer_create(&ignis_buzzer_context.timer, 250, false, false, ignis_buzzer_timer_elapsed_cb,
            NULL));
        k_ghost_io_register_interface("buzzer", ignis_buzzer_do_nothing, ignis_buzzer_sync_cb, NULL);
        ignis_buzzer_context.initialized = true;
    }
}

void ignis_buzzer_sound_short_alarm(void)
{
    ignis_buzzer_context.active = 1;
    k_osal_timer_start(ignis_buzzer_context.timer);
    ignis_buzzer_sync_cb();
}

void ignis_buzzer_sound_long_alarm(void)
{
    ignis_buzzer_context.active = 1;
    ignis_buzzer_sync_cb();
}

void ignis_buzzer_alarm_shutoff(void)
{
    ignis_buzzer_context.active = 0;
    k_osal_timer_stop(ignis_buzzer_context.timer);
    ignis_buzzer_sync_cb();
}

void ignis_buzzer_timer_elapsed_cb(void* param)
{
    (void)param;
    ignis_buzzer_context.active = 0;
    ignis_buzzer_sync_cb();
}

void ignis_buzzer_sync_cb(void)
{
    const size_t space_needed = snprintf(NULL, 0, "{\"interface\":\"buzzer\",\"value\":\"%d\"}",
                                         ignis_buzzer_context.active)
        +
        1;
    char* event_data = calloc(space_needed, sizeof(char));
    if
    (event_data)
    {
        snprintf(event_data, space_needed, "{\"interface\":\"buzzer\",\"value\":\"%d\"}",
                 ignis_buzzer_context.active);
        k_ghost_io_send_event(event_data);
    }

    free(event_data);
}

int ignis_buzzer_do_nothing(const cJSON* input_data_p, void* user_data_p)
{
    (void)input_data_p;
    (void)user_data_p;
    return 0;
}
