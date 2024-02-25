#include "Therm.h"

Therm::Therm(const std::string& name)
	: mName(name)
{

}

AbstractTherm::ReducedTherm Therm::reduce(bool isNegative) {
	throw std::runtime_error("call reduce on Therm");
	mIsProcessed = true;
	return AbstractTherm::ReducedTherm();
}

ReduceThermType Therm::reduceType(bool isNegative) {
	return ReduceThermType::NonReducable;
}

AbstractTherm::ThermPtr Therm::copy() {
	return std::make_shared<Therm>(mName);
}

void Therm::print(std::ostream& os) {
	os << mName;
}