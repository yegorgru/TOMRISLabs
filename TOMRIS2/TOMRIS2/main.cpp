#include <iostream>

#include "ExpressionParser.h"
#include "Reducer.h"

int main()
{
    ExpressionParser ep;
    Reducer reducer;
    std::string input;
    while (input != "exit") {
        std::cout << "Enter expression:" << std::endl;
        std::getline(std::cin, input);
        if (input == "help") {
            std::cout << "Therm:        uppercase letter" << std::endl;
            std::cout << "Function:     *(<name>)(<var1>,<var2>,...) where name is uppercase letters and vars are lowercase letters" << std::endl;
            std::cout << "Negative:     !(<therm>) where therm is another therm" << std::endl;
            std::cout << "Implication:  >(<therm1>)(<therm2>) where therm1, therm2 are other therms" << std::endl;
            std::cout << "Conjunction:  &(<therm1>)(<therm2>) where therm1, therm2 are other therms" << std::endl;
            std::cout << "Disjunction:  |(<therm1>)(<therm2>) where therm1, therm2 are other therms" << std::endl;
            std::cout << "Disjunction:  |(<therm1>)(<therm2>) where therm1, therm2 are other therms" << std::endl;
            std::cout << "Universal:    #(<var1>)(<function>) where var is lowercase letter, function is Function" << std::endl;
            std::cout << "Existential:  $(<var1>)(<function>) where var is lowercase letter, function is Function" << std::endl;
            continue;
        }
        try
        {
            auto expression = ep.parseExpression(input);
            auto reduceCollections = reducer.reduce(expression);
            for (const auto& collection : reduceCollections) {
                std::cout << "{ ";
                for (size_t i = 0; i < collection.size(); ++i) {
                    collection[i]->print(std::cout);
                    if (i != collection.size() - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << " }" << std::endl;
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}
