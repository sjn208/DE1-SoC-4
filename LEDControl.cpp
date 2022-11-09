#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <cmath>
#include "DE1SoCfpga.h"
#include "LEDControl.h"

using namespace std;



    //Takes in the LED number to be modified, the state to which the LED
    //should be set, and the current value of each LED.
    void LEDControl::Write1Led(int ledNum, int state, int value){

	  //Utilizes bitmasking to change only the LED requested
        int pos = pow(2, ledNum);
        if (!state)
            value = value &  ~pos;
        else
            value = value | pos;
        cout << endl << value << endl;
	  //Sends the updated value to the WriteAllLeds function to update LED state
        WriteAllLeds(value);
    }

    //Sets the state of the LEDs based on the value passed
    void LEDControl::WriteAllLeds(int value){
        RegisterWrite(LEDR_BASE, value);
    }
	
    //Takes in the number of the switch and outputs if it is on or off
    void LEDControl::Read1Switch(int switchNum){

        int v;
	  //Gets the value of all the switches
        v = ReadAllSwitches();
	  //Utilizes bitmasking to isolate the switch requested
        v = v & int (pow(2, switchNum));
        v = v >> switchNum;
        cout << endl << "switch value: " << v << endl;
    }

    //Returns the value of all of the switches
    int LEDControl::ReadAllSwitches(){
	
	  //Passes the switch memory offset to return the value of switches from RegisterRead
        int value = RegisterRead(SW_BASE);
        cout << endl << value << endl;
	  //Utilizes bitmasking to only display the values of the 10 switches and not the other 22 bits
        value = value & 1023;
        cout << value << endl;
        return value;
    }

    //Contains a while loop that returns a value based on the push-button that was pressed
    int LEDControl::PushButtonGet() {

	  //Initializes a counter to facilitate the while loop
        int count = 0;
        int keys;
	  
        while(count < 2000){
		//Returns the current value of the push-buttons
            keys = RegisterRead(KEY_BASE);
		//Sleeps to eliminate potential for multiple button detections
            sleep(1);
		//Bitmasks to isolate the 4 buttons memory
            keys = keys & 15;
		
            if (keys){
		    //Returns a value based on the button that was pressed
        	    switch(keys){
			  //The case conditions are because of what the binary value when each individual button is pressed
                    case(1):cout << "Pressed 0"; return 0;
                    case(2):cout << "Pressed 1"; return 1;
                    case(4):cout << "Pressed 2"; return 2;
                    case(8):cout << "Pressed 3"; return 3;
			  //If the value is anything other than the values above, it is guranteed that multiple buttons were activated
                    default:cout << "Pressed multiple buttons"; return 4;
                }
            }
		//Progresses the loop
            count ++;
            cout << endl << count;
        }
	  //If the while loop ends with no input, the program returns that no button was pressed
        cout << "No button pressed" << endl;
        return -1;
    }
    
    
