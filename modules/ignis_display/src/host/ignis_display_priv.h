/**
 ********************************************************************************
 * @file    ignis_display_priv.h
 * @author  Massimiliano Ianniello
 * @date    06/03/26
 ********************************************************************************
 */
#ifndef IGNIS_DISPLAY_PRIV_H
#define IGNIS_DISPLAY_PRIV_H

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>

#include "cJSON.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
typedef struct ignis_display_ctx_s
{
    uint8_t display_digits[4];
    bool    initialized;
} ignis_display_ctx_t;

/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
void ignis_display_sync_cb(void);

int ignis_display_do_nothing(const cJSON *input_data_p, void *user_data_p);

#ifdef __cplusplus
}
#endif
#endif  // IGNIS_DISPLAY_PRIV_H
