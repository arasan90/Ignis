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
#include "ignis_keymap.h"
#include "ignis_keymap_generic_priv.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
typedef struct ignis_keymap_ctx_s
{
    ignis_keymap_ctx_generic_t generic_ctx;
} ignis_keymap_ctx_t;

/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/**
 * @brief Callback to manage received data from host interface
 *
 * @param input_data_p Pointer to input data in cJSON format
 * @param user_data_p Pointer to user data
 * @return 0 in case of success, error code otherwise
 */
int ignis_keymap_host_interface_callback(const cJSON *input_data_p, void *user_data_p);

/**
 * @brief Translate key string to ignis_keymap_key_t type
 *
 * @brief key_string Pointer to key string
 * @return Translated key if successful, IGNIS_KEYMAP_KEY_INVALID otherwise
 */
ignis_keymap_key_t ignis_keymap_translate_key_string(const char *key_string);

#ifdef __cplusplus
}
#endif
#endif  // IGNIS_KEYMAP_PRIV_H
