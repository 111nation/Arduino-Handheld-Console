#include "Serial.hpp"

serialib Serial;

bool initPort(const char* Port) {
	if (Serial.openDevice(Port, 9600) != 1) return false;
	Serial.flushReceiver();
	return true;
}

void retrieveControlActions() {
	// Signal ready
	Serial.writeString("1\n");
	
	unsigned char received[DATA_LENGTH];
	if (Serial.available() < 0) return;
	Serial.readBytes(received,  DATA_LENGTH+1, 200);

	for (int i = 0; i < 19; i++) {
		std::cout << received[i];
	}

	std::cout << "\n";
}

void closePort() {
	Serial.writeString("0\n");
	Serial.closeDevice();
}
