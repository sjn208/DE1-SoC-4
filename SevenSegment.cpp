#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "DE1SoCfpga.h"
#include "SevenSegment.h"


using namespace std;

//Takes in a decimal number, an array to hold the resulting indices of the dec_bit_values, and a pointer to size of hexarr
void dec_to_hex(int dec, int hexarr[], int *size) {
    int count = 0;
    while(dec > 0) {
//        cout << "dec " << dec << endl;
        hexarr[count] = dec / (pow(16, 5-count));

//        cout << "hexarr[" << count << "] : " << hexarr[count] << endl;
        dec = dec % (int (pow(16, 5-count)));
//        cout << "Remainder = new dec : " << dec << endl;
        count++;
    }
//resets count back to 0
    count = 0;
    while (true) {
//Checks when the first non zero index of the array occurs
        if (hexarr[count] == 0) {
            count++;
        }
        else {
//Subtracts the number of zeroes preceeding the hex indices
            *size = *size-count;
            break;
        }
    }
//If the size is found to be 0, make it 1 to allow the program to print 0
	if (*size == 0){
		*size = 1;
	}

}

//Turns off each display
void SevenSegment::Hex_ClearAll(){
    RegisterWrite(HEX3_HEX0_BASE, 0);
    RegisterWrite(HEX5_HEX4_BASE, 0);
};

//Clears a specific display as determined by the index
void SevenSegment::Hex_ClearSpecific(int index){
    int m = 255, value;
    
    //Determines which register offset to use based on the index passed to the function
    if (index > 3)
    {
        //bitshifts 8 ones in binary based on the display to be cleared
	  m = m << 8*index;
	  //Determines the current values of each display in this set
        value = RegisterRead(HEX5_HEX4_BASE);
	  //takes the current value and bitwise ands it with the complement of m
        value = value & ~m;
	  //Writes it to the register
        RegisterWrite(HEX5_HEX4_BASE, value);
    }
    else
    {
	  //bitshifts the index - 4 because the second set of displays starts at display number 4
	  m = m << 8*(index-4);
        value = RegisterRead(HEX3_HEX0_BASE);
        value = value & ~m;
        RegisterWrite(HEX3_HEX0_BASE, value);
    }
};

//Writes a specific value to a single display
void SevenSegment::Hex_WriteSpecific(int display_id, int value){
     if (display_id > 3)
    {
	  //Clears the display to be written to
        Hex_ClearSpecific(display_id);
	  //Reads the current value of the register offset
        int v = RegisterRead(HEX5_HEX4_BASE);
	  //Gets the bit value corresponding to the value index, and bitshifts it to the display to be written to
        value = dec_bit_values[value] << 8*(display_id-4);
	  //bitwise ors v with value and writes to the register
        v = v | value;
        RegisterWrite(HEX5_HEX4_BASE, v);
    }
    else
    {
	  //Clears the display to be written to
        Hex_ClearSpecific(display_id);
	  //Gets current value of the offset
        int v = RegisterRead(HEX3_HEX0_BASE);
	  //Updates the value of the offset and writes it out
        value = dec_bit_values[value] << 8*display_id;
        v = v | value;
        RegisterWrite(HEX3_HEX0_BASE, v);
    }
};

//Writes a number to the displays ranging from -FFFF to FFFFF
void SevenSegment::Hex_WriteNumber(int number){
    //Initializes variables to be passed to dec_to_hex and to pass to register write
    int value1 = 0, value2 = 0, harr[6] = {0};
    int size = 6;
    //Determines if the number passed to the function is negative
    bool neg;
    if (number<0)
        neg = true;
    else
        neg = false;

    //gets the positive version of the number
    number = abs(number);
    //Gets the indices of the dec_bit_values to be printed and the size / number of displays needed to display it
    dec_to_hex(number, harr, &size);

    if (neg)
    {
	  //If the number is negative, shifts the negative symbol bit values and assigns to value2
        Hex_ClearAll();
        value2 = neg_symbol << 8;
        
	  //loops through the indices based on size
        for (int i = 0; i < size; i++){
		//returns the bit value to be placed at one display
            int temp = dec_bit_values[harr[6-size+i]];
		//If i is less than 4, then dataReg1 is used
            if (i<4)
            {
                temp = temp << 8*(size-1-i);
                value1 = value1 | temp;
            }
		//If i is greater, dataReg2 is used
            else
            {
                temp = temp << 8*(i-4);
                value2 = value2 | temp;
            }
		dataReg1 = value1;
		dataReg2 = value2;
		//Takes the updated dataReg1 and dataReg2 values and writes to the respective registers
            RegisterWrite(HEX3_HEX0_BASE, dataReg1);
            RegisterWrite(HEX5_HEX4_BASE, dataReg2);
        }
    }
    else
    {
	  //Behaves the same as the beginning of the if statement without the added neg symbol
        Hex_ClearAll();
        for (int i = 0; i < size; i++){
            int temp = dec_bit_values[harr[6-size+i]];
		
		//Writes to dataReg1 if i is less than 4
            if (i<4)
            {
                temp = temp << 8*(size-1-i);
                value1 = value1 | temp;
            }
		
		//Writes to value2 if i is greater than 3
            else
            {
                temp = temp << 8*(i-4);
                value2 = value2 | temp;
            }
		//Writes values to the register offset
		dataReg1 = value1;
		dataReg2 = value2;
            RegisterWrite(HEX3_HEX0_BASE, dataReg1);
            RegisterWrite(HEX5_HEX4_BASE, dataReg2);
        }
    }
};
