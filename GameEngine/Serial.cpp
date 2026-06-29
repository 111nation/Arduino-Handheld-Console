#include "Serial.hpp"

#ifdef EMULATE

using namespace std;

serialib Serial;
bool portReady = false;

bool initPort(STRING port) {
	if (Serial.openDevice(port, 9600) != 1) return false;
	Serial.flushReceiver();
	portReady = true;
	return true;
}

void retrieveControls() {
	if (!portReady) {
		return;
	}

	// Signal ready to make Arduino respond back
	Serial.writeString("1\n");
	if (Serial.available() < DATA_LENGTH+1) return;
	
	char buffer[DATA_LENGTH+1];
	Serial.readBytes(buffer,  DATA_LENGTH+1, 200);
	
	Joystick& joystick = control.joystick;

	string sInput = buffer;
	string x = sInput.substr(0, 8);
	string y = sInput.substr(8, 8);
	bool joyClicked = sInput[16] == '1';
	bool buttonA = sInput[17] == '1';

	joystick.x = stoi(x, nullptr, 2);
	joystick.y = stoi(y, nullptr, 2);
	joystick.clicked = joyClicked;
	control.buttonA = buttonA;
}

void closePort() {
	if (!portReady) return;
	Serial.writeString("0\n");
	Serial.closeDevice();
	portReady = false;
}

#endif
