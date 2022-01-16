
#ifndef SRC_PWM_H_
#define SRC_PWM_H_
#include "main.h"

#define PWMSAFEZONE 54
#define PWMPERIOD 16384

#define MINPWM PWMSAFEZONE
#define MAXPWM (PWMPERIOD-PWMSAFEZONE)

void set_pwm(int16_t val);
void startFade(bit dr);
void stopFade(void);

extern const uint16_t code num_led_data[50];

int16_t getPWMfromN(uint16_t n, int16_t step);
int16_t map(uint16_t val, int16_t valrange, int16_t newrange);

#endif /* SRC_PWM_H_ */
