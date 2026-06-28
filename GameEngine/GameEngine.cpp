#include "GameEngine.hpp"
#include "Program.hpp"

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
	cout << "Heap:\t[ ";
	
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
	init("programs/main");
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

int main() {
	/*
	init("programs/main");
	initDebugHeap();
	interpret();
	printHeap(true);
	close();
	*/

	if (!initPort("/dev/ttyACM1")) {
		std::cout << "Failed to Initialize Port\n";
		return 0;
	}

	while (true) {
		retrieveControlActions();
	}
	closePort();

	//debugCursor();

	return 0;
}

#else

#endif 
