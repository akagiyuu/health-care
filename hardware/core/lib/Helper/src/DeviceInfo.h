#pragma once
#include "Arduino.h"

namespace DeviceInfo
{
	String get_mac_address();
	void get_auth_data(char *email, char *password);
}
