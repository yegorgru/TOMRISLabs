#pragma once
#include "AbstractTherm.h"

class Function : public AbstractTherm
{
public:
	Function(const std::string& name, VariableCollection&& parameters);
public:
	ReducedTherm reduce(bool isNegative) override;
	ReduceThermType reduceType(bool isNegative) override;
	std::string getName() override {
		return mName;
	}
	ThermPtr copy() override;
	void print(std::ostream& os) override;
private:
	std::string mName;
	VariableCollection mParameters;
};

