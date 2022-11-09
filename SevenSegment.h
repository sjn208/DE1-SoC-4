#include <iostream>
#include "DE1SoCfpga.h"
#ifndef SEVENSEGMENT_H
#define SEVENSEGMENT_H

using namespace std;
//Stores the bit values to be written for hexadecimal and for the negative symbol
const unsigned int dec_bit_values[16] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111, 119, 124, 57, 94, 121, 113};
const unsigned int neg_symbol = 64;

class SevenSegment:public DE1SoCfpga{
private:
    //Stores the values of the register offsets for the 1st and 2nd set of seven-segment displays
    unsigned int dataReg1;
    unsigned int dataReg2;

public:
    //Constructor writes 0's to the displays
    SevenSegment(){
        Hex_WriteNumber(hex_bit_values[0]);
    }
    //Clears all of the displays, turns them off
    void Hex_ClearAll();
    //Clears a specific display based on the index
    void Hex_ClearSpecific(int index);
    //Writes to a single display with a single value 0 to 15
    void Hex_WriteSpecific(int display_id, int value);
    //Writes a number to the set of displays from -FFFF to FFFFF
    void Hex_WriteNumber(int number);
    //Deconstructor that clears all of the displays
    ~SevenSegment(){
        Hex_ClearAll();
    };
};

#endif
