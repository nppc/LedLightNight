#include "main.h"
#include "InitDevice.h"
#include "gen.h"

volatile bit timer1ms_tick;

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
  
  fader.cntr_step = 0;
  fader.state = FADE_NOTHING;

  initHW();

  TCON_TR1 = 0;
  TCON_TR1 = 1;

  IE_EA = 1; // Enable global interrupts

  delay_ms(100);

   while (1)
   {
     timer_routines();
   }
}
