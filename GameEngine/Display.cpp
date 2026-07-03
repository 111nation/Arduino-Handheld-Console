#include "Display.hpp"
#include "SDL3/SDL_events.h"
#include "Types.hpp"

#ifdef EMULATE 

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool initDisplay() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "Error:\t" << SDL_GetError() << "\n";
		return false;
	}

	window = SDL_CreateWindow(
				"Emulator", 
				SCREEN_WIDTH, 
				SCREEN_HEIGHT,
				0
			);

	if (!window) {
		std::cout << "Error:\t" << SDL_GetError() << "\n";
		SDL_Quit();
		return false;
	}

	renderer = SDL_CreateRenderer(window, NULL);

	if (!renderer) {
		std::cout << "Error:\t" << SDL_GetError() << "\n";
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}

	isRunning = true;

	return true;
}

void updateSDLDisplay() {
	if (!isRunning || !window || !renderer) return;

	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 1);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void handleSDLEvents() {
	if (!isRunning || !window || !renderer) return;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_EVENT_QUIT:
				isRunning = false;
				break;
		}
	}
}

void closeDisplay() {
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

#endif
