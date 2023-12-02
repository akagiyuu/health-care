#include "Database.h"
#include <Arduino.h>
#include <EEPROM.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <DeviceInfo.h>
#include "env.h"

#define BUFFER_SIZE 100

FirebaseData Database::DataObject;

FirebaseAuth Auth;
FirebaseConfig Config;

bool sign_up(const char *email, const char *password)
{
    Serial.println("signed up");
	bool is_success = Firebase.signUp(&Config, &Auth, email, password);

	if (is_success) {
		EEPROM.write(0, 0);
		EEPROM.commit();
	}

	return is_success;
}
void sign_in(const char *email, const char *password)
{
	Serial.println("Sign in");
	Auth.user.email = email;
	Auth.user.password = password;
	Serial.println("Successfully sign in");
}
void Database::auth(bool is_sign_up_needed)
{
	char email[BUFFER_SIZE];
	char password[BUFFER_SIZE];

	DeviceInfo::get_auth_data(email, password);
	Serial.println(email);
	Serial.println(password);

	Config.api_key = API_KEY;
	Config.database_url = DATABASE_URL;
	if (is_sign_up_needed) {
		if (!sign_up(email, password)) {
			Serial.println(Config.signer.signupError.message.c_str());
		}
	} else {
		sign_in(email, password);
	}

	Config.token_status_callback = tokenStatusCallback;

	Firebase.begin(&Config, &Auth);

	Firebase.reconnectWiFi(true);
}
