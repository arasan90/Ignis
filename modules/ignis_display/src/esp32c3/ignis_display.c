/**
 ********************************************************************************
 * @file    ignis_display.c
 * @author  Massimiliano Ianniello
 * @date    27/02/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "ignis_display.h"

#include "driver/gpio.h"
#include "esp_rom_sys.h"
#include "ignis_display_priv.h"
#include "tm1637.h"

/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
ignis_display_ctx_t ignis_display_ctx = IGNIS_DISPLAY_CTX_INIT();
tm1637_handle_t     display;

/* Function Definitions ------------------------------------------------------*/
void ignis_display_init(void)
{
    if (!ignis_display_ctx.initialized)
    {
        const tm1637_config_t config = {.clk_pin = IGNIS_DISPLAY_PIN_CLK, .dio_pin = IGNIS_DISPLAY_PIN_DATA, .bit_delay_us = 100};
        tm1637_init(&config, &display);
        tm1637_set_brightness(display, 7, true);
        tm1637_write_string(display, "----");
        ignis_display_ctx.initialized = true;
    }
}
void ignis_display_send_data(const uint8_t data[4], const bool time)
{
    for (int i = 0; i < 4; i++)
    {
        if (0xFF == data[i])
        {
            ignis_display_ctx.display_digits[i] = '-';
        }
        else
        {
            ignis_display_ctx.display_digits[i] = 0x30 + data[i];
        }
    }
    char buffer[6] = {0};
    snprintf(buffer, sizeof(buffer), "%c%c%c%c", ignis_display_ctx.display_digits[0], ignis_display_ctx.display_digits[1], ignis_display_ctx.display_digits[2],
             ignis_display_ctx.display_digits[3]);
    tm1637_write_string(display, buffer);
    if (time && 0xFF != data[1])
    {
        uint8_t segments = tm1637_encode_digit(data[1]);
        segments |= 0x80;
        tm1637_set_segments(display, &segments, 1, 1);
    }
}