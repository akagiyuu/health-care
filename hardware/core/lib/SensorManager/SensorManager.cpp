#include "SensorManager.h"
#include "json/FirebaseJson.h"
#include <cstdlib>

void Sensor::Manager::init()
{
	Sensor::Health::init();
	Sensor::Motion::init();
	this->health_data = { .heart_rate = 0, .spo2 = 0 };
}
bool Sensor::Manager::sync()
{
	bool is_health_read_successful = Health::read(&this->health_data);
	bool is_motion_read_successful = Motion::read(&this->motion_data);

    return is_health_read_successful;
}

void Sensor::Manager::to_json(FirebaseJson &output)
{
	int32_t heart_rate = this->health_data.heart_rate;
	int32_t spo2 = this->health_data.spo2;
	output.set("Heart rate", heart_rate);
	output.set("SP O2", spo2);
	output.set("Abnormal conditions", AbnormalCondition::detect(heart_rate, spo2));

	FirebaseJson gyro, acceleration;
	gyro.set("x", this->motion_data.gyro.x);
	gyro.set("y", this->motion_data.gyro.y);
	gyro.set("z", this->motion_data.gyro.z);
	acceleration.set("x", this->motion_data.acceleration.x);
	acceleration.set("y", this->motion_data.acceleration.y);
	acceleration.set("z", this->motion_data.acceleration.z);

	output.set("Gyro", gyro);
	output.set("Acceleration", acceleration);
}

void Sensor::Manager::print()
{
	Serial.printf("Heart rate: %d\n", this->health_data.heart_rate);
	Serial.printf("SP O2: %d\n", this->health_data.spo2);
}
