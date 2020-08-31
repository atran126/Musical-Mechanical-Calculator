/* Source file for the button class */
#include "Arduino.h"
#include "Button.h"

  /* The constructor initializes variables */
  Button::Button(int mult)
  {
    times_pressed = 0;
    multiplier = mult;
  }
  
      /* Adds how many times the button has been pressed
       *  If the button has not been pressed when the function is called,
       *  the value is zero, so it doesn't matter
       */
      int Button::press_button(int val)
      {
        times_pressed += val;
      }
  
      /* Returns the final value for the button
       *  Ex: If the user pressed 2 + 2 + 2 + 1 + 1,
       *  the final value for the two button is six
       */
      int Button::get_val() 
      {
        int val = times_pressed*multiplier;
        return val;
      }

 
  
}
