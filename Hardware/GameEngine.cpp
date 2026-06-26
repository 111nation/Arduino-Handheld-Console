#include "GameEngine.hpp"

#ifdef EMULATE 

using namespace std;

void interpret() {
	while (next()) {
		parse(PC);
	}
}


void initDebugHeap() {
	// Set all heap values to "null" by setting a large negative number
	for (int i = 0; i < HEAP_SIZE; i++) {
		Heap[i] = NULL_INT;
	}
}

void printHeap(bool symbols) {
	// Print heap and skip empty contents
	cout << "Heap:\t[";
	
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

	cout << "\b\b ]\n";
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

int main() {
	init("programs/main");
	initDebugHeap();
	interpret();
	printHeap(true);
	close();

	/*
	STRING line = "IF M1 != M5 UTHEN";
	STRING match = THEN;
	//debugConsume(match, line);
	debugFind(match, line, line);
	*/

	return 0;
}

#else

#endif 
