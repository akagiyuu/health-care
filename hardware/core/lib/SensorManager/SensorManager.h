#pragma once
#include <AbnormalCondition.h>
#include <Sensor.h>

namespace Sensor
{
	class Manager {
	    public:
		struct Health::Data health_data;
		struct Motion::Data motion_data;
		void init();
		bool sync();
		void to_json(FirebaseJson &output);
		void print();
	};
}
