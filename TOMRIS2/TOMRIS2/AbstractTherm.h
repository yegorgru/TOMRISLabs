#pragma once

#include "ReduceThermType.h"

#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <variant>
#include <ostream>

class AbstractTherm : public std::enable_shared_from_this<AbstractTherm> {
public:
	using ThermPtr = std::shared_ptr<AbstractTherm>;
	using ReducedThermWithoutDivison = std::vector<ThermPtr>;
	using ReducedThermWithDivison = std::pair<ThermPtr, ThermPtr>;
	using ReducedTherm = std::variant<ReducedThermWithoutDivison, ReducedThermWithDivison>;
	using Variable = std::string;
	using VariableCollection = std::vector<Variable>;
public:
	virtual ~AbstractTherm() = default;
public:
	virtual ReducedTherm reduce(bool isNegative) = 0;
	virtual ReduceThermType reduceType(bool isNegative) = 0;
	virtual ThermPtr copy() = 0;
	virtual bool needDuplicate(bool isNegative) {
		return false;
	}
	virtual std::string getName() {
		return "";
	}
	virtual void print(std::ostream& os) = 0;
protected:
	inline static int mVarCounter = 0;
protected:
	bool mIsProcessed = false;
};