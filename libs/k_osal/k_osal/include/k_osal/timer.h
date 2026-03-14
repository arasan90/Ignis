/**
 ********************************************************************************
 * @file    timer.h
 * @author  Massimiliano Ianniello
 * @date    12/03/26
 ********************************************************************************
 */
#ifndef TIMER_H
#define TIMER_H

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
typedef struct k_osal_timer_s
{
    void *timer_handle;  //!< Private member
} k_osal_timer_t;

/**
 * @brief Callback function for timer expirations
 *
 * @param params Context passed by the user
 */
typedef void (*k_osal_timer_callback_t)(void *params);

/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/**
 * @brief Creates a timer with specified attributes.
 *
 * This function initializes a timer setting its period, periodicity, auto-start behavior, and callback function.
 *
 * @param[out] timer        Pointer to a timer object that will hold the created timer's handle.
 * @param[in]  timer_period Timer duration in milliseconds.
 * @param[in]  periodic     Boolean flag indicating whether the timer is periodic.
 *                          - true: The timer will automatically restart after each expiration.
 *                          - false: The timer will be a one-shot timer.
 * @param[in]  auto_start   Boolean flag indicating whether the timer should start immediately.
 *                          - true: The timer starts immediately upon creation.
 *                          - false: The timer remains stopped on creation.
 * @param[in]  callback     Pointer to a callback function that will be executed upon timer expiration.
 *                          The callback is invoked with the user-provided params argument.
 * @param[in]  params       Optional user-defined parameters to be passed to the callback function.
 *
 * @return int
 *         - 0: Success; the timer is created and initialized.
 *         - Non-zero: Failure; an error occurred during timer creation.
 */
int k_osal_timer_create(k_osal_timer_t *timer, uint32_t timer_period, bool periodic, bool auto_start, k_osal_timer_callback_t callback, void *params);

/**
 * @brief Starts a previously created timer.
 *
 * This function resumes the operation of the specified timer if it was not already started.
 * If the timer is already running, the function has no effect.
 *
 * @param timer An instance of k_osal_timer_t that represents the timer to be started.
 *
 * @return Returns 0 on success, -1 otherwise.
 */
int k_osal_timer_start(k_osal_timer_t timer);

/**
 * @brief Stops a previously started timer.
 *
 * This function halts the execution of the specified timer if it is currently running.
 * f the timer was not started, the function performs no operation.
 *
 * @param timer The timer object to be stopped.
 *              This must be a valid `k_osal_timer_t` instance that was previously created.
 *
 * @return Returns 0 on success, -1 otherwise.
 */
int k_osal_timer_stop(k_osal_timer_t timer);

/**
 * Deletes the specified timer and releases associated resources.
 *
 * @param timer The timer object to be deleted. This object must be previously created
 *              and must not be used after deletion.
 * @return An integer indicating the success or failure of the operation.
 *         Returns 0 on success, -1 otherwise.
 */
int k_osal_timer_delete(k_osal_timer_t timer);

#ifdef __cplusplus
}
#endif
#endif  // TIMER_H
