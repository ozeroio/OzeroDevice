#include <Arduino.h>
#include <EepromBasedWiredDevice/EepromBasedWiredDevice.cpp>
#include <EepromBasedWiredDevice/EepromBasedWiredDevice.h>
#include <WiredDevice/WiredDevice.cpp>

#define LEN 32

EepromBasedWiredDevice device(27, 26, 0x50);

void setup() {
	Serial.begin(115200);
	Serial.println("Initializing...");
	device.setAddressSize(2);
	device.setWriteCycleTime(5000);
	uint8_t data[LEN] = {0};
	uint8_t read[LEN] = {0};
	for (unsigned char &i: data) {
		i = random() % 0xff;
	}
	int address = 0;
	Serial.print("Address: ");
	Serial.println(address);
	Serial.print("Written: ");
	Serial.println(device.writeBlock(address, data, LEN));
	Serial.print("Read: ");
	Serial.println(device.readBlock(address, read, LEN));
	bool match = true;
	for (int i = 0; i < LEN; i++) {
		if (data[i] != read[i]) {
			match = false;
			Serial.print("FILED! AT ");
			Serial.print(i);
			Serial.print(": data[] = ");
			Serial.print(": data[] = ");
			Serial.print(data[i], HEX);
			Serial.print(", read[] = ");
			Serial.println(read[i], HEX);
		}
	}
	if (match) {
		Serial.println("PASSED!");
	}
}

void loop() {
	delay(1);
}