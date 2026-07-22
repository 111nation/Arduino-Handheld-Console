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
    void printDebugInfo() {
        std::cout << "Finished Executing: Outputting Debug Information\n\n";

        printRegistry();
        printHeap(true);
        printArgumentList();

        std::cout << "\n\nType q and hit 'Enter' to quit\n";

        char input;
        while (std::cin >> input) {
            if (input == 'q' || input == 'Q') break;
        }
    }

	int main() {
		init("programs/main", "/dev/ttyACM0");
		
		initDebugHeap();
		initDebugRegistry();
		initDebugArgumentList();

		interpret();

		close();

        printDebugInfo();

		return 0;
	}
#endif
