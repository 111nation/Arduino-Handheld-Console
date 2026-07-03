#include "Program.hpp"
#include "Display.hpp"
#include "Serial.hpp"
#include "Types.hpp"

INTEGER* Heap = new INTEGER[HEAP_SIZE];
STRING PC = NULL;			
CURSOR* Registry = new CURSOR[REGISTRY_SIZE];
Control control;
INTEGER* ArgumentList = new INTEGER[MAX_ARGUMENTS];
bool isRunning = false;

// ========= HEAP ==========
bool validAddress(INTEGER address) {
	return address >= 0 && address < HEAP_SIZE;
}

void write(INTEGER address, INTEGER value) {
	if (!validAddress(address)) return;
	Heap[address] = value;
}

INTEGER read(INTEGER address) {
	return validAddress(address) ? Heap[address] : 0;
}

// ========= REGISTRY ==========
bool validRegistry(INTEGER address) {
	return address >= 0 && address < REGISTRY_SIZE;
}

void writeRegistry(INTEGER address, CURSOR cursor) {
	if (!validRegistry(address)) return;
	Registry[address] = cursor;
}

CURSOR readRegistry(INTEGER address) {
	return validAddress(address) ? Registry[address] : checkpoint();
}

// ========= ARGUMENTS ==========
INTEGER arg(INTEGER address) {
	if (address >= 0 && address < MAX_ARGUMENTS) return ArgumentList[address];
	return 0;
}

#ifdef EMULATE 
	using namespace std;

	string sPC; // Backing storage to keep the raw PC char pointer alive
	ifstream File;
	streampos Cursor;

	bool init(STRING fileName, STRING port) {
		if (File.is_open()) File.close();

		File.open(fileName, ifstream::in);

		if (!File.is_open()) {
			std::cout << "Failed to open " << fileName << "\n";
		}

		Cursor = File.tellg();

		return initPort(port) && initDisplay() && next();
	}

	bool next() {
		if (!File.is_open()) return false;
		Cursor = File.tellg();

		if (getline(File, sPC)) {
			PC = sPC.c_str();
			return isRunning;
		}

		return false;
	}

	CURSOR checkpoint() {
		return Cursor;
	}

	bool jump(CURSOR location) {
		File.seekg(location);
		return next();
	}

	void display() {
		updateSDLDisplay();
	}

	void input() {
		handleSDLEvents();
		retrieveControlsFromSerial();
	}

	void close() {
		File.close();
		closePort();
		closeDisplay();
		isRunning = false;
	}
#else

#endif
