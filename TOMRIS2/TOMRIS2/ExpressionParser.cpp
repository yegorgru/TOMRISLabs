#include "ExpressionParser.h"
#include "Therm.h"
#include "Conjunction.h"
#include "Function.h"
#include "Negative.h"
#include "Implication.h"
#include "Conjunction.h"
#include "Disjunction.h"
#include "Universal.h"
#include "Existential.h"

#include <stdexcept>

ExpressionParser::ThermCollection ExpressionParser::parseExpression(const std::string& expression) {
	size_t firstPos = 0;
	size_t lastPos = expression.find(' ');
	ThermCollection collection;
	while (lastPos != std::string::npos) {
		collection.push_back(parseNextTherm(std::string_view(expression.begin() + firstPos, expression.begin() + lastPos)));
		firstPos = lastPos + 1;
		lastPos = expression.find(' ', firstPos);
	}
	collection.push_back(parseNextTherm(std::string_view(expression.begin() + firstPos, expression.end())));
	return collection;
}

AbstractTherm::ThermPtr ExpressionParser::parseNextTherm(std::string_view input) {
	if (input.front() == '(') {
		input.remove_prefix(1);
		if (input.back() == ')') {
			input.remove_suffix(1);
		}
	}
	if (input.size() == 0) {
		throw std::runtime_error("Incorrect specification. Expected not-empty symbol");
	}
	const char operation = input.front();
	input.remove_prefix(1);
	switch (operation) {
	case '&':
		return parseConjunction(input);
	case '|':
		return parseDisjunction(input);
	case '>':
		return parseImplication(input);
	case '!':
		return parseNegative(input);
	case '*':
		return parseFunction(input);
	case '#':
		return parseUniversal(input);
	case '$':
		return parseExistential(input);
	default:
		return parseTherm(operation);
	}
}

AbstractTherm::ThermPtr ExpressionParser::parseTherm(char input) {
	if (input < 'A' || input > 'Z') {
		throw std::runtime_error("Incorrect therm name. It should be uppercase single symbol");
	}
	return std::make_shared<Therm>(std::string(1, input));
}

AbstractTherm::ThermPtr ExpressionParser::parseFunction(std::string_view input) {
	if (input.size() < 5 || input[0] != '(' || input[2] != ')' || input[3] != '(') {
		throw std::runtime_error("Incorrect function specification. It should be *(<name>)(<var1>,<var2>,...)");
	}
	const char chName = input[1];
	if (chName < 'A' || chName > 'Z') {
		throw std::runtime_error("Incorrect function name. It should be uppercase single symbol");
	}
	std::string name(1, chName);
	input.remove_prefix(3);
	auto variables = parseVariables(input);
	return std::make_shared<Function>(name, std::move(variables));
}

AbstractTherm::VariableCollection ExpressionParser::parseVariables(std::string_view input) {
	if (input.size() < 3 || input.front() != '(' || input.back() != ')' || input.size() % 2 == 0) {
		throw std::runtime_error("Incorrect variables specification. It should be (<var1>,<var2>,...)");
	}
	input.remove_prefix(1);
	input.remove_suffix(1);
	AbstractTherm::VariableCollection result;
	for (size_t pos = 0; pos < input.size(); ++pos) {
		if (pos % 2 == 1) {
			if (input[pos] != ',') {
				throw std::runtime_error("Incorrect variables specification. It should be (<var1>,<var2>,...)");
			}
			else {
				continue;
			}
		}
		char var = input[pos];
		if (var < 'a' || var > 'z') {
			throw std::runtime_error("Incorrect variable name. It should be lowercase single symbol");
		}
		result.push_back(std::string(1, var));
	}
	return result;
}

AbstractTherm::ThermPtr ExpressionParser::parseNegative(std::string_view input) {
	if (input.front() != '(' || input.back() != ')') {
		throw std::runtime_error("Incorrect negative specification. It should be !(<therm>)");
	}
	auto child = parseNextTherm(input);
	return std::make_shared<Negative>(child);
}

