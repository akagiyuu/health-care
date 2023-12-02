#include "HardwareSerial.h"
#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"
#include <Sensor.h>
#include <Util.h>
#include "config.h"

MAX30105 ParticleSensor;
struct Sensor::Health::Data health_data = { .heart_rate = 0, .spo2 = 0 };

void setup()
{
	Serial.begin(115200);
	Config::Led();

	// Initialize sensor
	if (!ParticleSensor.begin(Wire, I2C_SPEED_FAST)) {
		Serial.println(F(
			"MAX30105 was not found. Please check wiring/power."));
		while (true)
			;
	}

	Util::wait_for_comfirm(F(
		"Attach sensor to finger with rubber band. Press any key to start conversion"));

	Config::Sensor(&ParticleSensor);

    Sensor::Health::init(&ParticleSensor);
}

void loop()
{
    Sensor::Health::read(&ParticleSensor, &health_data);
	Serial.print(health_data.heart_rate);
	Serial.print(",");
	Serial.println(health_data.spo2);
}
