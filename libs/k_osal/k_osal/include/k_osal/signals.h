/**
 ********************************************************************************
 * @file    signals.h
 * @author  Massimiliano Ianniello
 * @date    27/02/26
 ********************************************************************************
 */
#ifndef SIGNALS_H
#define SIGNALS_H

/* Includes ------------------------------------------------------------------*/
#include <stddef.h>
#include <stdint.h>

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
typedef struct k_osal_signal_s
{
    void *handle;
} k_osal_signal_t;

/* Constants -----------------------------------------------------------------*/
#define K_OSAL_SIGNAL_NO_WAIT      0
#define K_OSAL_SIGNAL_WAIT_FOREVER 0xFFFFFFFF

/* Function Declarations -----------------------------------------------------*/
/**
 * @brief Creates and initializes a signal handle.
 *
 * This function allocates and initializes the necessary resources for a signal
 * handle, including memory allocation for an internal context structure,
 * initialization of a mutex, and a condition variable for thread-safety
 * and signaling operations.
 *
 * @param[out] signal_handle Pointer to the signal handle structure that will
 *                           be initialized by the function.
 *
 * @return Returns 0 on success, or -1 if an error occurs.
 */
int k_osal_signal_create(k_osal_signal_t *signal_handle);

/**
 * @brief Waits for one or more signals to be set in a signal object, with an optional timeout.
 *
 * This function waits for specified signals to be set in the provided signal object.
 * The behavior for waiting depends on the `wait_all` parameter:
 * - When `wait_all` is 0: The function returns when any one signal in the mask is set.
 * - When `wait_all` is 1: The function returns only if all signals in the mask are set.
 *
 * After waking up, the signals that caused the wake-up are stored in `received_signals`.
 * Optionally, the signals that have been received can be cleared from the signal object.
 *
 * @param[in] signal_handle   Signal object handle.
 * @param[in] mask            Bitmask specifying the signals to wait for.
 * @param[out] received_signals Pointer to store the signals received during the wait.
 * @param[in] wait_all        Non-zero to wait for all signals in the mask, zero to wait for any.
 * @param[in] clear           Non-zero to clear the received signals after waking up.
 * @param[in] timeout_ms      Timeout for the wait in milliseconds.
 *                            Use `K_OSAL_SIGNAL_WAIT_FOREVER` for indefinite wait or
 *                            `K_OSAL_SIGNAL_NO_WAIT` for non-blocking behavior.
 *
 * @return
 * - 1 on successful signal reception.
 * - 0 if the timeout elapsed without receiving any signals.
 * - -1 on failure (e.g., invalid arguments or internal error).
 */
int k_osal_signal_wait(k_osal_signal_t signal_handle, size_t mask, size_t *received_signals, uint8_t wait_all, uint8_t clear, size_t timeout_ms);

/**
 * @brief Sets the specified signal(s) in the signal set.
 *
 * This function sets the bitmask specified by `mask` in the `signals` field
 * of the signal context associated with the provided signal handle.
 *
 * @param[in] signal_handle A `k_osal_signal_t` structure, which
 *                          should contain a valid signal context handle.
 * @param[in] mask          A bitmask representing the signal(s) to be set.
 *
 * @return 0 on successful signal setting and broadcasting, or -1 if the
 *         operation fails (e.g., invalid handle or internal errors).
 */
int k_osal_signal_set(k_osal_signal_t signal_handle, size_t mask);

#ifdef __cplusplus
}
#endif
#endif  // SIGNALS_H
