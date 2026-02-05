/**
 ********************************************************************************
 * @file    ignis_keymap.c
 * @author  Massimiliano Ianniello
 * @date    29/01/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "ignis_keymap.h"

#include <string.h>

#include "cJSON.h"
#include "ignis_keymap_priv.h"
#include "k_ghost_io.h"

/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
ignis_keymap_ctx_t ignis_keymap_ctx = {0};

/* Function Definitions ------------------------------------------------------*/
void ignis_keymap_start(void)
{
    k_ghost_io_init();
    if (K_GHOST_REGISTER_RET_CODE_ERROR != k_ghost_io_register_interface("keymap", NULL, NULL, NULL))
    {
        // TODO
    }
}
void ignis_keymap_register_callback(const ignis_keymap_callback_t callback) { (void)callback; }

int ignis_keymap_host_interface_callback(const cJSON *input_data_p, void *user_data_p)
{
    (void)user_data_p;
    int    ret_code  = -1;
    cJSON *data_item = cJSON_GetObjectItem(input_data_p, "data");
    if (data_item)
    {
        cJSON *key_item = cJSON_GetObjectItem(data_item, "key");
        if (key_item && cJSON_IsString(key_item) && ignis_keymap_ctx.generic_ctx.callback)
        {
            ignis_keymap_key_t key = ignis_keymap_translate_key_string(key_item->valuestring);
            if (IGNIS_KEYMAP_KEY_INVALID != key)
            {
                ignis_keymap_ctx.generic_ctx.callback(ignis_keymap_translate_key_string(key_item->valuestring));
                ret_code = 0;
            }
        }
    }
    return ret_code;
}

ignis_keymap_key_t ignis_keymap_translate_key_string(const char *key_string)
{
    ignis_keymap_key_t key = IGNIS_KEYMAP_KEY_ESC;
    switch (key_string[0])
    {
        case '0':
            key = IGNIS_KEYMAP_KEY_0;
            break;
        case '1':
            key = IGNIS_KEYMAP_KEY_1;
            break;
        case '2':
            key = IGNIS_KEYMAP_KEY_2;
            break;
        case '3':
            key = IGNIS_KEYMAP_KEY_3;
            break;
        case '4':
            key = IGNIS_KEYMAP_KEY_4;
            break;
        case '5':
            key = IGNIS_KEYMAP_KEY_5;
            break;
        case '6':
            key = IGNIS_KEYMAP_KEY_6;
            break;
        case '7':
            key = IGNIS_KEYMAP_KEY_7;
            break;
        case '8':
            key = IGNIS_KEYMAP_KEY_8;
            break;
        case '9':
            key = IGNIS_KEYMAP_KEY_9;
            break;
        default:
            if (0 == strcmp(key_string, "enter"))
            {
                key = IGNIS_KEYMAP_KEY_ENTER;
            }
            else if (0 == strcmp(key_string, "esc"))
            {
                key = IGNIS_KEYMAP_KEY_ESC;
            }
            else
            {
                key = IGNIS_KEYMAP_KEY_INVALID;
            }
            break;
    }
    return key;
}
