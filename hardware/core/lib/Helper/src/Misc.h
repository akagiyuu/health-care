#pragma once
#include <Arduino.h>

namespace Misc
{
	template <typename T> void wait_for_comfirm(T message)
	{
		Serial.println(message);
		while (Serial.available() == 0)
			; // wait until user presses a key
		Serial.read();
	}

}
