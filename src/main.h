#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <SI_C8051F530_Register_Enums.h>

#define C8051F530

#define STEPFADEIN 15 // step for values in led array
#define STEPFADEOUT 600 // step for values in led array
#define LEDONTIME 30 // seconds while LED is on when movement detected

#ifdef C8051F530
SI_SBIT(PIN_PWM, SFR_P1, 5);
SI_SBIT(PIN_ONOFF, SFR_P1, 6);
#else
SI_SBIT(PIN_PWM, SFR_P0, 5);
SI_SBIT(PIN_ONOFF, SFR_P0, 3);
#endif

extern uint16_t PWM_HIGH;
extern uint16_t PWM_LOW;

extern int16_t stp;

extern bit ms_tick, LEDstate, dir, fade;

#endif /* SRC_MAIN_H_ */
