/**
 ********************************************************************************
 * @file    ignis_buzzer_mock.h
 * @author  Massimiliano Ianniello
 * @date    20/03/26
 ********************************************************************************
 */
#ifndef IGNIS_BUZZER_MOCK_H
#define IGNIS_BUZZER_MOCK_H

/* Includes ------------------------------------------------------------------*/
#include "fff.h"
#include "ignis_buzzer.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
/* Typedefs ------------------------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
    DECLARE_FAKE_VOID_FUNC(ignis_buzzer_start)
    DECLARE_FAKE_VOID_FUNC(ignis_buzzer_sound_short_alarm)
    DECLARE_FAKE_VOID_FUNC(ignis_buzzer_sound_long_alarm)
    DECLARE_FAKE_VOID_FUNC(ignis_buzzer_alarm_shutoff)

#ifdef __cplusplus
}
#endif
#endif //IGNIS_BUZZER_MOCK_H