#ifndef SERIAL_HPP
#define SERIAL_HPP

#include "Lib/serialib.h"
#include <string>
#include "Control.hpp"

struct Control;

extern serialib Serial;
constexpr short int DATA_LENGTH = 19;

bool initPort(const char* port);
void retrieveControls();
void closePort();

#endif
