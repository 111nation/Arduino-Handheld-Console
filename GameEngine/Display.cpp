#include "Display.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_oldnames.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_render.h"
#include "Types.hpp"

void boundPosition(INTEGER& x, INTEGER& y) {
	x = x > 0 ? x : 0;
	y = y > 0 ? y : 0;
}

#ifdef EMULATE 

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* canvas = NULL;

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

	canvas = SDL_CreateTexture(renderer, 
			SDL_PIXELFORMAT_RGBA8888, 
			SDL_TEXTUREACCESS_TARGET, 
			SCREEN_WIDTH,
			SCREEN_HEIGHT);

	if (!canvas) {
		std::cout << "Error:\t" << SDL_GetError() << "\n";
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}

	isRunning = true;
	clear();
	updateSDLDisplay();

	return true;
}

void updateSDLDisplay() {
	if (!isRunning) return;

	// NOTE: AI Assisted Code
	// Switch target to physical window screen buffer
	SDL_SetRenderTarget(renderer, NULL);

	// Clear screen hardware buffer to prevent artifacts/ flickering
	SDL_RenderTexture(renderer, canvas, NULL, NULL);
	SDL_RenderPresent(renderer);

	// Copy persistent canvas texture to fill window
	SDL_RenderTexture(renderer, canvas, NULL, NULL);

	// Instruct the GPU to physically display the compiled frame
	SDL_RenderPresent(renderer);
}

void handleSDLEvents() {
	if (!isRunning) return;

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
	SDL_DestroyTexture(canvas);
	canvas = NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

// ========= DRAW FUNCTIONS ==========
void point(POSITION(x,y), COLOR) {
	if (!isRunning) return;
	
	boundPosition(x, y);

	SDL_SetRenderTarget(renderer, canvas);
	SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderPoint(renderer, x, y);
}

void fill(COLOR) {
	if (!isRunning) return;
	SDL_SetRenderTarget(renderer, canvas);
	SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void line(POSITION(x1, y1), POSITION(x2, y2), COLOR) {
	if (!isRunning) return;

	boundPosition(x1, y1);
	boundPosition(x2, y2);
	
	SDL_SetRenderTarget(renderer, canvas);
	SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderLine(renderer, x1, y1, x2, y2);
}

void clear() {
	if (!isRunning) return;
	SDL_SetRenderTarget(renderer, canvas);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

#endif
