#include <Arduino.h>
#include <Wire.h>

void setup() {
	Serial.begin(115200);

#ifdef ARDUINO_ARCH_ESP32
	//	Wire.begin(27, 26);
	Wire.begin();
#else
	Wire.begin();
#endif

	Serial.println("Initializing scanner...");
}

void printAddress(uint8_t address) {
	Serial.print("0x");
	if (address < 0x10) {
		Serial.print("0");
	}
	Serial.println(address, HEX);
}

void loop() {
	uint8_t result, address;
	int devices;
	devices = 0;
	Serial.println("Scanning from 0x01 to 0x7f...");
	for (address = 0x01; address < 0x7f; address++) {
		Wire.beginTransmission(address);
		result = Wire.endTransmission();
		switch (result) {
			case 0:
				Serial.print("Device found @ ");
				printAddress(address);
				devices++;
				break;
			case 4:
				Serial.print("Unknown error @ ");
				printAddress(address);
				break;
			case 5:
				Serial.print("Timeout @ ");
				printAddress(address);
				break;
		}
	}

	if (devices == 0) {
		Serial.println("No devices found.");
	} else {
		Serial.println("Scanning complete.");
	}

	delay(5000);
}
