/**
 ********************************************************************************
 * @file    ignis_keymap_generic_priv.h
 * @author  Massimiliano Ianniello
 * @date    05/02/26
 ********************************************************************************
 */
#ifndef IGNIS_KEYMAP_GENERIC_PRIV_H
#define IGNIS_KEYMAP_GENERIC_PRIV_H

/* Includes ------------------------------------------------------------------*/
#include "ignis_keymap.h"
#include "k_osal/thread.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
typedef struct ignis_keymap_ctx_generic_s
{
    k_osal_thread_t         thread_handle;
    ignis_keymap_callback_t callback;
} ignis_keymap_ctx_generic_t;

/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif  // IGNIS_KEYMAP_GENERIC_PRIV_H
