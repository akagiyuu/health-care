#include "DeviceInfo.h"
#include "WiFiManager.h"

String DeviceInfo::get_mac_address()
{
	String mac_address = WiFi.macAddress();
	mac_address.replace(":", "");

	return mac_address;
}

void DeviceInfo::get_auth_data(char *email, char *password)
{
	strcpy(password, get_mac_address().c_str());
    sprintf(email, "%s@gmail.com", password);
}
