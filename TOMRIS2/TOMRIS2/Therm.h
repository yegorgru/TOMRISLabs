#pragma once

#include "AbstractTherm.h"

class Therm : public AbstractTherm
{
public:
	Therm(const std::string& name);
public:
	ReducedTherm reduce(bool isNegative) override;
	ReduceThermType reduceType(bool isNegative) override;
	ThermPtr copy() override;
	void print(std::ostream& os) override;
private:
	std::string mName;
};

