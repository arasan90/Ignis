/**
 ********************************************************************************
 * @file    ignis_pcf8575.h
 * @author  Massimiliano Ianniello
 * @date    29/01/26
 ********************************************************************************
 */
#ifndef IGNIS_PCF8575
#define IGNIS_PCF8575

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>

#include "k_hal/k_hal_i2c_master.h"
#include "k_osal/mutex.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
typedef struct ignis_pcf8575_ctx_s
{
    k_hal_i2c_master_device_handle_t i2c_handle;
    k_osal_mutex_t                   mutex_handle;
    uint8_t                          pins_state[2];
    bool                             initialized;
} ignis_pcf8575_ctx_t;

/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/

/**
 * @brief Initializes the PCF8575 I/O expander with the given context.
 *
 * This function sets up the PCF8575 I/O expander using the specified context.
 */
void ignis_pcf8575_init(void);

/**
 * Retrieves the status from the PCF8575 device.
 *
 * This function reads the current status of the PCF8575 I/O expander
 * and writes the retrieved data to the provided status array.
 *
 * @param status An array of size 2 where the retrieved status will be stored.
 *               Each byte in the array represents the status of 8 pins.
 * @return An integer indicating the operation result.
 *         A return value of 0 indicates success. -1 indicates failure.
 */
int ignis_pcf8575_get_status(uint8_t status[2]);

/**
 * Updates the status of the PCF8575 I/O expander.
 *
 * @param status An array of two 8-bit unsigned values representing the
 *               desired status for each of the 16 pins of the PCF8575.
 *               Each bit in the array corresponds to a pin, with 1 indicating
 *               a high state and 0 indicating a low state.
 * @return An integer status code where 0 indicates success, and a -1 indicates failure.
 */
int ignis_pcf8575_set_status(const uint8_t status[2]);
#ifdef __cplusplus
}
#endif
#endif  // IGNIS_PCF8575
