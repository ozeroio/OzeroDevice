#include <Arduino.h>
#include <EepromBasedWiredDevice/EepromBasedWiredDevice.cpp>
#include <EepromBasedWiredDevice/EepromBasedWiredDevice.h>
#include <WiredDevice/WiredDevice.cpp>
#ifdef ARDUINO_ARCH_ESP32
#include <freertos/FreeRTOS.h>
// Not more than a page worth of data.
#define LEN 16
#else

// Has to be <= than the buffer size (32) minus the address size (2)
#define LEN 16
#endif

class EepromBasedWiredDevice24x08 : public EepromBasedWiredDevice {

public:
	explicit EepromBasedWiredDevice24x08(uint8_t deviceAddress) : EepromBasedWiredDevice(deviceAddress) {
	}

	// From datasheet: Following the A2 hardware slave address bit are bits A9 and A8 (bit 2 and bit 1 of the device address
	// byte), which are the two Most Significant bits of the memory array word address. Refer to Table 6-1 to
	// review these bit positions.
	uint8_t dynamicAddress(int32_t memoryAddress) const override {

		// Set A9 and A8 bits as part of LSB of the device address.
		return (deviceAddress & 0xfc) | ((memoryAddress >> 8) & 0x03);
	}
};

EepromBasedWiredDevice24x08 device(0x50);

void setup() {
	Serial.begin(115200);

#ifdef ARDUINO_ARCH_ESP32
	//	Wire.begin(27, 26);
	Wire.begin();
#else
	Wire.begin();
#endif

	Serial.println("Initializing...");
	device.setAddressSize(1);
	device.setWriteCycleTime(5000);
	auto *data = new uint8_t[LEN];
	auto *data2 = new uint8_t[LEN];
	auto *read = new uint8_t[LEN];
	for (int i = 0; i < LEN; i++) {
		data[i] = random() % 0xff;
		data2[i] = random() % 0xff;
		read[i] = 0;
	}
	int address = 0b1100000000;
	int address2 = 0b0100000000;
	Serial.print("Address: ");
	Serial.println(address);
	Serial.print("Written: ");
	Serial.println(device.writeBlock(address, data, LEN));
	Serial.print("Written2: ");
	Serial.println(device.writeBlock(address2, data2, LEN));
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
	Serial.print("Read2: ");
	Serial.println(device.readBlock(address2, read, LEN));
	bool match2 = true;
	for (int i = 0; i < LEN; i++) {
		if (data2[i] != read[i]) {
			match2 = false;
			Serial.print("FILED! AT ");
			Serial.print(i);
			Serial.print(": data[] = ");
			Serial.print(": data[] = ");
			Serial.print(data2[i], HEX);
			Serial.print(", read[] = ");
			Serial.println(read[i], HEX);
		}
	}
	free(data);
	free(data2);
	free(read);
	if (match) {
		Serial.println("PASSED!");
	}
	if (match2) {
		Serial.println("PASSED2!");
	}
}

void loop() {
#ifdef ARDUINO_ARCH_ESP32
	Serial.print("Free heap: ");
	Serial.println(xPortGetFreeHeapSize());
#endif
	delay(1000);
}