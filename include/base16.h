#pragma once

#include <string>
#include <cassert>

std::string encode_16(const char* data, int length);
void decode_16(const std::string& data, char* output);

template<typename T>
inline std::string encode_16(const T& data)
{
	return encode_16((const char*)&data, sizeof(T));
}

template<typename T>
inline void decode_16(const std::string& data, T * output)
{
	assert(sizeof(T) == data.length() / 2);
	decode_16(data, (char*)output);
}
