/**
 ********************************************************************************
 * @file    ignis_buzzer.h
 * @author  Massimiliano Ianniello
 * @date    20/03/26
 ********************************************************************************
 */
#ifndef IGNIS_BUZZER_H
#define IGNIS_BUZZER_H

/* Includes ------------------------------------------------------------------*/
/* Macros --------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {



#endif
/* Typedefs ------------------------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
void ignis_buzzer_start(void);
void ignis_buzzer_sound_short_alarm(void);
void ignis_buzzer_sound_long_alarm(void);
void ignis_buzzer_alarm_shutoff(void);

#ifdef __cplusplus
}
#endif
#endif //IGNIS_BUZZER_H
