#pragma once
#include <Arduino.h>
#include <MAX30105.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "json/FirebaseJson.h"

namespace Sensor
{
	namespace Health
	{
		struct Data {
			int32_t heart_rate;
			int32_t spo2;
		};
		void init();
		bool read(struct Data *health_data);
	}
	namespace Motion
	{
		struct Data {
			sensors_vec_t acceleration;
			sensors_vec_t gyro;
		};
		void init();
		bool read(struct Data *motion_data);
	}
}
