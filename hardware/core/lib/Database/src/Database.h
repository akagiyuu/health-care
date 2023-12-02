#pragma once
#include "WString.h"
#include <Firebase_ESP_Client.h>
#include <Sensor.h>
#include <SensorManager.h>

namespace Database
{
	extern FirebaseData DataObject;
	void auth(bool is_sign_up_needed);
	bool send(Sensor::Manager &sensor_manager);
}
