/**
 ********************************************************************************
 * @file    ignis_keymap.h
 * @author  Massimiliano Ianniello
 * @date    29/01/26
 ********************************************************************************
 */
#ifndef IGNIS_KEYMAP_MOCK_H
#define IGNIS_KEYMAP_MOCK_H

/* Includes ------------------------------------------------------------------*/
#include "fff.h"
#include "ignis_keymap.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
DECLARE_FAKE_VOID_FUNC(ignis_keymap_register_callback, ignis_keymap_callback_t)

inline void ignis_keymap_mock_reset_fakes(void) { RESET_FAKE(ignis_keymap_register_callback); }
#ifdef __cplusplus
}
#endif
#endif  // IGNIS_KEYMAP_MOCK_H
