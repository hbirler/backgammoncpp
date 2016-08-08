#pragma once

#include <string>
#include <fstream>

template <class T>
void serialize(const std::string& path, T const& val);

template <class T>
T deserialize(const std::string& path);

template <typename T>
union union_bytes;

template <typename T>
union union_bytes
{
	T val;
	char bytes[sizeof(T)];
	union_bytes() {}
	~union_bytes() {}
};

template <typename T>
void serialize(const std::string& path, T const& val)
{
	using namespace std;

	ofstream outputBuffer(path, ios::out | ios::binary | ios::trunc);

	bool isopen = outputBuffer.is_open();

	int size = sizeof(T);

	outputBuffer.write((const char*)&val, size);

	outputBuffer.close();
}


template <typename T>
T deserialize(const std::string& path)
{
	using namespace std;
	ifstream fileBuffer(path, ios::in | ios::binary | ios::ate);

	T retval;
	int size = sizeof(T);
	int fsize = fileBuffer.tellg();

	if (fileBuffer.is_open())
	{
		//fileBuffer.clear();
		fileBuffer.seekg(0, ios::beg);
		fileBuffer.read((char*)&retval, size);
	}

	fileBuffer.close();
	return retval;
}
