#include "Function.h"

Function::Function(const std::string& name, VariableCollection&& parameters)
	: mName(name)
	, mParameters(std::move(parameters))
{
	
}

AbstractTherm::ReducedTherm Function::reduce(bool isNegative) {
	throw std::runtime_error("call reduce on Function");
	mIsProcessed = true;
	return AbstractTherm::ReducedTherm();
}

ReduceThermType Function::reduceType(bool isNegative) {
	return ReduceThermType::NonReducable;
}

AbstractTherm::ThermPtr Function::copy() {
	auto parameters = mParameters;
	return std::make_shared<Function>(mName, std::move(parameters));
}

void Function::print(std::ostream& os) {
	os << "*(" << mName << ")(";
	os << mParameters[0];
	for (size_t i = 1; i < mParameters.size(); ++i) {
		os << "," << mParameters[i];
	}
	os << ")";
}