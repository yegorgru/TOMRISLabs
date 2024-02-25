#include "Existential.h"
#include "Function.h"
#include "Negative.h"

#include <memory>

Existential::Existential(VariableCollection&& variables, ThermPtr child)
	: mVariables(std::move(variables))
	, mChild(child)
{

}

AbstractTherm::ReducedTherm Existential::reduce(bool isNegative) {
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

ReduceThermType Existential::reduceType(bool isNegative) {
	if (mIsProcessed) {
		return ReduceThermType::NonReducable;
	}
	return ReduceThermType::ReducableWithoutDivision;
}

bool Existential::needDuplicate(bool isNegative) {
	return isNegative;
}

AbstractTherm::ThermPtr Existential::copy() {
	auto variables = mVariables;
	return std::make_shared<Existential>(std::move(variables), mChild->copy());
}

void Existential::print(std::ostream& os) {
	os << "$(";
	os << mVariables[0];
	for (size_t i = 1; i < mVariables.size(); ++i) {
		os << "," << mVariables[i];
	}
	os << ")(";
	mChild->print(os);
	os << ")";
}