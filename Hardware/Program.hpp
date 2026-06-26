#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#define STRING const char*
#define INTEGER short int // 16 bit integer
#define ADDR uint8_t
#define HEAP_SIZE 64      // 64 heap memory addresses

extern INTEGER* Heap;     	// Heap memory
extern STRING PC;			// Program Counter

bool init(STRING fileName);
bool next();
void close();

#define EMULATE

#ifdef EMULATE 
	#include <fstream>
	#include <string>

	using namespace std;

	extern ifstream File;
#else

#endif

#endif
