#include "GameEngine.hpp"
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <filesystem>

// UNIVERSAL IMPLEMENTATION

INTEGER* Heap = new INTEGER[HEAP_SIZE];

bool validAddress(ADDR address) {
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

void parse(STRING line) {
}

#ifdef EMULATE 

using namespace std;

string readFile(std::string fileName) {
	// Read file and return its string data
	ifstream file(fileName);
	string line, contents;	

	// Read File Contents
	while (getline(file, line)) {
		// Skip leading whitespace
		size_t start = line.find_first_not_of(" \t\n\r\f\v");

		// Skip comments and empty lines
		if (start == std::string::npos || line[start] == INLINE_COMMENT) continue;

		contents += line + '\n';
	}

	file.close();

	return contents;
}

void initDebugHeap() {
	// Set all heap values to "null" by setting a large negative number
	for (int i = 0; i < HEAP_SIZE; i++) {
		Heap[i] = NULL_INT;
	}
}

void printHeap() {
	// Print heap and skip empty contents
	cout << "Heap:\t[ ";
	
	int occupied = 0;
	bool allowEllips = true;
	for (int i = 0; i < HEAP_SIZE; i++) {
		if (Heap[i] == NULL_INT) {
			if (allowEllips) cout << "... , ";
			allowEllips = false;
			continue;
		} 

		cout << Heap[i] << " , ";
		allowEllips = true;
	}

	cout << "\b\b ]\n";
}

int main() {
	string program = readFile("programs/main");
	initDebugHeap();

	write(6, 30);
	write(7, -1);
	write(3, read(6));

	printHeap();
	return 0;
}

#else

#endif 
