#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Types.hpp"
#include <cstdint>

#ifdef EMULATE

#include <SDL3/SDL.h>
#include <iostream>

#define POSITION(x,y) INTEGER x, INTEGER y
#define COLOR uint8_t r, uint8_t g, uint8_t b
#define KEYPRESS_VELOCITY 20

constexpr int SCREEN_WIDTH = 320;
constexpr int SCREEN_HEIGHT = 240;

bool initDisplay();
void retrieveControlsFromSDL();
void handleSDLEvents();
void updateSDLDisplay();
void closeDisplay();

// Draw Functions
void point(POSITION(x,y), COLOR);
void fill(COLOR);
void line(POSITION(x1, y1), POSITION(x2, y2), COLOR);
void clear();

#endif

#endif

