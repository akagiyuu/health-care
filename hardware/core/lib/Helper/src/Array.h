#pragma once

namespace Array
{
	template <typename T, unsigned int size> void shift_left(T (&array)[size], const unsigned int offset)
	{
		for (unsigned int i = offset; i < size; ++i) {
			array[i - offset] = array[i];
		}
	}

}
