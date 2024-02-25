#include "Universal.h"
#include "Function.h"
#include "Negative.h"

#include <memory>


Universal::Universal(VariableCollection&& variables, ThermPtr child)
	: mVariables(std::move(variables))
	, mChild(child)
{

}

AbstractTherm::ReducedTherm Universal::reduce(bool isNegative) {
	mIsProcessed = true;
	auto vars = mVariables;
	++mVarCounter;
	for (auto& var : vars) {
		var += std::to_string(mVarCounter);
	}
	if (isNegative) {
		return ReducedTherm{
			ReducedThermWithoutDivison{
				std::make_shared<Negative>(std::make_shared<Function>(mChild->getName(), std::move(vars)))
			}
		};
	}
	else {
		return ReducedTherm{
			ReducedThermWithoutDivison{ std::make_shared<Function>(mChild->getName(), std::move(vars))}
		};
	}
}

ReduceThermType Universal::reduceType(bool isNegative) {
	if (mIsProcessed) {
		return ReduceThermType::NonReducable;
	}
	return ReduceThermType::ReducableWithoutDivision;
}

bool Universal::needDuplicate(bool isNegative) {
	return !isNegative;
}

AbstractTherm::ThermPtr Universal::copy() {
	auto variables = mVariables;
	return std::make_shared<Universal>(std::move(variables), mChild->copy());
}

void Universal::print(std::ostream& os) {
	os << "#(";
	os << mVariables[0];
	for (size_t i = 1; i < mVariables.size(); ++i) {
		os << "," << mVariables[i];
	}
	os << ")(";
	mChild->print(os);
	os << ")";
}