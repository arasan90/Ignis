/**
 ********************************************************************************
 * @file    mutex.h
 * @author  Massimiliano Ianniello
 * @date    20/02/26
 ********************************************************************************
 */
#ifndef MUTEX_H
#define MUTEX_H

/* Includes ------------------------------------------------------------------*/
/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Typedef -------------------------------------------------------------------*/
/**
 * @brief Represents an OS abstraction layer (OSAL) mutex.
 *
 * This structure provides a handle to a platform-specific mutex
 * implementation, allowing for thread synchronization within an
 * operating system-independent layer.
 *
 * The actual mutex implementation is platform-dependent and
 * resides within the private handle `mutex_handle`.
 *
 * The `mutex_handle` field serves as storage for the underlying
 * mutex context and is managed internally by mutex operations.
 *
 * @note Initialization and deallocation of this structure are
 *       handled through appropriate OSAL mutex operations.
 */
typedef struct k_osal_mutex_s
{
    /**
     * @brief Internal handle to the platform-specific mutex context.
     *
     * This pointer serves as the internal storage for the underlying implementation
     * of the mutex, enabling thread-safe synchronization within the OS abstraction layer (OSAL).
     *
     * The content and usage of this handle are platform-dependent and managed
     * through OSAL mutex operations. It typically points to a structure containing
     * platform-specific synchronization primitives (e.g., POSIX pthread mutex).
     *
     * @note This member is meant for internal use only and should not be accessed
     *       or modified directly by application-level code.
     */
    void *mutex_handle;
} k_osal_mutex_t;

/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/**
 * Creates a new recursive mutex and assigns the created mutex handle to the given
 * k_osal_mutex_t structure.
 *
 * @param mutex_handle Pointer to the k_osal_mutex_t structure where the mutex
 *        handle will be stored. Must not be NULL.
 * @return Returns 0 on success, or -1 if the mutex creation failed or
 *         if the input pointer is NULL.
 */
int k_osal_mutex_create(k_osal_mutex_t *mutex_handle);

/**
 * Locks the specified mutex, blocking until the mutex is successfully acquired.
 *
 * This function takes the provided mutex and prevents other threads from acquiring it
 * until it is released. The function blocks indefinitely until the mutex becomes available.
 *
 * @param mutex_handle The handle to the mutex to be locked.
 */
void k_osal_mutex_lock(k_osal_mutex_t mutex_handle);

/**
 * Unlocks the specified mutex.
 *
 * This function calls the underlying OS-specific implementation to release
 * the lock on the mutex represented by the given handle. The mutex must
 * have been previously locked by the current thread.
 *
 * @param mutex_handle The handle to the mutex to be unlocked.
 */
void k_osal_mutex_unlock(k_osal_mutex_t mutex_handle);

#ifdef __cplusplus
}
#endif
#endif  // MUTEX_H
