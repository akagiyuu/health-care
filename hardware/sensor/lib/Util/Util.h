#pragma once

#include "HardwareSerial.h"
namespace Util
{
	template <typename T> void wait_for_comfirm(T message)
	{
		Serial.println(message);
		while (Serial.available() == 0)
			; // wait until user presses a key
		Serial.read();
	}
	template <typename T, unsigned int size>
	void shift_left(T (&array)[size], const unsigned int offset)
	{
		for (unsigned int i = offset; i < size; ++i) {
			array[i - offset] = array[i];
		}
	}

}
