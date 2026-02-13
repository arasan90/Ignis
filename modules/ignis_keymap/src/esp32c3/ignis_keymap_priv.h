/**
 ********************************************************************************
 * @file    ignis_keymap_priv.h
 * @author  Massimiliano Ianniello
 * @date    05/02/26
 ********************************************************************************
 */
#ifndef IGNIS_KEYMAP_PRIV_H
#define IGNIS_KEYMAP_PRIV_H

/* Includes ------------------------------------------------------------------*/
#include "ignis_keymap_generic_priv.h"
#include "k_osal/thread.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
typedef struct ignis_keymap_ctx_s
{
    ignis_keymap_ctx_generic_t generic_ctx;
    k_osal_thread_t thread_handle;
} ignis_keymap_ctx_t;

/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/**
 * @brief Thread function for the keymap module
 * @param param User context
 */
void ignis_keymap_thread_function(void *param);

#ifdef __cplusplus
}
#endif
#endif  // IGNIS_KEYMAP_PRIV_H
