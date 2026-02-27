/**
 ********************************************************************************
 * @file    signals_priv.h
 * @author  Massimiliano Ianniello
 * @date    27/02/26
 ********************************************************************************
 */
#ifndef SIGNALS_PRIV_H
#define SIGNALS_PRIV_H

/* Includes ------------------------------------------------------------------*/
#include <pthread.h>
#include <semaphore.h>

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
typedef struct k_osal_signal_context_s
{
    pthread_mutex_t mutex;    //!< Mutex for thread safety.
    pthread_cond_t  cond;     //!< Condition variable for signaling.
    size_t          signals;  //!< Bitmask of active signals.
} k_osal_signal_context_t;

/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/

#ifdef __cplusplus
}
#endif
#endif  // SIGNALS_PRIV_H
