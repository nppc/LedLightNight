#include "main.h"
#include "InitDevice.h"
#include "pwm.h"

void initHW(void){
  // PCA - don't start yet
  PCA0CN    = PCA0CN_CR__RUN;
  PCA0MD    = PCA0MD_CPS__SYSCLK;
  PCA0CPL0 = (0xff & PWM_HIGH);
  PCA0CPL0 = (0xff & (PWM_HIGH >> 8));
  PCA0CPM0  = PCA0CPM0_ECOM__ENABLED | PCA0CPM0_MAT__ENABLED | PCA0CPM0_TOG__ENABLED | PCA0CPM0_ECCF__ENABLED;// 0x4D;
  EIE1     |= EIE1_EPCA0__ENABLED;

  // timers setup
  CKCON     = CKCON_T2ML__SYSCLK;
  // Timer2 configuration for delays
  TMR2CN    = TMR2CN_TR2__RUN;
  // 1ms period
  TMR2RLL   = 0x4C;
  TMR2RLH   = 0xA0;
  //IE_ET2 = false; // do not fire interrupt routine. We will monitor flag in main loop

  // Set internal oscillator to run at its maximum frequency
   OSCICN = OSCICN_IOSCEN__ENABLED |
            OSCICN_IFCN__HFOSC_DIV_1;

   // Port init
#ifdef C8051F530
   P1MDOUT   = P1MDOUT_B5__PUSH_PULL;
   P0SKIP    = 0xFF;
   P1SKIP    = 0x1F;
#else
   P0MDOUT   = P0MDOUT_B5__PUSH_PULL;
   P0SKIP    = 0x1F; //C8051F520
#endif

   //XBR1 = XBR1_PCA0ME__CEX0 | XBR1_XBARE__ENABLED;
   XBR1 = XBR1_XBARE__ENABLED;

}
