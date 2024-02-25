#include "Conjunction.h"
#include "Negative.h"

#include <memory>

Conjunction::Conjunction(ThermPtr left, ThermPtr right)
	: mLeft(left)
	, mRight(right)
{

}

AbstractTherm::ReducedTherm Conjunction::reduce(bool isNegative) {
	mIsProcessed = true;
	return isNegative ? 
		ReducedTherm{ ReducedThermWithDivison{ std::make_shared<Negative>(mLeft), std::make_shared<Negative>(mRight) } } :
		ReducedTherm{ ReducedThermWithoutDivison{ mLeft, mRight } };
}

ReduceThermType Conjunction::reduceType(bool isNegative) {
	if (mIsProcessed) {
		return ReduceThermType::NonReducable;
	}
	return isNegative ? ReduceThermType::ReducableWithDivision : ReduceThermType::ReducableWithoutDivision;
}

AbstractTherm::ThermPtr Conjunction::copy() {
	return std::make_shared<Conjunction>(mLeft->copy(), mRight->copy());
}

void Conjunction::print(std::ostream& os) {
	os << "&(";
	mLeft->print(os);
	os << ")(";
	mRight->print(os);
	os << ")";
}