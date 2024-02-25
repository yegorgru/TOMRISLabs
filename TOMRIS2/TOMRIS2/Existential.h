#pragma once

#include "AbstractTherm.h"

class Existential : public AbstractTherm
{
public:
	Existential(VariableCollection&& variables, ThermPtr child);
public:
	ReducedTherm reduce(bool isNegative) override;
	ReduceThermType reduceType(bool isNegative) override;
	bool needDuplicate(bool isNegative) override;
	ThermPtr copy() override;
	void print(std::ostream& os) override;
private:
	VariableCollection mVariables;
	ThermPtr mChild;
};

