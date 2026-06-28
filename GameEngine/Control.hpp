#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <cstdint>

struct Joystick {
	int8_t x = 0;
	int8_t y = 0;
	bool clicked = false;
};

struct Control {
	Joystick joystick;
	bool buttonA = false;
};

extern Control control;

#endif
