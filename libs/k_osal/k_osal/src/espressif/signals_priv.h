/**
 ********************************************************************************
 * @file    signals_priv.h
 * @author  Massimiliano Ianniello
 * @date    27/02/26
 ********************************************************************************
 */
#ifndef SIGNALS_PRIV_H
#define SIGNALS_PRIV_H

/* Includes ------------------------------------------------------------------*/
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
typedef struct k_osal_signal_context_s
{
    EventGroupHandle_t event_group;
} k_osal_signal_context_t;

/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/

#ifdef __cplusplus
}
#endif
#endif  // SIGNALS_PRIV_H
