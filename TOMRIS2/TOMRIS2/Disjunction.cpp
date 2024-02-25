#include "Disjunction.h"
#include "Negative.h"

#include <memory>

Disjunction::Disjunction(ThermPtr left, ThermPtr right)
	: mLeft(left)
	, mRight(right)
{

}

AbstractTherm::ReducedTherm Disjunction::reduce(bool isNegative) {
	mIsProcessed = true;
	return isNegative ?
		ReducedTherm{ ReducedThermWithoutDivison{ std::make_shared<Negative>(mLeft), std::make_shared<Negative>(mRight) } } :
		ReducedTherm{ ReducedThermWithDivison{ mLeft, mRight } };
}

ReduceThermType Disjunction::reduceType(bool isNegative) {
	if (mIsProcessed) {
		return ReduceThermType::NonReducable;
	}
	return isNegative ? ReduceThermType::ReducableWithoutDivision : ReduceThermType::ReducableWithDivision;
}

AbstractTherm::ThermPtr Disjunction::copy() {
	return std::make_shared<Disjunction>(mLeft->copy(), mRight->copy());
}

void Disjunction::print(std::ostream& os) {
	os << "|(";
	mLeft->print(os);
	os << ")(";
	mRight->print(os);
	os << ")";
}