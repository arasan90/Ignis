/**
 ********************************************************************************
 * @file    ignis_buzzer_priv.h
 * @author  Massimiliano Ianniello
 * @date    20/03/26
 ********************************************************************************
 */
#ifndef IGNIS_BUZZER_PRIV_H
#define IGNIS_BUZZER_PRIV_H

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "cJSON.h"
#include "k_osal/timer.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {



#endif

/* Typedefs ------------------------------------------------------------------*/
typedef struct ignis_buzzer_context_s
{
    k_osal_timer_t timer;
    bool initialized;
    bool active;
} ignis_buzzer_context_t;

/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/

void ignis_buzzer_timer_elapsed_cb(void* param);

void ignis_buzzer_sync_cb(void);

int ignis_buzzer_do_nothing(const cJSON* input_data_p, void* user_data_p);

#ifdef __cplusplus
}
#endif
#endif //IGNIS_BUZZER_PRIV_H
