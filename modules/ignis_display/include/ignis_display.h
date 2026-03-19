/**
 ********************************************************************************
 * @file    ignis_display.h
 * @author  Massimiliano Ianniello
 * @date    27/02/26
 ********************************************************************************
 */
#ifndef IGNIS_DISPLAY_H
#define IGNIS_DISPLAY_H

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
void ignis_display_init(void);
void ignis_display_send_numeric_data(const uint8_t *data, bool time);
void ignis_display_send_string(const char *text);

#ifdef __cplusplus
}
#endif
#endif  // IGNIS_DISPLAY_H
