#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include <cstdint>

// DATA TYPES

#define STRING const char*
#define INTEGER short int // 16 bit integer
#define ADDR uint8_t
#define HEAP_SIZE 64      // 64 heap memory addresses

// SYNTAX CONSTANTS
constexpr char INLINE_COMMENT = '#';

// ========================
// UNIVERSAL IMPLEMENTATION
// ========================

extern INTEGER* Heap;     // Heap memory

// Helpers
bool validAddress(ADDR address);
STRING trimLeadingTrailingWhitespace(STRING value);

// Basic I/O
void write(ADDR address, INTEGER value);
INTEGER read(ADDR address);

// Parsing and Interpreting
void parse(STRING line); 


#define EMULATE
						
/* 
 * SWITCH BETWEEN EMULATING LANGUAGE ON 
 * PERSONAL COMPUTER AND ARDUINO HARDWARE
 */
#ifdef EMULATE 
	#include <iostream>
	#include <fstream>
	#include <string>
	
	constexpr INTEGER NULL_INT = 1 << (sizeof(INTEGER) * 8 - 1);

	using namespace std;

	string readFile(string fileName);

	// Debug Functions
	void initDebugHeap();
	void printHeap();
#else

#endif 



#endif
