#include "Program.hpp"

INTEGER* Heap = new INTEGER[HEAP_SIZE];
STRING PC;			
CURSOR* Registry = new CURSOR[REGISTRY_SIZE];

// ========= HEAP ==========
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

// ========= REGISTRY ==========
bool validRegistry(INTEGER address) {
	// We accept a INTEGER instead of ADDR on purpose
	// Prevents silent downcasting/truncation overflow bugs
	// Ensures that numbers that overflow ADDR are not accepted as  
	// valid addresses due to truncation
	return address >= 0 && address < REGISTRY_SIZE;
}

void writeRegistry(ADDR address, CURSOR cursor) {
	// Write location of a function at specified registry address
	if (!validRegistry(address)) return;
	Registry[address] = cursor;
}

CURSOR readRegistry(ADDR address) {
	// Return cursor location of function at specified registry address
	// If invalid address return current cursor location
	return validAddress(address) ? Registry[address] : checkpoint();
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
