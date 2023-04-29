#include <Arduino.h>
#include <EepromBasedWiredDevice/EepromBasedWiredDevice.cpp>
#include <EepromBasedWiredDevice/EepromBasedWiredDevice.h>
#include <WiredDevice/WiredDevice.cpp>
#ifdef ARDUINO_ARCH_ESP32
#include <freertos/FreeRTOS.h>
// Not more than a page worth of data.
#define LEN 64
#else
#define LEN 64
#endif

EepromBasedWiredDevice device(27, 26, 0x50);

void setup() {
	Serial.begin(115200);
	Serial.println("Initializing...");
	device.setAddressSize(2);
	device.setWriteCycleTime(5000);
	auto *data = new uint8_t[LEN];
	auto *read = new uint8_t[LEN];
	for (int i = 0; i < LEN; i++) {
		data[i] = random() % 0xff;
		read[i] = 0;
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
	free(data);
	free(read);
	if (match) {
		Serial.println("PASSED!");
	}
}

void loop() {
#ifdef ARDUINO_ARCH_ESP32
	Serial.print("Free heap: ");
	Serial.println(xPortGetFreeHeapSize());
#endif
	delay(1000);
}