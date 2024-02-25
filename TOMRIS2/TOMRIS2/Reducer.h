#pragma once

#include "AbstractTherm.h"

class Reducer
{
public:
	using ThermCollection = std::vector<AbstractTherm::ThermPtr>;
	using Collections = std::vector<ThermCollection>;
public:
	Collections reduce(const ThermCollection& collection);
};

