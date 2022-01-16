//#pragma src
#include "pwm.h"
#include "main.h"

const uint16_t code num_led_data[] = {
  54,
  72,
  100,
  138,
  187,
  247,
  319,
  403,
  500,
  610,
  735,
  874,
  1030,
  1203,
  1393,
  1603,
  1833,
  2085,
  2358,
  2656,
  2978,
  3326,
  3699,
  4100,
  4528,
  4983,
  5465,
  5974,
  6508,
  7065,
  7644,
  8242,
  8855,
  9480,
  10113,
  10747,
  11377,
  11997,
  12602,
  13183,
  13733,
  14247,
  14717,
  15136,
  15499,
  15801,
  16036,
  16202,
  16295,
  16314,
};

void set_pwm(int16_t val){
  int16_t pmin, pwm_val;
  pwm_val = val;
  if(val>(PWMPERIOD-PWMSAFEZONE)) pwm_val = PWMPERIOD-PWMSAFEZONE;
  if(val<PWMSAFEZONE) pwm_val = PWMSAFEZONE;
  pmin = PWMPERIOD - pwm_val;
  IE_EA = false; // Disable global interrupts
  PWM_LOW = pmin;
  PWM_HIGH = pwm_val;
  IE_EA = true; // Enable global interrupts
}

int16_t getPWMfromN(uint16_t n, int16_t step){
  int16_t val, d, of;
  uint8_t p = n/step;
  //d= sizeof(num_led_data);
  if(p>=(sizeof(num_led_data)/2)-1) return num_led_data[(sizeof(num_led_data)/2)-1]; //select prelast
  val = num_led_data[p];
  d = num_led_data[p+1]-val;
  of = n % step;
  of = (int32_t)of * d / step;
  return val+of;
}

int16_t map(uint16_t val, int16_t valrange, int16_t newrange){
  return (int32_t)val*newrange/valrange;
}

// dr - direction of dir
void startFade(bit dr){
  dir = dr;
  if(dr){
      stp=STEPFADEIN;
  }else{
      stp=STEPFADEOUT;
  }
  // start PCA0
  XBR1 = XBR1_PCA0ME__CEX0 | XBR1_XBARE__ENABLED;
  fade = true;
}

void stopFade(void){
  // stop PCA0
  XBR1 = XBR1_XBARE__ENABLED;
  fade = false;
}
