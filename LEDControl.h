#include "DE1SoCfpga.h"
#ifndef LEDCONTROL_H
#define LEDCONTROL_H

using namespace std;



//Derived class of De1-SoCfpga contains all user based input and logic of LEDs
class LEDControl : DE1SoCfpga{
private:
  unsigned int leds_regValue;
  
public:
    LEDControl(){
    
      leds_regValue = 0;
    }

    //Takes in the LED number to be modified, the state to which the LED
    //should be set, and the current value of each LED.
    void Write1Led(int ledNum, int state, int value);

    //Sets the state of the LEDs based on the value passed
    void WriteAllLeds(int value);
	
    //Takes in the number of the switch and outputs if it is on or off
    void Read1Switch(int switchNum);

    //Returns the value of all of the switches
    int ReadAllSwitches();

    //Contains a while loop that returns a value based on the push-button that was pressed
    int PushButtonGet();
    
    ~LEDControl() {
      cout << "Closing LEDs, Switches, & Buttons..." << endl;
    }

};

#endif
