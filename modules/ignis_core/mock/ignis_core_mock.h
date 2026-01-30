/**
 ********************************************************************************
 * @file    ignis_core_mock.h
 * @author  Massimiliano Ianniello
 * @date    30/01/26
 ********************************************************************************
 */
#ifndef IGNIS_CORE_MOCK_H
#define IGNIS_CORE_MOCK_H

/* Includes ------------------------------------------------------------------*/

#include "fff.h"
#include "ignis_core.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
DECLARE_FAKE_VOID_FUNC(ignis_core_start)

#ifdef __cplusplus
}
#endif
#endif  // IGNIS_CORE_MOCK_H
