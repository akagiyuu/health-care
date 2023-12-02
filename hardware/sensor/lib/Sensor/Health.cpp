#include "Sensor.h"
#include "Arduino.h"
#include "HardwareSerial.h"
#include "MAX30105.h"
#include "spo2_algorithm.h"
#include <Util.h>

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
static uint16_t IrBuffer[BUFFER_SIZE]; // infrared LED sensor data
static uint16_t RedBuffer[BUFFER_SIZE]; // red LED sensor data
#else
static uint32_t IrBuffer[BUFFER_SIZE]; // infrared LED sensor data
static uint32_t RedBuffer[BUFFER_SIZE]; // red LED sensor data
#endif
#define SAMPLE_PER_CALCULATE 25
#define READ_LED 13


void Sensor::Health::init(MAX30105 *sensor)
{
	for (byte i = 0; i < 100; i++) {
		read_raw(sensor, i);
	}
}
bool Sensor::Health::read(MAX30105 *sensor, struct Data *health_data)
{
    Util::shift_left(IrBuffer, SAMPLE_PER_CALCULATE);
    Util::shift_left(RedBuffer, SAMPLE_PER_CALCULATE);

	for (byte i = 100 - SAMPLE_PER_CALCULATE; i < 100; i++) {
		read_raw(sensor, i);
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

void Sensor::Health::read_raw(MAX30105 *sensor, byte sample_index)
{
	while (sensor->available() == false)
		sensor->check();

	digitalWrite(READ_LED, !digitalRead(READ_LED));

	RedBuffer[sample_index] = sensor->getRed();
	IrBuffer[sample_index] = sensor->getIR();
	sensor->nextSample();
	//
	// Serial.print("Ir: ");
	// Serial.print(IrBuffer[sample_index]);
	// Serial.print(", Red: ");
	// Serial.println(RedBuffer[sample_index]);
}
