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
#include <stdint.h>

#include "ignis_keymap_generic_priv.h"
#include "k_hal/k_hal_i2c_master.h"
#include "k_osal/thread.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
typedef struct ignis_keymap_ctx_s
{
    ignis_keymap_ctx_generic_t       generic_ctx;
    k_osal_thread_t                  thread_handle;
    k_hal_i2c_master_device_handle_t i2c_handle;
} ignis_keymap_ctx_t;

/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/**
 * @brief Thread function for the keymap module
 * @param param User context
 */
void ignis_keymap_thread_function(void *param);

/**
 * @brief Identifies the button pressed on the keymap based on the provided data.
 * @param data Array containing the state of the row and column ports for the keymap.
 */
void ignis_keymap_find_button(uint8_t data[2]);

/**
 * @brief Translates a character representing a key into its corresponding keymap-specific key type.
 * @param key The character representing the key to be translated.
 * @return The keymap-specific key type corresponding to the input character.
 */
ignis_keymap_key_t ignis_keymap_translate_key(char key);

/**
 * @brief Resets the state of the keymap module.
 */
void ignis_keymap_reset_state(void);

#ifdef __cplusplus
}
#endif
#endif  // IGNIS_KEYMAP_PRIV_H
