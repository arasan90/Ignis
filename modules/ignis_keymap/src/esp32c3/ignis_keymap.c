/**
 ********************************************************************************
 * @file    ignis_keymap.c
 * @author  Massimiliano Ianniello
 * @date    29/01/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "ignis_keymap.h"

#include "ignis_keymap_priv.h"
#include "k_osal/thread.h"

/* Macros --------------------------------------------------------------------*/
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
    // ReSharper disable once CppDFAEndlessLoop
    while (1)
    {
        k_osal_thread_sleep(1000);
    }
}
