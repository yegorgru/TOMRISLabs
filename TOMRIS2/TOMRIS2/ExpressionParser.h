#pragma once

#include "AbstractTherm.h"

#include <memory>
#include <string_view>
#include <utility>

class ExpressionParser
{
public:
	using ThermCollection = std::vector<AbstractTherm::ThermPtr>;
public:
	ThermCollection parseExpression(const std::string& expression);
private:
	AbstractTherm::ThermPtr parseNextTherm(std::string_view input);
	AbstractTherm::ThermPtr parseTherm(char input);
	AbstractTherm::ThermPtr parseFunction(std::string_view input);
	AbstractTherm::VariableCollection parseVariables(std::string_view input);
	AbstractTherm::ThermPtr parseNegative(std::string_view input);
	AbstractTherm::ThermPtr parseImplication(std::string_view input);
	AbstractTherm::ThermPtr parseUniversal(std::string_view input);
	AbstractTherm::ThermPtr parseExistential(std::string_view input);
	AbstractTherm::ThermPtr parseConjunction(std::string_view input);
	AbstractTherm::ThermPtr parseDisjunction(std::string_view input);
private:
	using LeftRightChildren = std::pair<AbstractTherm::ThermPtr, AbstractTherm::ThermPtr>;
private:
	LeftRightChildren findLeftAndRightChildren(std::string_view input);
};

