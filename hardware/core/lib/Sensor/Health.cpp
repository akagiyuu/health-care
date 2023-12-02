#include "Sensor.h"
#include <Arduino.h>
#include "spo2_algorithm.h"
#include <Array.h>
#include <MAX30105.h>
#include <Misc.h>

using namespace Sensor;

#define SAMPLE_PER_CALCULATE 25
#define READ_LED 13

static uint32_t IrBuffer[BUFFER_SIZE]; // infrared LED sensor data
static uint32_t RedBuffer[BUFFER_SIZE]; // red LED sensor data

MAX30105 HealthSensor;

void read_raw(byte sample_index)
{
	while (HealthSensor.available() == false)
		HealthSensor.check();

	digitalWrite(READ_LED, !digitalRead(READ_LED));

	RedBuffer[sample_index] = HealthSensor.getRed();
	IrBuffer[sample_index] = HealthSensor.getIR();
	HealthSensor.nextSample();
	//
	// Serial.print("Ir: ");
	// Serial.print(IrBuffer[sample_index]);
	// Serial.print(", Red: ");
	// Serial.println(RedBuffer[sample_index]);
}

void Health::init()
{
	if (!HealthSensor.begin(Wire, I2C_SPEED_FAST)) {
		Serial.println(F("MAX30105 was not found. Please check wiring/power."));
		while (true)
			;
	}

	// Misc::wait_for_comfirm(F("Attach sensor to finger with rubber band. Press any key to start conversion"));

	// clang-format off
	byte led_brightness = 60; // Options: 0=Off to 255=50mA
    byte led_mode = 2; // Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
	byte sample_average = 4; // Options: 1, 2, 4, 8, 16, 32
	byte sample_rate = 100; // Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
	int pulse_width = 411; // Options: 69, 118, 215, 411
	int adc_range = 4096; // Options: 2048, 4096, 8192, 16384
	// clang-format on

	HealthSensor.setup(led_brightness, sample_average, led_mode, sample_rate, pulse_width, adc_range);

	for (byte i = 0; i < 100; i++) {
		read_raw(i);
	}
}
bool Health::read(struct Data *health_data)
{
	Array::shift_left(IrBuffer, SAMPLE_PER_CALCULATE);
	Array::shift_left(RedBuffer, SAMPLE_PER_CALCULATE);

	for (byte i = 100 - SAMPLE_PER_CALCULATE; i < 100; i++) {
		read_raw(i);
	}
	int8_t is_valid_spo2, is_valid_heart_rate;

	// After gathering 25 new samples recalculate HR and SP02
	maxim_heart_rate_and_oxygen_saturation(IrBuffer,
		BUFFER_SIZE,
		RedBuffer,
		&(health_data->spo2),
		&is_valid_spo2,
		&(health_data->heart_rate),
		&is_valid_heart_rate);

	return is_valid_heart_rate && is_valid_spo2;
}
