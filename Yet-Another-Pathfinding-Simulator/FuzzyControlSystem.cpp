#include "stdafx.h"
#include "FuzzyControlSystem.h"

using namespace yaps;

FuzzyControlSystem::FuzzyControlSystem() {

}

FuzzyControlSystem::~FuzzyControlSystem() {

}

bool FuzzyControlSystem::run(std::vector<int> front, std::vector<int> left, std::vector<int> right) {
    return false;
}

FuzzyControlSystem::Fuzzifier::Fuzzifier() {
	// Allocate memory and assign lambda functions
	membershipFunctions = new std::function<int(int, int, int, int)>[3];
	membershipFunctions[LOW] = [](int x, int sA, int sB, int sC) -> int {
		return x < sA ? 1 : x > sB ? 0 : (sB - x) / (sB - sA);
	};
	membershipFunctions[MEDIUM] = [](int x, int sA, int sB, int sC) -> int {
		return x < sA || x > sC ? 0
			: x < sB ? (x - sA) / (sB - sA)
			: (sC - x) / (sC - sB);
	};
	membershipFunctions[HIGH] = [](int x, int sA, int sB, int sC) -> int {
		return x > sC ? 1 : x < sB ? 0 : (x - sB) / (sC - sB);
	};
}

void FuzzyControlSystem::Fuzzifier::fuziffy(int front, int left, int right) {
	// Calculate input relation to fuzzy sets
	for (int i = 0; i < 3; i++) {
		fuzzySets[FRONT][i] = membershipFunctions[i](1, low, medium, high);
        fuzzySets[LEFT][i] = membershipFunctions[i](1, low, medium, high);
        fuzzySets[RIGHT][i] = membershipFunctions[i](1, low, medium, high);
	}
}