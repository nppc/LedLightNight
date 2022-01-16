//#pragma src
#include "main.h"
#include "gen.h"
#include "pwm.h"

// Structure for accessing 16bit number by 2 8 bit (back and forth)
// u16 and u8[] sharing the same memory space
// Usage:
// U16_U8 ptr;
// ptr.u8[0] = high;
// ptr.u8[1] = low;
// ptr.u16 = 16bit;
typedef union
   {
   unsigned short u16;
   unsigned char u8[2];
   } U16_U8;

SI_INTERRUPT (PCA0_ISR, PCA0_IRQn)
  {
    U16_U8 temp;
    if(PCA0CN_CCF0){
        PCA0CN_CCF0 = false;
        if(PIN_PWM){
            temp.u8[0] = PCA0CPH0;
            temp.u8[1] = PCA0CPL0;
            temp.u16 += PWM_HIGH;

            PCA0CPL0 = temp.u8[1];
            PCA0CPH0 = temp.u8[0];
        } else {
            temp.u8[0] = PCA0CPH0;
            temp.u8[1] = PCA0CPL0;
            temp.u16 += PWM_LOW;

            PCA0CPL0 = temp.u8[1];
            PCA0CPH0 = temp.u8[0];
        }

    }
  }

