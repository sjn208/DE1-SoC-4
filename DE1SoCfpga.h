#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <cmath>
#ifndef DE1SOCFPGA_H
#define DE1SOCFPGA_H

using namespace std;
// Physical base address of FPGA Devices 
const unsigned int LW_BRIDGE_BASE = 0xFF200000; // Base offset 
// Length of memory-mapped IO window 
const unsigned int LW_BRIDGE_SPAN = 0x00005000; //Address map size 
// Cyclone V FPGA device addresses 
const unsigned int LEDR_BASE = 0x00000000; // Leds offset 
const unsigned int SW_BASE = 0x00000040; // Switches offset 
const unsigned int KEY_BASE = 0x00000050; // Push buttons offset 

// added offsets
const unsigned int HEX3_HEX0_BASE  = 0x00000020;  // Data Reg1 offset
const unsigned int HEX5_HEX4_BASE  = 0x00000030;  // Data Reg2 offset

//Base class containing only read and writes to the board's memory.
class DE1SoCfpga{
    char *pBase;
    int fd;
public:
    DE1SoCfpga(){
        fd = open( "/dev/mem", (O_RDWR | O_SYNC));
        if (fd == -1) // check for errors in openning /dev/mem
        {
            cout << "ERROR: could not open /dev/mem..." << endl;
            exit(1);
        }
        // Get a mapping from physical addresses to virtual addresses
        char *virtual_base = (char *)mmap (NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd,
 LW_BRIDGE_BASE);
        if (virtual_base == MAP_FAILED) // check for errors
        {
            cout << "ERROR: mmap() failed..." << endl;
            close (fd); // close memory before exiting
            exit(1); // Returns 1 to the operating system;
        }
        pBase = virtual_base;
    }
    ~DE1SoCfpga(){
        if (munmap (pBase, LW_BRIDGE_SPAN) != 0)
        {
            cout << "ERROR: munmap() failed..." << endl;
            exit(1);
        }
        close (fd); // close memory
    }

    //Writes the value given to a location in memory determined by the offset provided
    void RegisterWrite(unsigned int reg_offset, int value);
	
    //Returns the value of the location in memory based on the offset provided
    int RegisterRead(unsigned int reg_offset);

};

#endif
