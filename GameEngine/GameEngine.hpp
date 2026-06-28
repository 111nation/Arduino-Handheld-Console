#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "Program.hpp"
#include "Parse.hpp"
#include "Serial.hpp"

/* 
 * SWITCH BETWEEN EMULATING LANGUAGE ON 
 * PERSONAL COMPUTER AND ARDUINO HARDWARE
 */
#ifdef EMULATE 
	#include <iostream>
	
	constexpr INTEGER NULL_INT = 1 << (sizeof(INTEGER) * 8 - 1);

	using namespace std;

	void interpret();

	// Debug Functions
	void initDebugHeap();
	void printHeap(bool symbols=false);
	void debugConsume(STRING value, STRING& line, STRING& start);
	void debugFind(STRING value, STRING& line, STRING start);
	void debugCursor();
	void debugPrintPC();
	CURSOR debugCheckpoint();
	void debugJump(CURSOR location);
#else

#endif 



#endif
