#include <Arduino.h>

void setup() {
	Serial.begin(9600);
	Serial.println("Initializing...");
}

void loop() {
	Serial.print(".");
	delay(1000);
}