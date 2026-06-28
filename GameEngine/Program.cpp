#include "Program.hpp"

INTEGER* Heap = new INTEGER[HEAP_SIZE];
STRING PC;			// Program Counter

bool validAddress(INTEGER address) {
	// We accept a INTEGER instead of ADDR on purpose
	// Prevents silent downcasting/truncation overflow bugs
	// Ensures that numbers that overflow ADDR are not accepted as  
	// valid addresses due to truncation
	return address >= 0 && address < HEAP_SIZE;
}

void write(ADDR address, INTEGER value) {
	// Write value at specified heap address
	if (!validAddress(address)) return;
	Heap[address] = value;
}

INTEGER read(ADDR address) {
	// Return value at specified heap address
	return validAddress(address) ? Heap[address] : 0;
}

#define EMULATE

#ifdef EMULATE 
	using namespace std;

	string sPC; // Program Counter as a C++ Style String
	ifstream File;
	streampos Cursor;

	bool init(STRING fileName) {
		if (File.is_open()) File.close();
		File.open(fileName);
		Cursor = checkpoint();
		return next(); // Load first line
	}

	bool next() {
		// Load first line to Program Counter
		Cursor = File.tellg();
		if (File.is_open() && getline(File, sPC)) {
			PC = sPC.c_str();
			return true;
		}

		return false;
	}

	CURSOR checkpoint() {
		// Save current cursor position
		return Cursor;
	}

	bool jump(CURSOR location) {
		File.seekg(location);
		return next();
	}

	void close() {
		File.close();
	}
#else

#endif
