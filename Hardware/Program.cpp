#include "Program.hpp"

INTEGER* Heap = new INTEGER[HEAP_SIZE];
STRING PC;			// Program Counter

#ifdef EMULATE 
	using namespace std;

	string sPC; // Program Counter as a C++ Style String
	ifstream File;

	bool init(STRING fileName) {
		if (File.is_open()) File.close();
		File.open(fileName);
		return next(); // Load first line
	}

	bool next() {
		// Load first line to Program Counter
		if (File.is_open() && getline(File, sPC)) {
			PC = sPC.c_str();
			return true;
		}

		return false;
	}

	void close() {
		File.close();
	}
#else

#endif
