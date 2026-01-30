/**
 ********************************************************************************
 * @file    ignis_keymap.h
 * @author  Massimiliano Ianniello
 * @date    29/01/26
 ********************************************************************************
 */
#ifndef IGNIS_KEYMAP_H
#define IGNIS_KEYMAP_H

/* Includes ------------------------------------------------------------------*/
/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/* Typedefs ------------------------------------------------------------------*/
typedef enum ignis_keymap_key_e
{
    IGNIS_KEYMAP_KEY_0 = 0,
    IGNIS_KEYMAP_KEY_1 = 1,
    IGNIS_KEYMAP_KEY_2 = 2,
    IGNIS_KEYMAP_KEY_3 = 3,
    IGNIS_KEYMAP_KEY_4 = 4,
    IGNIS_KEYMAP_KEY_5 = 5,
    IGNIS_KEYMAP_KEY_6 = 6,
    IGNIS_KEYMAP_KEY_7 = 7,
    IGNIS_KEYMAP_KEY_8 = 8,
    IGNIS_KEYMAP_KEY_9 = 9,
    IGNIS_KEYMAP_KEY_ENTER,
    IGNIS_KEYMAP_KEY_ESC
} ignis_keymap_key_t;

typedef void (*ignis_keymap_callback_t)(ignis_keymap_key_t key);
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
void ignis_keymap_start(void);
void ignis_keymap_register_callback(ignis_keymap_callback_t callback);

#ifdef __cplusplus
}
#endif
#endif  // IGNIS_KEYMAP_H
