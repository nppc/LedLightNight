#include "gen.h"
#include "main.h"

volatile bit delay_tick;

void delay_ms(uint16_t ms_count)
 {
  uint16_t i;
  delay_tick = false;
  for(i=0; i<ms_count;i++){
      while(!delay_tick);
      delay_tick = false;
  }
 }

void timer_routines(void){
  if(TMR2CN_TF2H){
    TMR2CN_TF2H = false;
	
	//delay functions
	delay_tick = true;
  }
}
