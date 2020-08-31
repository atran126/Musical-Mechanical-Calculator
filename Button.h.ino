/* Header file for the button class */

/* Ensures no errors if user includes the class twice */
#ifndef Button_h
#define Button_h
#include "Arudino.h"

class Button {
 
  public:     
     Button(int mult);     
     int press_button(int val);  
     int get_val();
   private:
    int times_pressed;
    int multiplier;
  
     
  
};
#endif
