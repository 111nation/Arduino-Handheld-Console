#include "GameEngine.hpp"

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

		//debugControls("/dev/ttyACM1");
		//debugSerial("/dev/ttyACM1");

		return 0;
	}
#endif
