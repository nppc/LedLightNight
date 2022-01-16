#include "main.h"
#include "InitDevice.h"
#include "gen.h"
#include "pwm.h"

volatile uint16_t PWM_HIGH;
volatile uint16_t PWM_LOW;

volatile int16_t stp = STEPFADEIN;

// LEDstate: 1 - LED is ON, 0 - LED is OFF
// ms_tick: every 1ms sets to 1.
// dir:  1 - fadeIN, 0 - fadeOUT
// fade: 1 - fade is in progress, 0 - fade is finished
volatile bit ms_tick = false, LEDstate = false, dir = true, fade = false;

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
  int16_t i=0;
  dir = 1;
  fade = false;

  initHW();

  set_pwm(MINPWM);
  PIN_PWM = 0;

  
  //IE_EA = true; // Enable global interrupts

   while (true)
   {
       timer_routines();

       LEDstate = setLedState();

       if(LEDstate){
           if(i!=sizeof(num_led_data)/2*STEPFADEIN){ // if not at max, enable fade if not yet enabled
               if(!fade || !dir){
                   i=map(i,sizeof(num_led_data)/2*STEPFADEOUT,sizeof(num_led_data)/2*STEPFADEIN);
                   startFade(1);
               }
           }else if(fade){ //stop fade and set brightness to 100%
               stopFade();
               PIN_PWM = 1;
           }
       }else{
           if(i!=0){ // if not at min, enable fade if not yet enabled
               if(!fade || dir){
                   i=map(i,sizeof(num_led_data)/2*STEPFADEIN,sizeof(num_led_data)/2*STEPFADEOUT);
                   startFade(0);
               }
           }else if(fade){ //stop fade and set brightness to 0%
               stopFade();
               PIN_PWM = 0;
           }
       }

       if(ms_tick){
         ms_tick = false;

         if(fade){
             set_pwm(getPWMfromN(i,stp));
             if(dir){
                 i++;
             }else{
                 i--;
             }
         }
       }
   }
}
