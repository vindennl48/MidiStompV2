#include "ShiftRegisterPWM.h"


// One static reference to the ShiftRegisterPWM that was lastly created. Used for access through timer interrupts.
ShiftRegisterPWM *ShiftRegisterPWM::singleton = NULL;

/**
  * The ISR is being used unless the CUSTOM_INTERRUPT macro is defined.
  * That way this library can be used in combination with libraries that rely on Timer 1.
  * See CustomTimerInterrupt example sketch.
  */
#ifndef ShiftRegisterPWM_CUSTOM_INTERRUPT
  //Timer 1 interrupt service routine (ISR)
  ISR(TIMER1_COMPA_vect) { // function which will be called when an interrupt occurs at timer 1
    cli(); // disable interrupts (in case update method takes too long)
    ShiftRegisterPWM::singleton->update();
    sei(); // re-enable
};
#endif

