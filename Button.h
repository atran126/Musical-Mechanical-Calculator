/* Buffer.h
Header file for the button class
*/

/* Ensures no errors if user includes the class twice */
#ifndef Button_h
#define Button_h


class Button {

  public:
     Button(int mult, int pin);
     int press_button(int val);
     int get_val();
     int get_pin();
     int reset();
   private:
    int times_pressed;
    int multiplier;
    int pin_num;



};
#endif
