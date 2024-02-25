#pragma once

#include "AbstractTherm.h"

class Negative : public AbstractTherm
{
public:
	Negative(ThermPtr child);
public:
	ReducedTherm reduce(bool isNegative) override;
	ReduceThermType reduceType(bool isNegative) override;
	bool needDuplicate(bool isNegative) override;
	ThermPtr copy() override;
	void print(std::ostream& os) override;
private:
	ThermPtr mChild;
};

