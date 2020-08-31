/* Abbie Tran
 *  code.ino: Arduino file that controls components
 *  Lab 9: Mechanical Musical Calculator
 */

/* The button class keeps track of how many times a button
 *  has been pressed and its value (1, 2, 3, etc.)
 *  Servo library used to control two motors
 */
 #include <Servo.h>
 #include <Button.h>

// Tone constants
// Note constants from Brett Hagman of Arduino
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
int pitches []  = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4};

/* Set up buttons with multiplier,pin, if a plus value, and tone*/
Button one(1, 2, false, pitches[0]);
Button two(2, 4, false, pitches[1]);
Button three(3, 5, false, pitches[2]);
Button plus(0, 6, true, 0);

// Set up pins and motors
int led_pin = 8;
int lmpin = 9;
int rmpin = 10;
int equal = 7;
int buzz_pin = 12;
int clear_pin = 13;
Servo rmotor;
Servo lmotor;

void setup() {

  /* Set up input pinsl*/
  
   pinMode(equal, INPUT);
   pinMode(clear_pin, INPUT);   
   pinMode(led_pin, OUTPUT); 
   pinMode(rmpin, OUTPUT);
   pinMode(lmpin, OUTPUT);

   // Attach and set initial motor angles
   rmotor.attach(rmpin);
   lmotor.attach(lmpin);
   // Initially set rmotor to 90
   rmotor.write(10);
   lmotor.write(27);
   
  Serial.begin(115200);

}

void loop() { 

  /* Count how many times each button has been pressed */

    one.press_button(digitalRead(one.get_pin()));
    two.press_button(digitalRead(two.get_pin()));
    three.press_button(digitalRead(three.get_pin()));
    plus.press_button(digitalRead(plus.get_pin()));
 
  
  /* Print "a" to serial monitor to clear screen and rest buttons to zero*/
   if(digitalRead(clear_pin) == HIGH) {
     tone(buzz_pin, pitches[6], 100);
      Serial.println("a\n");      
       one.reset();
       two.reset();
       three.reset();
  }
  /* When equal button is pressed, the value is computed and all variables reset to zero */
 
  if (digitalRead(equal) == HIGH) {
     int final_val = one.get_val() + two.get_val() + three.get_val();
     if(final_val != 0) {
      Serial.print("=");
      Serial.println(final_val);

   
      move_motor(final_val);  
      
      
      /* Reset all button presses to zero */
       one.reset();
       two.reset();
       three.reset();
     }          
  }
  
  delay(5); 
}


// Control motor motion to let one sphere down at a time
void move_motor (int times) {
  
  for(int i = 0; i < times; i++) {
    // Open left motor
    lmotor.write(3);
    delay(200);    

    // Close left motor
    lmotor.write(27);
    
    

    // Open and close right motor to let next ball down
    rmotor.write(38);
    delay(150);
    rmotor.write(10);
    blink_and_play(times);
  } 
}

// Blinks LED and play a tone
void blink_and_play(int num) {
  // Blink LED 
   digitalWrite(led_pin, HIGH);
   tone(buzz_pin, pitches[num - 1], 100);
   digitalWrite(led_pin, LOW);
   delay(100);
  
}
