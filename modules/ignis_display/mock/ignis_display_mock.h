/**
 ********************************************************************************
 * @file    ignis_display_mock.h
 * @author  Massimiliano Ianniello
 * @date    27/02/26
 ********************************************************************************
 */
#ifndef IGNIS_DISPLAY_MOCK_H
#define IGNIS_DISPLAY_MOCK_H

/* Includes ------------------------------------------------------------------*/
#include "fff.h"
#include "ignis_display.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
DECLARE_FAKE_VOID_FUNC(ignis_display_send_data, uint8_t *)

inline void ignis_display_mock_reset_fakes(void) { RESET_FAKE(ignis_display_send_data); }
#ifdef __cplusplus
}
#endif
#endif  // IGNIS_DISPLAY_MOCK_H
