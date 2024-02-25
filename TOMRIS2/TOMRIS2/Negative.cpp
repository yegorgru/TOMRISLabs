#include "Negative.h"

Negative::Negative(ThermPtr child)
	: mChild(child)
{

}

AbstractTherm::ReducedTherm Negative::reduce(bool isNegative) {
	mIsProcessed = true;
	return isNegative ?
		ReducedTherm{ ReducedThermWithoutDivison{ mChild } } :
		mChild->reduce(true);
}

ReduceThermType Negative::reduceType(bool isNegative) {
	if (mIsProcessed) {
		return ReduceThermType::NonReducable;
	}
	return isNegative ? ReduceThermType::ReducableWithoutDivision : mChild->reduceType(true);
}

bool Negative::needDuplicate(bool isNegative) {
	return isNegative ? false : mChild->needDuplicate(true);
}

AbstractTherm::ThermPtr Negative::copy() {
	return std::make_shared<Negative>(mChild->copy());
}

void Negative::print(std::ostream& os) {
	os << "!(";
	mChild->print(os);
	os << ")";
}