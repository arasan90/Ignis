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

typedef struct ignis_pcf8575_pin_level_s
{
    uint8_t pin;
    int8_t  level;
} ignis_pcf8575_pin_level_t;

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
 * @brief Retrieves the pin levels from the PCF8575 I/O expander.
 *
 * This function reads the levels of the pins from the PCF8575 and populates
 * the provided buffer with pin level information.
 *
 * @param pin_levels_p Pointer to a buffer where the pin levels will be stored.
 * @param pin_levels_size Size of the buffer (number of elements) pointed to
 *                        by pin_levels_p.
 */
void ignis_pcf8575_get_pin_level(ignis_pcf8575_pin_level_t *pin_levels_p, size_t pin_levels_size);

/**
 * @brief Sets the pin levels for the PCF8575 I/O expander.
 *
 * This function updates the state of the pins on the PCF8575 I/O expander based on the provided pin levels.
 *
 * @param pin_levels_p Pointer to an array containing the desired pin levels.
 * @param pin_levels_size The number of entries in the pin levels array.
 */
void ignis_pcf8575_set_pin_level(const ignis_pcf8575_pin_level_t *pin_levels_p, size_t pin_levels_size);
#ifdef __cplusplus
}
#endif
#endif  // IGNIS_PCF8575
