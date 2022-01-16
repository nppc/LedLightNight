#include "gen.h"

uint16_t cntr_ms_sec=0; // counter for second tick
uint16_t cntrLED_ON_sec=0; // counter for LED

void timer_routines(void){
  if(TMR2CN_TF2H){
    TMR2CN_TF2H = false;

    ms_tick = true;

    // generate seconds tick
    if(cntr_ms_sec==0){
        cntr_ms_sec = 1000;
        if(cntrLED_ON_sec != 0) cntrLED_ON_sec--;
    }else{
        cntr_ms_sec--;
    }
  }
}

bit setLedState(void){
  bit st = true;
  if(PIN_ONOFF){
      cntrLED_ON_sec = LEDONTIME;
  }else if(cntrLED_ON_sec==0){
      st = false;
  }
  return st;
}
