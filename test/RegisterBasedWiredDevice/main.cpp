#include <Arduino.h>
#include <RegisterBasedDevice/RegisterBasedDevice.cpp>
#include <RegisterBasedWiredDevice/RegisterBasedWiredDevice.cpp>
#include <RegisterBasedWiredDevice/RegisterBasedWiredDevice.h>
#include <WiredDevice/WiredDevice.cpp>

#ifdef ARDUINO_ARCH_ESP32
#include <freertos/FreeRTOS.h>
#endif

RegisterBasedWiredDevice device(0x68);

void setup() {
	Serial.begin(115200);

#ifdef ARDUINO_ARCH_ESP32
	//	Wire.begin(27, 26);
	Wire.begin(11, 12);
#else
	Wire.begin();
#endif

	Serial.println("Initializing...");

	for (int i = 0; i < 0x16; i++) {
		Serial.print("Register(");
		Serial.print(i, HEX);
		Serial.print("): 0x");
		Serial.println(device.getRegisterBits(i, 0x0f), HEX);
	}
}

void loop() {
#ifdef ARDUINO_ARCH_ESP32
	Serial.print("Free heap: ");
	Serial.println(xPortGetFreeHeapSize());
#endif
	delay(1000);
}