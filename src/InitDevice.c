#include "main.h"
#include "InitDevice.h"

void initHW(void){
  // PCA for debug purposes
  PCA0CN    = 0x40;
  PCA0MD    &= ~0x40;
  PCA0MD    = 0x08;
  PCA0CPM2  = 0x48;

  // timer0 & 1 setup
  TCON      = 0x50;
  CKCON     = 0x0C;
  TL0       = 10; // initial value

  // Timer2 configuration for delays
  CKCON     = CKCON_T2ML__SYSCLK;
  TMR2CN    = TMR2CN_TR2__RUN;
  // 1ms period
  TMR2RLL   = 0x4C;
  TMR2RLH   = 0xA0;
  IE_ET2 = 1;

  // Set internal oscillator to run at its maximum frequency
   OSCICN = OSCICN_IOSCEN__ENABLED |
            OSCICN_IFCN__HFOSC_DIV_1;

   // Port init
   P1MDOUT   = P1MDOUT_B4__PUSH_PULL | P1MDOUT_B5__PUSH_PULL; // debug on 1.5
   P0SKIP    = 0xFF;
   P1SKIP    = 0x03;
   XBR1 = XBR1_XBARE__ENABLED;  // Enable crossbar

   // Interrupts priority and enabling timer interrupts
   IP        = IP_PT0__HIGH | IP_PT1__HIGH;
   IE        = IE_ET0__ENABLED | IE_ET1__ENABLED;

}
