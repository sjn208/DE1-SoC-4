#include <iostream>
#include <cstdlib>
#include "SevenSegment.h"
#include "DE1SoCfpga.h"
#include "LEDControl.h"

/** 
 * Main operates the DE1‐SoC 7‐Segment Displays 
 * This program writes an integer number on the 7‐Segment Displays 
 */ 
int main(void)
{
    // Initializes classes and opens location in memory
    LEDControl *leds = new LEDControl;
    
    // Create a pointer object of the SevenSegment class 
    SevenSegment *display = new SevenSegment; 
    cout << "Program Starting..." << endl;

    // ************** Put your code here **********************
    //Gets initial readings from switches and writes to LEDs

    int v = leds->ReadAllSwitches();
    leds->WriteAllLeds(v);
    display->Hex_WriteNumber(v);

    //Initializes a counter to keep track of the LEDs' state
    int counter = leds->ReadAllSwitches();

    while(true){
	  //Based on the output of the push-buttons performs specific functions
        int ret = leds->PushButtonGet();
        switch(ret){
            case(0):
		    //binary increments the LEDs
                counter ++; break;
            case(1):
		    //binary decrements the LEDs
                counter --; break;
            case(2):
		    //Shifts the LEDs to the right by one using bitwise shifting
                counter = counter >> 1; break;
            case(3):
		    //Shifts the LEDs to the left by one using bitwise shifting
                counter = counter << 1; break;
            case(4):
		    //Resets the LEDs to the current switch orientation
                counter = leds->ReadAllSwitches(); break;
            default: cout << "No valid inputs"; return 0;

        }
	  //Writes to the LEDs based on the updated counter value
        leds->WriteAllLeds(counter);
        display->Hex_WriteNumber(counter);
    }

  delete display;
  delete leds;
} 
