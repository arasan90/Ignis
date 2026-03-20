/**
 ********************************************************************************
 * @file    ignis_buzzer_mock.c
 * @author  Massimiliano Ianniello
 * @date    20/03/26
 ********************************************************************************
 */
#include "ignis_buzzer_mock.h"

/* Includes ------------------------------------------------------------------*/
/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Definitions ------------------------------------------------------*/
DEFINE_FAKE_VOID_FUNC(ignis_buzzer_start)
    DEFINE_FAKE_VOID_FUNC(ignis_buzzer_sound_short_alarm)
    DEFINE_FAKE_VOID_FUNC(ignis_buzzer_sound_long_alarm)
    DEFINE_FAKE_VOID_FUNC(ignis_buzzer_alarm_shutoff)