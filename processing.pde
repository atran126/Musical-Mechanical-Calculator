  /* Processing file
  Controls visual output on screen
  */
  
  import processing.serial.*; // add the serial library
  Serial myPort; // define a serial port object to monitor
  
  // Initialize global variables
  int text_pos = 0;
  int total = 6;
  int rad = 60;
  int blue_circles = 0;
  
  void setup() {
    size(1200, 600); // set the window size
    println(Serial.list()); // list all available serial ports
    myPort = new Serial(this, Serial.list()[0], 115200); // define input port
    myPort.clear(); // clear the port of any initial junk
    
    // Draw intial triangle ramp with circles
    background(255);
    stroke(255);
    fill(242, 221, 162);
    triangle(0,600,0,300,400,600);
      
      // Draw six red circles
      for(int i = 0; i < total; i++) {
        fill(196, 18, 2);
        int x = 30 + (67 * i);
        int y = 280 + (50 * i);
        ellipse(x, y, rad,rad);
      }
  }
  
  
  void draw () {
    
    while (myPort.available () > 0) { // make sure port is open
      
      String inString = myPort.readStringUntil('\n'); 
      inString = trim(inString);
      
      // Redraw triangle base with circles on top      
      fill(242, 221, 162);
      triangle(0,600,0,300,400,600);
      
      // Draw six red circles
      for(int i = 0; i < total; i++) {
        fill(196, 18, 2);
        int x = 30 + (67 * i);
        int y = 280 + (50 * i);
        ellipse(x, y, rad,rad);
      }
       
      // Read in string and call methods
      if (inString != null && !inString.equals("\n") && inString.length() > 0) { // ignore null strings
        print_circles(inString);
        print_calculator(inString);            
   
      }    
    }
  }
  
  // Prints "Calculator" Input
  void print_calculator(String inString) {
  
       
      // Clear screen on a
       fill(0);
        if(inString.equals("a")) {                 
          text_pos = 0;
          background(255); 
          blue_circles = 0;
        }
        
        else {
          textSize(60);
          
          if(inString.charAt(0) == '=') {
            text('=', text_pos, 100);
            text_pos += 80;
            text(inString.charAt(1), text_pos, 100);
          }
          
          else { 
            text(inString, text_pos, 100);
            text_pos += 80;
          }
        }
        
  }
  

  // Prints circles on triangle and changes color based on input
  void print_circles(String inString) {
    
    int val = 0;
    int new_circles = blue_circles;
    char input = inString.charAt(0);
    
    // Change input circles to blue
    if(input == '1' || input == '2' || input == '3' ||input == '+') {
      // Accomodate char to int ASCII conversion
      
      if(input != '+') {      
        val = int(input) - 48;
        new_circles = val + blue_circles;
      }
 
      
      // Mark val circles blue
      for(int i = 0; i < new_circles; i++) {
        fill(56, 174, 242);
        ellipse(365 - (67 * i), 530 - (50 * i), rad,rad);
      }
      blue_circles += val;
    }
    
    else if(input == '=') {
      int output = int(inString.charAt(1) - 48);
      blue_circles = 0;
      
      // Roll output circles down the ramp   
      
      
      // Create white circles to block out previous circles
      for(int i = 0; i < total ; i++) {
        //println("Creating circle");
        stroke(255);
        fill(255);
        ellipse(365 - (67 * i), 530 - (50 * i), rad,rad);
        
      }
      
      // Print remaining red circles
      for(int i = 0; i < total - output; i++) {       
        fill(196, 18, 2);          
        ellipse(365 - (67 * i), 530 - (50 * i), rad,rad);        
      }
      
      // put total blue circles next to ramp
      for(int i = 0; i < output; i++) {        
       fill(56, 174, 242);
        ellipse(600 + (80 * i), 530 , rad,rad);
      } 
    }
 
  }
  
