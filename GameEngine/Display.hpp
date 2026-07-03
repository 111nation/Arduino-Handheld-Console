#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Types.hpp"

#ifdef EMULATE

#include <SDL3/SDL.h>
#include <iostream>

constexpr int SCREEN_WIDTH = 320;
constexpr int SCREEN_HEIGHT = 240;

bool initDisplay();
void handleSDLEvents();
void updateSDLDisplay();
void closeDisplay();

#endif

#endif

