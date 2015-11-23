#include <Utils.h>

#define BATTERY_VOLTAGE_PIN A0
#define PHOTOCELL_PIN A1
#define PIR_PIN A2

void setup(void)
{
	pinMode(BATTERY_VOLTAGE_PIN, INPUT);
	pinMode(PHOTOCELL_PIN, INPUT);
	pinMode(PIR_PIN, INPUT);
	// start serial port
	Serial.begin(19200);
	Serial.println("Basic sensors Test");
}

void loop(void)
{
	Serial.print("Battery voltage[x10]: ");
	Serial.println(batteryVoltage(BATTERY_VOLTAGE_PIN));
	Serial.print("Luminosity: ");
	Serial.println(photoCell(PHOTOCELL_PIN));
	Serial.print("Pir: ");
	Serial.println(pir(PIR_PIN));
	delay(500);
}


