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
DECLARE_FAKE_VOID_FUNC(ignis_display_send_numeric_data, const uint8_t *, bool)
DECLARE_FAKE_VOID_FUNC(ignis_display_send_string, const char *)
DECLARE_FAKE_VOID_FUNC(ignis_display_init)

inline void ignis_display_mock_reset_fakes(void)
{
    RESET_FAKE(ignis_display_send_numeric_data);
    RESET_FAKE(ignis_display_send_string);
    RESET_FAKE(ignis_display_init);
}
#ifdef __cplusplus
}
#endif
#endif  // IGNIS_DISPLAY_MOCK_H
