#include "Internet.h"
#include <WiFiManager.h>
#include <DeviceInfo.h>
#include <cstdio>

String default_parameter()
{
	String mac_address = DeviceInfo::get_mac_address();

	String display = "<p>Your ID: " + mac_address + "</p>";

	return display;
}

void Internet::init()
{
	WiFiManager wifi_manager;

	String parameter = default_parameter();

	WiFiManagerParameter custom_text((const char *)parameter.c_str());

	wifi_manager.resetSettings();

	wifi_manager.addParameter(&custom_text);
	wifi_manager.autoConnect("Health care device");
	Serial.println("connected");
}
