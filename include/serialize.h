#ifndef SERIALIZEH
#define SERIALIZEH

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

	union_bytes<T> mynet;
	mynet.val = val;

	ofstream outputBuffer(path, ios::out | ios::binary | ios::trunc);

	outputBuffer.write(mynet.bytes, sizeof(mynet.bytes));

	outputBuffer.close();
}


template <typename T>
T deserialize(const std::string& path)
{
	using namespace std;
	union_bytes<T> mynet;
	ifstream fileBuffer(path, ios::in | ios::binary);

	if (fileBuffer.is_open())
	{
		fileBuffer.seekg(0, ios::beg);
		fileBuffer.getline(mynet.bytes, sizeof(mynet.bytes));
	}

	fileBuffer.close();
	return mynet.val;
}

#endif