#include "pwm.h"
#include "main.h"

// for 13 bit pwm we are useing timer0/1
// pwm change is achieving by pausing timer 0 or 1

volatile int16_t pwm_val = MINPWM; // initial PWM value (min)

void init_pwm(void){
  PIN_PWM = 0;
  TL0       = MINPWM; // set initial value
  TCON      = TCON_TR0_ENABLED | TCON_TR1_ENABLED; // start timers
}

bit inc_pwm(void){
	if(pwm_val >= MAXPWM) return 0; // increment is not successful
	// only change pwm if we are far from overflow interrupt
	while(TL0>=MAXPWM || TL1>=MAXPWM);
	TCON_TR1 = false;
	TCON_TR1 = true;
	pwm_val++;
	return 1; // succeeded
}

bit dec_pwm(void){
	if(pwm_val <= MINPWM) return 0; // increment is not successful
	// only change pwm if we are far from overflow interrupt
	while(TL0>=MAXPWM || TL1>=MAXPWM);
	TCON_TR0 = false;
	TCON_TR0 = true;
	pwm_val--;
	return 1; // succeeded
}
