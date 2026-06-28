#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <cstdint>
#include "Serial.hpp"
#include "Control.hpp"

#define EMULATE

#ifdef EMULATE 
	#include <fstream>
	#include <string>

	#define CURSOR std::streampos
#else
	#define CURSOR uint_8

#endif

//======= DATA ======

#define STRING const char*
#define INTEGER short int	// 16 bit integer
#define ADDR uint8_t
#define HEAP_SIZE 64      	// 64 heap memory addresses
#define REGISTRY_SIZE 16  	// 16 Functions Possible

extern INTEGER* Heap;     	// Heap Memory
extern STRING PC;			// Program Counter
extern CURSOR* Registry;	// Fuction Registry

//======= FUNCTIONS ======
void update();
bool next();
CURSOR checkpoint();
bool jump(CURSOR location);
void close();

// Memory
bool validAddress(INTEGER address); 
void write(ADDR address, INTEGER value);
INTEGER read(ADDR address);

// Registy
bool validRegistry(INTEGER address);
void writeRegistry(ADDR address, CURSOR cursor);
CURSOR readRegistry(ADDR address);

#ifdef EMULATE
	bool init(STRING fileName, STRING port);
#else
	bool init(STRING fileName);
#endif


#endif
