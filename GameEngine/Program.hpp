#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "Types.hpp"
#include "Display.hpp"

//======= FUNCTIONS ======
#ifdef EMULATE
	#include "Serial.hpp"
	bool init(STRING fileName, STRING port);
#else
	bool init(STRING fileName);
#endif

bool next();
void close();

CURSOR checkpoint();
bool jump(CURSOR location);

void display(); // Update display
void input(); // Update Input

// Memory
bool validAddress(INTEGER address); 
void write(INTEGER address, INTEGER value);
INTEGER read(INTEGER address);

// Registy
bool validRegistry(INTEGER address);
void writeRegistry(INTEGER address, CURSOR cursor);
CURSOR readRegistry(INTEGER address);

// Argument List
INTEGER arg(INTEGER address);

#endif
