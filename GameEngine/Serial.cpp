#include "Serial.hpp"
#include "Control.hpp"

using namespace std;

serialib Serial;

bool initPort(const char* Port) {
	if (Serial.openDevice(Port, 9600) != 1) return false;
	Serial.flushReceiver();
	return true;
}

void retrieveControls() {
	// Signal ready
	Serial.writeString("1\n");
	if (Serial.available() < 0) return;
	
	char buffer[DATA_LENGTH+1];
	Serial.readBytes(buffer,  DATA_LENGTH+1, 200);
	
	// Read control data
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
	Serial.writeString("0\n");
	Serial.closeDevice();
}
