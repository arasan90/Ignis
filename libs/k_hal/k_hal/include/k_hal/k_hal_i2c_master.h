/**
 ********************************************************************************
 * @file    k_hal_i2c_master.h
 * @author  Massimiliano Ianniello
 * @date    18/02/26
 ********************************************************************************
 */
#ifndef HAL_I2C_MASTER_H
#define HAL_I2C_MASTER_H

/* Includes ------------------------------------------------------------------*/
#include <stddef.h>
#include <stdint.h>

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
typedef struct k_hal_i2c_master_device_handle_s
{
    void *handle;
} k_hal_i2c_master_device_handle_t;

/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/**
 * @brief Initializes the I2C master hardware interface.
 *
 * This function sets up the I2C master hardware for communication by
 * configuring necessary control registers and initializing the required
 * resources. It prepares the I2C master for sending and receiving data.
 *
 * The function should be called before any other I2C master-related
 * operations are performed to ensure proper initialization and functionality.
 *
 * @note This function can be called multiple times
 */
void k_hal_i2c_master_init(void);

/**
 * @brief Adds a new device to the I2C master interface.
 *
 * This function registers a device with the I2C master by specifying its
 * I2C address, enabling communication with the device through later
 * I2C transactions. It ensures that the provided address is valid and
 * prepares the system for interactions with the device.
 *
 * @param handle_p Pointer to store the device handle if connection is successful
 * @param address The 7-bit I2C address of the device to be added.
 * @param speed_hz Communication speed in hz
 *
 * @return 0 on success or -1 on failure.
 *
 * @note Ensure that the address does not conflict with other devices
 * already registered on the same I2C bus.
 */
int k_hal_i2c_master_add_device(k_hal_i2c_master_device_handle_t *handle_p, uint8_t address, size_t speed_hz);

/**
 * @brief Reads data from the I2C device associated with the given handle.
 *
 * This function performs a read operation on the specified I2C master device.
 * Data is read from the device into the provided buffer. The function blocks
 * until the requested number of bytes has been read or a timeout occurs.
 *
 * @param handle The handle to the I2C device from which data will be read. Must be valid.
 * @param data_p Pointer to the buffer where the read data will be stored. Must not be NULL.
 * @param length The number of bytes to read from the device. Must be greater than 0.
 *
 * @return 0 on success, or -1 on failure.
 */
int k_hal_i2c_master_read(k_hal_i2c_master_device_handle_t handle, uint8_t *data_p, size_t length);

/**
 * @brief Writes data to an I2C master device.
 *
 * This function sends data to the I2C master device specified by the handle.
 * It writes the specified number of bytes from the provided data buffer to
 * the connected I2C device.
 *
 * The function ensures data is properly transmitted over the I2C bus
 * and returns the status of the operation.
 *
 * @param handle The handle to the I2C master device to which data is written.
 * @param data_p Pointer to the buffer containing the data to be written.
 * @param length The number of bytes to write from the buffer.
 * @return 0 on success, or -1 on failure.
 */
int k_hal_i2c_master_write(k_hal_i2c_master_device_handle_t handle, const uint8_t *data_p, size_t length);

#ifdef __cplusplus
}
#endif
#endif  // HAL_I2C_MASTER_H
