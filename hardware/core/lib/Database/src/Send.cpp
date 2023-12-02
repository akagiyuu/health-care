#include "Database.h"
#include <Arduino.h>
#include "HardwareSerial.h"
#include "Sensor.h"
#include "json/FirebaseJson.h"
#include <Arduino.h>
#include <DeviceInfo.h>
#include <cstdlib>

void firebase_set_error_handler(FirebaseData *data_object)
{
	Serial.println(data_object->errorReason());
}

bool Database::send(Sensor::Manager &sensor_manager)
{
    static String base = DeviceInfo::get_mac_address();
    static FirebaseJson firebase_data;
	while (!Firebase.ready())
		;

    sensor_manager.to_json(firebase_data);

    Serial.printf("Sending to database at key: %s\n", base.c_str());
    if(!Firebase.RTDB.updateNode(&DataObject, base, &firebase_data)) {
        firebase_set_error_handler(&DataObject);
        return false;
    }

	return true;
}
