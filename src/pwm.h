
#ifndef SRC_PWM_H_
#define SRC_PWM_H_

#define MINPWM 10
#define MAXPWM 8080

void init_pwm(void);
bit inc_pwm(void);
bit dec_pwm(void);

#endif /* SRC_PWM_H_ */
