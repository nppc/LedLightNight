#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <SI_C8051F530_Register_Enums.h>

#define FADE_DELAY 3
#define LEDONINTERVAL 60 // seconds

typedef enum {FADE_OUT, FADE_IN, FADE_NOTHING} fader_e;
typedef struct {
  uint8_t cntr_step; // current fade step (0-255)
  fader_e state; // should we change light?
} fader_t;

extern fader_t fader;
extern uint8_t fade_ms_cntr;

SI_SBIT(PIN_PWM, SFR_P1, 5);
SI_SBIT(PIN_ONOFF, SFR_P1, 6);

#endif /* SRC_MAIN_H_ */
