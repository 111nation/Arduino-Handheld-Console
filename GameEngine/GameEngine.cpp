#include "GameEngine.hpp"
#include "Program.hpp"
#include "Serial.hpp"

#ifdef EMULATE 

using namespace std;

void interpret() {
	do {
		parse();
	} while (next());
}


void initDebugHeap() {
	// Set all heap values to "null" by setting a large negative number
	for (int i = 0; i < HEAP_SIZE; i++) {
		Heap[i] = NULL_INT;
	}
}

void printHeap(bool symbols) {
	// Print heap and skip empty contents
	cout << "Heap:\t\t[ ";
	
	bool allowEllips = true;
	for (int i = 0; i < HEAP_SIZE; i++) {
		if (Heap[i] == NULL_INT) {
			if (allowEllips) cout << "... , ";
			allowEllips = false;
			continue;
		} 

		if (symbols) {
			cout << "M" << i << "=";
		}


		cout << Heap[i] << " , ";
		allowEllips = true;
	}

	cout << "\b\b]\n";
}

void initDebugRegistry() {
	// Set all registry values to "null" 
	for (int i = 0; i < REGISTRY_SIZE; i++) {
		Registry[i] = NULL_CURSOR;
	}
}

void printRegistry() {
	// Print heap and skip empty contents
	cout << "Registry:\t[ ";
	
	bool allowEllips = true;
	for (int i = 0; i < REGISTRY_SIZE; i++) {
		if (Registry[i] <= NULL_CURSOR) {
			if (allowEllips) cout << "... , ";
			allowEllips = false;
			continue;
		} 

		cout << "FUNC" << i <<  " , ";
		allowEllips = true;
	}

	cout << "\b\b]\n";

}

void debugConsume(STRING value, STRING& line) {
	STRING start = line;
	std::cout << "Consuming keyword \"" << value << "\" immediately in \"" << line << "\"\n";

	if (consume(value, line)) {
		std::cout << "\"" << value << "\" was found\n";
		std::cout << "\"" << *line << "\" at position " << line-start << "\n";
	} else {
		std::cout << "\"" << value << "\" was not found\n";
	}
}

void debugFind(STRING value, STRING& line, STRING start) {
	std::cout << "Finding keyword \"" << value << "\" in \"" << start << "\"\n";
	
	if (find(value, line, start)) {
		std::cout << "\"" << value << "\" was found\n";
		std::cout << "\"" << *line << "\" at position " << line-start << "\n";
	} else {
		std::cout << "\"" << value << "\" was not found\n";
	}

}

void debugPrintPC() {
	if (!PC) {
		std::cout << "ERROR:\tPC is NULL\n";
		return;
	}

	std::cout << "PRINT:\t\t" << PC << "\n";
}

CURSOR debugCheckpoint() {
	if (!PC) {
		std::cout << "ERROR:\tPC is NULL\n";
		return checkpoint();
	}

	std::cout << "CHECKPOINT:\t" << PC << "\n";
	return checkpoint(); 
}

void debugJump(CURSOR location) {
	if (!PC) {
		std::cout << "ERROR:\tPC is NULL\n";
		return;
	}

	jump(location);
	std::cout << "JUMP:\t\t" << PC << "\n";
}

void debugCursor() {
	init("programs/main", "/dev/ttyACM1");
	debugPrintPC();
	next();
	debugPrintPC();
	CURSOR cur = debugCheckpoint();
	next();
	debugPrintPC();
	next();
	debugPrintPC();
	next();
	next();
	CURSOR cur2 = debugCheckpoint();
	debugJump(cur);
	debugPrintPC();
	debugJump(cur2);
	debugPrintPC();
	close();
}

void debugSerial(STRING port) {
	if (!initPort(port)) {
		std::cout << "Failed to Initialize Port\n";
		return;
	}

	std::cout << "debugSerial not in use\n";

	closePort();
}

void printControls() {
	Joystick& joystick = control.joystick;
	std::cout << "X: " << (int) joystick.x << "\n";
	std::cout << "Y: " << (int) joystick.y << "\n";

	if (joystick.clicked) {
		std::cout << "Joystick Clicked!\n";
	}

	if (control.buttonA) {
		std::cout << "Button A Clicked!\n";
	}
}

void debugControls(const char *port) {
	if (!initPort(port)) {
		std::cout << "Failed to Initialize Port\n";
		return;
	}
	
	while (true) {
		retrieveControls();
		printControls();
	}

	closePort();
}

int main() {
	init("programs/main", "/dev/ttyACM0");
	initDebugHeap();
	initDebugRegistry();

	interpret();

	printRegistry();
	printHeap(true);

	close();

	//debugControls("/dev/ttyACM1");

	//debugSerial("/dev/ttyACM1");

	return 0;
}

#else

#endif 
