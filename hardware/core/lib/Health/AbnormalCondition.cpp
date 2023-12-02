#include "AbnormalCondition.h"

uint AbnormalCondition::detect(int32_t heart_rate, int32_t spo2)
{
	uint32 conditions = 0;
	if (heart_rate < 60 || heart_rate > 100)
		conditions |= AbnormalCondition::UnsualHeartRate;
	if (spo2 > 90)
		conditions |= AbnormalCondition::UnsualSPO2;

	return conditions;
}
// uint32 detect(Sensor::Health::Data *health_data, Sensor::Motion::Data *motion_data)
// {
// 	uint32 conditions = detect_health(health_data->heart_rate, health_data->spo2);
//
// 	return conditions;
// }
