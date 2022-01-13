#include "main.h"
#include "InitDevice.h"

void initHW(void){
  // PCA for debug purposes
  PCA0CN    = 0x40;
  PCA0MD    &= ~0x40;
  PCA0MD    = 0x08;
  PCA0CPM2  = 0x48;

  // timer0 & 1 setup
  // don't start timers yet
  CKCON     = CKCON_T0M_SYSTEMCLOCK | CKCON_T1M_SYSTEMCLOCK;

  // Timer2 configuration for delays
  CKCON     = CKCON_T2ML__SYSCLK;
  TMR2CN    = TMR2CN_TR2__RUN;
  // 1ms period
  TMR2RLL   = 0x4C;
  TMR2RLH   = 0xA0;
  //IE_ET2 = false; // do not fire interrupt routine. We will monitor flag in main loop

  // Set internal oscillator to run at its maximum frequency
   OSCICN = OSCICN_IOSCEN__ENABLED |
            OSCICN_IFCN__HFOSC_DIV_1;

   // Port init
   P1MDOUT   = P1MDOUT_B5__PUSH_PULL;
   //P0SKIP    = 0xFF;
   //P1SKIP    = 0x03;
   XBR1 = XBR1_XBARE__ENABLED;  // Enable crossbar

   // Interrupts priority and enabling timer interrupts
   IP        = IP_PT0__HIGH | IP_PT1__HIGH;
   IE        = IE_ET0__ENABLED | IE_ET1__ENABLED;

}
