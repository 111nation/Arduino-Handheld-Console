#include "GameEngine.hpp"
#include "Debug.hpp"
#include "Serial.hpp"

void interpret() {
	do {
		parse();
	} while (next());
}

#ifdef EMULATE
	int main() {
		init("programs/main", "/dev/ttyACM0");
		initDebugHeap();
		initDebugRegistry();

		interpret();

		printRegistry();
		printHeap(true);

		close();

		return 0;
	}
#endif
