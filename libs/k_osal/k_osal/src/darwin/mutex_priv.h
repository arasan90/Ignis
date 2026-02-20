/**
 ********************************************************************************
 * @file    mutex_priv.h
 * @author  Massimiliano Ianniello
 * @date    20/02/26
 ********************************************************************************
 */
#ifndef MUTEX_PRIV_H
#define MUTEX_PRIV_H

/* Includes ------------------------------------------------------------------*/
#include "pthread.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
typedef struct k_osal_mutex_context_s
{
    pthread_mutex_t mutex;
} k_osal_mutex_context_t;
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/

#ifdef __cplusplus
}
#endif
#endif  // MUTEX_PRIV_H
