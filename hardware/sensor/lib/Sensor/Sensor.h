#pragma once
#include "MAX30105.h"

namespace Sensor
{
	namespace Health
	{
		struct Data {
			int32_t heart_rate;
			int32_t spo2;
		};
		void init(MAX30105 *sensor);
		bool read(MAX30105 *sensor, struct Data *health_data);

		void read_raw(MAX30105 *sensor, byte sample_index);
	}
	namespace Motion
	{

	}
}
