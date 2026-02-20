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
 * @brief Retrieves the status from the PCF8575 keymap module.
 * @param status An array of two uint8_t elements to store the retrieved status.
 * @return Returns 0 on success or -1 on failure.
 */
int ignis_keymap_pcf8575_get_status(uint8_t status[2]);

/**
 * @brief Sets the status for the PCF8575 keymap module
 * @param status Array of 2 bytes representing the desired status
 * @return Returns 0 on success or -1 on failure.
 */
int ignis_keymap_pcf8575_set_status(const uint8_t status[2]);

#ifdef __cplusplus
}
#endif
#endif  // IGNIS_KEYMAP_PRIV_H
