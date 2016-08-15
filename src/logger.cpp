#include "logger.h"

logger::logger(std::ostream* os)
{
	this->out = os;
}

logger::~logger()
{
}
/*template <typename T>
void logger::log(std::map<std::string, T> data)
{
	*(this->out) << "{";
	bool first = true;
	for (auto& kv : data) {
		if (!first)
			*(this->out) << ",";
		else
			first = false;
		*(this->out) << "\"" << kv.first << "\":\"" << kv.second << "\"";
	}
	*(this->out) << "}" << std::endl;
}

template <>*/
void logger::log(std::map<std::string, double> data)
{
	*(this->out) << "{";
	bool first = true;
	for (auto& kv : data) {
		if (!first)
			*(this->out) << ",";
		else
			first = false;
		*(this->out) << "\"" << kv.first << "\":" << std::fixed << kv.second;
	}
	*(this->out) << "}" << std::endl;
}
