//#pragma src
#include "main.h"
#include "gen.h"

// every 1ms timer
SI_INTERRUPT (TIMER0_ISR, TIMER0_IRQn)
  {
    PIN_PWM = 0;
  }

SI_INTERRUPT (TIMER1_ISR, TIMER1_IRQn)
  {
    PIN_PWM = 1;
  }

SI_INTERRUPT (TIMER2_ISR, TIMER2_IRQn)
  {
    timer1ms_tick = 1;

    // advance delay timer
    delay_tick = 1;

    TMR2CN_TF2H = 0;
  }