AbstractTherm::ThermPtr ExpressionParser::parseImplication(std::string_view input) {
	auto children = findLeftAndRightChildren(input);
	return std::make_shared<Implication>(children.first, children.second);
}

AbstractTherm::ThermPtr ExpressionParser::parseUniversal(std::string_view input) {
	if (input.front() != '(' || input.back() != ')') {
		throw std::runtime_error("Incorrect universal specification. It should be #(<var1>)(<function>)");
	}
	int counter = 0;
	size_t pos = 0;
	while (pos < input.size()) {
		if (input[pos] == '(') {
			++counter;
		}
		else if (input[pos] == ')') {
			--counter;
			if (counter == 0) {
				break;
			}
		}
		++pos;
	}
	if (pos >= input.size() - 1) {
		throw std::runtime_error("Incorrect universal specification. It should be #(<var1>,<var2>,...)(<function>)");
	}
	auto variables = parseVariables(input.substr(0, pos + 1));
	auto child = parseNextTherm(input.substr(pos + 1));
	return std::make_shared<Universal>(std::move(variables), child);
}

AbstractTherm::ThermPtr ExpressionParser::parseExistential(std::string_view input) {
	if (input.front() != '(' || input.back() != ')') {
		throw std::runtime_error("Incorrect existential specification. It should be $(<var1>,<var2>,...)(<function>)");
	}
	int counter = 0;
	size_t pos = 0;
	while (pos < input.size()) {
		if (input[pos] == '(') {
			++counter;
		}
		else if (input[pos] == ')') {
			--counter;
			if (counter == 0) {
				break;
			}
		}
		++pos;
	}
	if (pos >= input.size() - 1) {
		throw std::runtime_error("Incorrect existential specification. It should be $(<var1>,<var2>,...)(<function>)");
	}
	auto variables = parseVariables(input.substr(0, pos + 1));
	auto child = parseNextTherm(input.substr(pos + 1));
	return std::make_shared<Existential>(std::move(variables), child);
}

AbstractTherm::ThermPtr ExpressionParser::parseConjunction(std::string_view input) {
	auto children = findLeftAndRightChildren(input);
	return std::make_shared<Conjunction>(children.first, children.second);
}

AbstractTherm::ThermPtr ExpressionParser::parseDisjunction(std::string_view input) {
	auto children = findLeftAndRightChildren(input);
	return std::make_shared<Disjunction>(children.first, children.second);
}

ExpressionParser::LeftRightChildren ExpressionParser::findLeftAndRightChildren(std::string_view input) {
	if (input.front() != '(' || input.back() != ')') {
		throw std::runtime_error("Incorrect left and right children specification. It should be (<therm1>)(<therm2>)");
	}
	int counter = 0;
	size_t pos = 0;
	while (pos < input.size()) {
		if (input[pos] == '(') {
			++counter;
		}
		else if (input[pos] == ')') {
			--counter;
			if (counter == 0) {
				break;
			}
		}
		++pos;
	}
	if (pos >= input.size() - 1) {
		throw std::runtime_error("Incorrect left and right children specification. It should be (<therm1>)(<therm2>)");
	}
	auto left = parseNextTherm(input.substr(0, pos + 1));
	if (input[pos + 1] != '(') {
		throw std::runtime_error("Incorrect left and right children specification. It should be (<therm1>)(<therm2>)");
	}
	counter = 0;
	++pos;
	size_t rightBegin = pos;
	while (pos < input.size()) {
		if (input[pos] == '(') {
			++counter;
		}
		else if (input[pos] == ')') {
			--counter;
			if (counter == 0) {
				break;
			}
		}
		++pos;
	}
	if (pos != input.size() - 1) {
		throw std::runtime_error("Incorrect left and right children specification. It should be (<therm1>)(<therm2>)");
	}
	auto right = parseNextTherm(input.substr(rightBegin));
	return { left, right };
}