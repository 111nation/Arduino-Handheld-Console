#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "Types.hpp"

//======= FUNCTIONS ======
#ifdef EMULATE
	#include "Serial.hpp"
	bool init(STRING fileName, STRING port);
#else
	bool init(STRING fileName);
#endif

void update();
bool next();
void close();

CURSOR checkpoint();
bool jump(CURSOR location);

// Memory
bool validAddress(INTEGER address); 
void write(INTEGER address, INTEGER value);
INTEGER read(INTEGER address);

// Registy
bool validRegistry(INTEGER address);
void writeRegistry(INTEGER address, CURSOR cursor);
CURSOR readRegistry(INTEGER address);

#endif
