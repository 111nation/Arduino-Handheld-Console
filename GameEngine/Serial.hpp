#ifndef SERIAL_HPP
#define SERIAL_HPP

#include "Lib/serialib.h"
#include <iostream>

extern serialib Serial;
constexpr short int DATA_LENGTH = 19;

bool initPort(const char* port);
void retrieveControlActions();
void closePort();

#endif
