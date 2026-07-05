#include "Program.hpp"
#include "Parse.hpp"
#include "Debug.hpp"

void interpret() {
	if (!isRunning) return;

	do {
		parse();
	} while (isRunning && next());
}

#ifdef EMULATE
	int main() {
		init("programs/main", "/dev/ttyACM0");
		
		initDebugHeap();
		initDebugRegistry();
		initDebugArgumentList();

		interpret();

		printRegistry();
		printHeap(true);
		printArgumentList();

		close();

		return 0;
	}
#endif
