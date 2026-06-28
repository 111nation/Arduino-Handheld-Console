#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <stdint.h>

#define EMULATE

#ifdef EMULATE 
	#include <fstream>
	#include <string>

	#define CURSOR std::streampos
#else
	#define CURSOR uint_8

#endif

#define STRING const char*
#define INTEGER short int // 16 bit integer
#define ADDR uint8_t
#define HEAP_SIZE 64      // 64 heap memory addresses

extern INTEGER* Heap;     	// Heap memory
extern STRING PC;			// Program Counter


bool init(STRING fileName);
bool next();
CURSOR checkpoint();
bool jump(CURSOR location);
void close();

// Memory
bool validAddress(INTEGER address); 

// Basic I/O
void write(ADDR address, INTEGER value);
INTEGER read(ADDR address);

#endif
