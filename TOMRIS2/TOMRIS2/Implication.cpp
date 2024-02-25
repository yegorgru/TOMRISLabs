#include "Implication.h"
#include "Negative.h"

Implication::Implication(ThermPtr left, ThermPtr right)
	: mLeft(left)
	, mRight(right)
{

}

AbstractTherm::ReducedTherm Implication::reduce(bool isNegative) {
	mIsProcessed = true;
	return isNegative ?
		ReducedTherm{ ReducedThermWithoutDivison{ mLeft, std::make_shared<Negative>(mRight) } } :
		ReducedTherm{ ReducedThermWithDivison{ std::make_shared<Negative>(mLeft), mRight } };
}

ReduceThermType Implication::reduceType(bool isNegative) {
	if (mIsProcessed) {
		return ReduceThermType::NonReducable;
	}
	return isNegative ? ReduceThermType::ReducableWithoutDivision : ReduceThermType::ReducableWithDivision;
}

AbstractTherm::ThermPtr Implication::copy() {
	return std::make_shared<Implication>(mLeft->copy(), mRight->copy());
}

void Implication::print(std::ostream& os) {
	os << ">(";
	mLeft->print(os);
	os << ")(";
	mRight->print(os);
	os << ")";
}