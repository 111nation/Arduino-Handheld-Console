#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#define INTEGER short int // 16 bit integer
#define HEAP_SIZE 64      // 64 heap memory addresses

extern INTEGER* Heap;     // Heap memory

#define EMULATE
						
/* 
 * SWITCH BETWEEN EMULATING LANGUAGE ON 
 * PERSONAL COMPUTER AND ARDUINO HARDWARE
 */
#ifndef EMULATE 
	#include <iostream>
	#include <fstream>
	#include <string>

	void loadFile(std::string fileName);
#else

#endif 



#endif
