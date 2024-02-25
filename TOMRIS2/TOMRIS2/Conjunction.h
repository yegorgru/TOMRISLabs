#pragma once

#include "AbstractTherm.h"

class Conjunction : public AbstractTherm
{
public:
	Conjunction(ThermPtr left, ThermPtr right);
public:
	ReducedTherm reduce(bool isNegative) override;
	ReduceThermType reduceType(bool isNegative) override;
	ThermPtr copy() override;
	void print(std::ostream& os) override;
private:
	ThermPtr mLeft;
	ThermPtr mRight;
};

