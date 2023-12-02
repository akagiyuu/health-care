#pragma once
#include <Arduino.h>

namespace AbnormalCondition
{
	enum Conditions {
        UnsualHeartRate = 1,
        UnsualSPO2 = 2
	};
	uint32 detect(int32_t heart_rate, int32_t spo2);
}
