#include "Reducer.h"

Reducer::Collections Reducer::reduce(const ThermCollection& collection) {
	ReduceThermType type = ReduceThermType::NonReducable;
	size_t withDivisionIdx = 0;
	for (size_t i = 0; i < collection.size(); ++i) {
		if (collection[i]->reduceType(false) == ReduceThermType::ReducableWithoutDivision) {
			type = ReduceThermType::ReducableWithoutDivision;
		}
		if (collection[i]->reduceType(false) == ReduceThermType::ReducableWithDivision && type != ReduceThermType::ReducableWithoutDivision) {
			type = ReduceThermType::ReducableWithDivision;
			withDivisionIdx = i;
		}
	}
	if (type == ReduceThermType::NonReducable) {
		return { collection };
	}
	else if (type == ReduceThermType::ReducableWithoutDivision) {
		ThermCollection nextCollection;
		ThermCollection dups;
		for (size_t i = 0; i < collection.size(); ++i) {
			if (collection[i]->reduceType(false) == ReduceThermType::ReducableWithoutDivision) {
				auto reducedTherms = std::get<AbstractTherm::ReducedThermWithoutDivison>(collection[i]->reduce(false));
				if (collection[i]->needDuplicate(false)) {
					dups.push_back(collection[i]);
				}
				for (auto therm : reducedTherms) {
					nextCollection.push_back(therm);
				}
			}
			else {
				nextCollection.push_back(collection[i]);
			}
		}
		auto collections = reduce(nextCollection);
		for (auto& coll : collections) {
			for (const auto& dup : dups) {
				coll.push_back(dup);
			}
		}
		return collections;
	}
	else {
		auto partTherms = std::get<AbstractTherm::ReducedThermWithDivison>(collection[withDivisionIdx]->reduce(false));
		ThermCollection lhs;
		lhs.reserve(collection.size());
		ThermCollection rhs;
		rhs.reserve(collection.size());
		for (size_t i = 0; i < collection.size(); ++i) {
			if (i == withDivisionIdx) {
				continue;
			}
			lhs.push_back(collection[i]->copy());
			rhs.push_back(collection[i]->copy());
		}
		lhs.push_back(partTherms.first);
		rhs.push_back(partTherms.second);
		auto res = reduce(lhs);
		for (const auto& rhsRes : reduce(rhs)) {
			res.push_back(rhsRes);
		}
		return res;
	}
}