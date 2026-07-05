#ifndef SERIAL_HPP
#define SERIAL_HPP

#include "Types.hpp"

#ifdef EMULATE

#include "Lib/serialib/lib/serialib.h"

struct Control;

extern serialib Serial;
constexpr short int DATA_LENGTH = 19;

bool initPort(STRING port);
bool retrieveControlsFromSerial();
void closePort();

#endif

#endif
