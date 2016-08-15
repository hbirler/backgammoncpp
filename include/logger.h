#pragma once

#include "network.h"
#include "learn.h"
#include "tavla.h"
#include "buzinessman.h"
#include <iostream>
#include <iomanip>
#include <map>

class logger
{
public:
	logger(std::ostream* os);
	~logger();

	/*template <typename T>
	void log(std::map<std::string, T> data);
	template <>*/
	void log(std::map<std::string, double> data);

private:
	std::ostream* out;
};
