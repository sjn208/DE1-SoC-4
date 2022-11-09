#include <iostream>
#include "DE1SoCfpga.h"

void DE1SoCfpga::RegisterWrite(unsigned int reg_offset, int value) {
	 * (volatile unsigned int *)(pBase + reg_offset) = value;
        //volatile prevents the compiler from optimizing code
};

int DE1SoCfpga::RegisterRead(unsigned int reg_offset) {
	return * (volatile unsigned int *)(pBase + reg_offset);
};

