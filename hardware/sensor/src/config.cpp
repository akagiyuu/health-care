#include "config.h"
#include "Arduino.h"
#include "MAX30105.h"

void Config::Led()
{
	byte pulseLED = 11; // Must be on PWM pin
	byte readLED = 13;

	pinMode(pulseLED, OUTPUT);
	pinMode(readLED, OUTPUT);
}

void Config::Sensor(MAX30105 *sensor)
{
	// clang-format off
	byte led_brightness = 60; // Options: 0=Off to 255=50mA
    byte led_mode = 2; // Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
	byte sample_average = 4; // Options: 1, 2, 4, 8, 16, 32
	byte sample_rate = 100; // Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
	int pulse_width = 411; // Options: 69, 118, 215, 411
	int adc_range = 4096; // Options: 2048, 4096, 8192, 16384
	// clang-format on

	sensor->setup(
        led_brightness,
        sample_average,
        led_mode,
        sample_rate,
        pulse_width,
        adc_range
    );
}
