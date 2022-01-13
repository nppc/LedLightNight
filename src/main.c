#include "main.h"
#include "InitDevice.h"
#include "gen.h"
#include "pwm.h"

volatile fader_t fader;
volatile uint8_t fade_ms_cntr = 0;


//-----------------------------------------------------------------------------
// SiLabs_Startup() Routine
// ----------------------------------------------------------------------------
// This function is called immediately after reset, before the initialization
// code is run in SILABS_STARTUP.A51 (which runs before main() ). This is a
// useful place to disable the watchdog timer, which is enable by default
// and may trigger before main() in some instances.
//-----------------------------------------------------------------------------
void SiLabs_Startup (void)
{
   PCA0MD &= ~PCA0MD_WDTE__ENABLED;    // Disable the watchdog timer;
}
 

//-----------------------------------------------------------------------------
// main() Routine
//-----------------------------------------------------------------------------
void main (void)
{
  
  initHW();

  init_pwm();

  fader.cntr_step = 0;
  fader.state = FADE_NOTHING;
  
  // debug
  TCON_TR1 = false;
  TCON_TR1 = true;

  IE_EA = true; // Enable global interrupts

  delay_ms(100);

   while (true)
   {
     timer_routines();
   }
}
