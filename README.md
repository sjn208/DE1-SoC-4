# DE1-SoC-4, Embedded Design (C++)

Main codes to run include Main and MainB cpp files. Makefiles for these are respectively named with 4a and 4b. 

Using the DE1-SoC FPGA board, these programs allow readings of binary data from the set of switches and keys to generate a binary number printed to the LED displays and the equivalent hexadecimal value to the seven-segment displays. 

PREMISE (MainB), with 10 switches and 10 LEDs, switches that are turned on should result in the same order of LEDs turned on. A set of 4 keys can also be used to increment, decrement, bitshift left, bitshift right, and fully reset the binary value displayed by the 10 LEDs, where a light on is equal to 1 and off is 0. Accordingly, the binary value shown at any time by the LEDs will be output as a hexadecimal value to the seven-segment displays on the board. 

PREMISE (Main), using only the seven-segment displays, display values 0-25 in hexadecimal. This code was a prerequisite to developing MainB, to ensure that data values are properly converted and communicated to the data registry.
