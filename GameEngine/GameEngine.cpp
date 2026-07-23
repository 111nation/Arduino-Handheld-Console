#include "Program.hpp"
#include "Parse.hpp"
#include "Debug.hpp"

#ifdef __APPLE__
	#include <TargetConditionals.h>
#endif

#if defined(__APPLE__) && TARGET_OS_MAC 
	#include <mach-o/dyld.h>
	#include <limits.h>
	#include <libgen.h>
	#include <unistd.h>
#endif

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

		bool changeWorkingDirectory() {
			#ifdef TARGET_OS_MAC 
				char buf[PATH_MAX];
				uint32_t bufsize = PATH_MAX;
				if (_NSGetExecutablePath(buf, &bufsize)==-1) return false;

				char* dir = dirname(buf);

				// Failed to change directory
				if (chdir(dir) != 0) {
					return false;
				}
			#endif

			return true;
		}

	int main() {
		if (!changeWorkingDirectory()) {
			std::cout << "Failed to initialize game emulator\n";
			std::cout << "Could not change current working directory\n";
			return 0;
		}

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
