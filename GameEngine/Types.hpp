#ifndef TYPES_HPP
#define TYPES_HPP

/* 
 * SWITCH BETWEEN EMULATING LANGUAGE ON 
 * PERSONAL COMPUTER AND ARDUINO HARDWARE
 */
#define EMULATE

#ifdef EMULATE 
	#include <fstream>
	#define CURSOR std::streampos
#else
	#define CURSOR uint_8
#endif

#include <cstdint>

extern bool isRunning;

// ===== BASIC DATA STRUCTURES ======
#define STRING const char*
#define INTEGER short int	// 16 bit integer

#define HEAP_SIZE 64      	// 64 heap memory addresses
#define REGISTRY_SIZE 16  	// 16 Functions Possible
#define MAX_ARGUMENTS 10

struct Joystick {
	int8_t x = 0;
	int8_t y = 0;
	int8_t clicked = 0;
};

struct Control {
	Joystick joystick;
	int8_t buttonA = 0;
};

// ===== CORE GLOBALS ======
extern Control control;			// Control Structure
extern INTEGER* Heap;     		// Heap Memory
extern STRING PC;				// Program Counter
extern CURSOR* Registry;		// Fuction Registry
extern INTEGER* ArgumentList; 	// Argument List "Stack"

#endif

