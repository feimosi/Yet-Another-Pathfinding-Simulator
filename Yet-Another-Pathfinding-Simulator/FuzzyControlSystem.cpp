#include "stdafx.h"
#include "FuzzyControlSystem.h"

using namespace yaps;

FuzzyControlSystem::FuzzyControlSystem(Settings &settingsRef) : fuzzifier(), settings(settingsRef),
        defuzzifier(settingsRef.MAX_ANGLE, settingsRef.MAX_SPEED) { }

FuzzyControlSystem::~FuzzyControlSystem() { }

bool FuzzyControlSystem::run(std::vector<float> front, std::vector<float> left, std::vector<float> right, float minValue, float maxValue) {
    // If no data is passed return
    if (front.size() == 0 && left.size() == 0 && right.size() == 0)
        return false;

    float avgFront, avgLeft, avgRight;  // Average values for each vector
    avgFront = avgLeft = avgRight = 0;

    for (unsigned i = 0; i < front.size(); i++)
        avgFront += front[i];
    avgFront /= front.size() != 0 ? front.size() : 1;

    for (unsigned i = 0; i < left.size(); i++)
        avgLeft += left[i];
    avgLeft /= left.size() != 0 ? left.size() : 1;

    for (unsigned i = 0; i < right.size(); i++)
        avgRight += right[i];
    avgRight /= right.size() != 0 ? right.size() : 1;

    // Run fuzzifier to fuzzify input
    const DataMatrix<float> &fuzzySets = fuzzifier.fuzzify(avgFront, avgLeft, avgRight, minValue, (minValue + maxValue) / 2, maxValue);
    // Run inference engine to determine output according to the rule base
    auto fuzzyOutputList = inferenceEngine.processInput(fuzzySets, ruleBase);
    // Defuzzify results
    auto resultPair = defuzzifier.defuzzify(fuzzyOutputList);
    // Assign final output
    angle = resultPair.first;
    speed = resultPair.second;
#ifdef DEBUG
    std::cout << "---------------------------\n" << "FuzzyControlSystem\n\n" 
        << "Max depth: " << settings.getMaxDepth() << '\n'
        << "Average front: " << avgFront << '\n'
        << "Average left: " << avgLeft << '\n'
        << "Average right: " << avgRight << '\n'
        << "Angle: " << angle << '\n'
        << "Speed: " << speed << '\n'
        << " s\n---------------------------\n";
#endif
    return true;
}

FuzzyControlSystem::Fuzzifier::Fuzzifier() : fuzzySets(INPUT_VARIABLES, FUZZY_SETS) {
    // Allocate memory and assign lambda functions
    membershipFunctions = new std::function<float(float, float, float, float)>[3];
    membershipFunctions[LOW] = [](float x, float sA, float sB, float sC) -> float {
        return x < sA ? 1.f : x > sB ? 0.f : (sB - x) / (sB - sA);
    };
    membershipFunctions[MEDIUM] = [](float x, float sA, float sB, float sC) -> float {
        return x < sA || x > sC ? 0.f
            : x < sB ? (x - sA) / (sB - sA)
            : (sC - x) / (sC - sB);
    };
    membershipFunctions[HIGH] = [](float x, float sA, float sB, float sC) -> float {
        return x > sC ? 1.f : x < sB ? 0.f : (x - sB) / (sC - sB);
    };
}

const DataMatrix<float> &FuzzyControlSystem::Fuzzifier::fuzzify(float front, float left, float right, float lowSet, float mediumSet, float highSet) {
    // Calculate input relation to fuzzy sets 
    for (int i = 0; i < FUZZY_SETS; i++) {
        fuzzySets[FRONT][i] = membershipFunctions[i](front, lowSet, mediumSet, highSet);
        fuzzySets[LEFT][i]  = membershipFunctions[i](left, lowSet, mediumSet, highSet);
        fuzzySets[RIGHT][i] = membershipFunctions[i](right, lowSet, mediumSet, highSet);
    }
#ifdef VERBOSE_DEBUG
        std::cout << "Front = " << front << " Left = " << left << " Right = " << right << '\n';
        printFuzzySets();
#endif
    return fuzzySets;
}

void FuzzyControlSystem::Fuzzifier::printFuzzySets() {
    std::cout << "Fuzzy sets:\n";
    std::cout << "Front\tLeft\tRight\n";
    for (int i = 0; i < INPUT_VARIABLES; i++) {
        for (int j = 0; j < FUZZY_SETS; j++)
            std::cout << fuzzySets[j][i] << '\t';
        std::cout << '\n';
    }
}

FuzzyControlSystem::RuleBase::RuleBase() {
    // [front] [left] [right]
    // turn right - positive angle
    // turn left  - negative angle
    typedef std::pair<outputAngle, outputSpeed> output;
    rules[HIGH][HIGH][HIGH]     = output(ZERO,      VERY_FAST);
    rules[HIGH][HIGH][MEDIUM]   = output(N_QUARTER, VERY_FAST);
    rules[HIGH][HIGH][LOW]      = output(N_HALF,    FAST);
    rules[HIGH][MEDIUM][HIGH]   = output(QUARTER,   VERY_FAST);
    rules[HIGH][MEDIUM][MEDIUM] = output(ZERO,      VERY_FAST);
    rules[HIGH][MEDIUM][LOW]    = output(N_QUARTER, FAST);
    rules[HIGH][LOW][HIGH]      = output(HALF,      FAST);
    rules[HIGH][LOW][MEDIUM]    = output(QUARTER,   FAST);
    rules[HIGH][LOW][LOW]       = output(ZERO,      FAST);

    rules[MEDIUM][HIGH][HIGH]   = output(ZERO,      FAST);
    rules[MEDIUM][HIGH][MEDIUM] = output(N_HALF,    FAST);
    rules[MEDIUM][HIGH][LOW]    = output(N_FULL,    MODERATE);
    rules[MEDIUM][MEDIUM][HIGH] = output(HALF,      FAST);
    rules[MEDIUM][MEDIUM][MEDIUM] = output(ZERO,    FAST);
    rules[MEDIUM][MEDIUM][LOW]  = output(N_HALF,    MODERATE);
    rules[MEDIUM][LOW][HIGH]    = output(FULL,      MODERATE);
    rules[MEDIUM][LOW][MEDIUM]  = output(HALF,      MODERATE);
    rules[MEDIUM][LOW][LOW]     = output(ZERO,      MODERATE);

    rules[LOW][HIGH][HIGH]      = output(ZERO,      SLOW);
    rules[LOW][HIGH][MEDIUM]    = output(N_FULL,    SLOW);
    rules[LOW][HIGH][LOW]       = output(N_FULL,    VERY_SLOW);
    rules[LOW][MEDIUM][HIGH]    = output(FULL,      SLOW);
    rules[LOW][MEDIUM][MEDIUM]  = output(ZERO,      SLOW);
    rules[LOW][MEDIUM][LOW]     = output(N_FULL,    VERY_SLOW);
    rules[LOW][LOW][HIGH]       = output(FULL,      VERY_SLOW);
    rules[LOW][LOW][MEDIUM]     = output(FULL,      VERY_SLOW);
    rules[LOW][LOW][LOW]        = output(ZERO,      VERY_SLOW);
}

std::pair<FuzzyControlSystem::outputAngle, FuzzyControlSystem::outputSpeed> FuzzyControlSystem::RuleBase::giveOutputSets(inputValue front, inputValue left, inputValue right) {
    return rules[front][left][right];
}

FuzzyControlSystem::InferenceEngine::InferenceEngine() { }

std::vector< std::pair< std::pair<FuzzyControlSystem::outputAngle, FuzzyControlSystem::outputSpeed>, float> > FuzzyControlSystem::InferenceEngine::processInput(const DataMatrix<float> &fuzzySets, RuleBase &rulebase) {
    std::vector< std::pair< std::pair<outputAngle, outputSpeed>, float> > result;
    // For every combination of fuzzy sets of input
    for (int v1 = LOW; v1 <= HIGH; v1++) {
        for (int v2 = LOW; v2 <= HIGH; v2++) {
            for (int v3 = LOW; v3 <= HIGH; v3++) {
                float front = fuzzySets[FRONT][v1],
                      left  = fuzzySets[LEFT][v2],
                      right = fuzzySets[RIGHT][v3];
                if (front != 0 && left != 0 && right != 0) {
                    result.push_back(std::pair< std::pair<outputAngle, outputSpeed>, float>(
                        rulebase.giveOutputSets((inputValue)v1, (inputValue)v2, (inputValue)v3), fminf(fminf(front, left), right))
                    );
                }
            }
        }
    }
#ifdef VERBOSE_DEBUG
    std::cout << "Result list: \n";
    for (unsigned i = 0; i < result.size(); i++) {
        std::cout << "Angle set: " << result[i].first.first << " Speed set: " << result[i].first.second << " Value: " << result[i].second << '\n';
    }
#endif
    return result;
}

FuzzyControlSystem::Defuzzifier::Defuzzifier(float maxAngle, float maxSpeed) {
    // Initialise angle sets delimiters
    angleSetsValues[N_FULL]     = -maxAngle;
    angleSetsValues[N_HALF]     = -maxAngle / 2;
    angleSetsValues[N_QUARTER]  = -maxAngle / 4;
    angleSetsValues[ZERO]       = 0;
    angleSetsValues[QUARTER]    = maxAngle / 4;
    angleSetsValues[HALF]       = maxAngle / 2;
    angleSetsValues[FULL]       = maxAngle;
    // Initialise speed sets delimiter
    float speed = 0;
    for (int i = 0; i < SPEED_SETS; i++) {
        speed += maxSpeed / SPEED_SETS;
        speedSetsValues[i] = speed;
    }
}

std::pair<float, float> FuzzyControlSystem::Defuzzifier::defuzzify(std::vector< std::pair< std::pair<outputAngle, outputSpeed>, float> > &outputList) {
    float dividantAngle, divisorAngle, dividantSpeed, divisorSpeed, fuzzyValue;
    std::pair<outputAngle, outputSpeed> outputType;
    dividantAngle = divisorAngle = dividantSpeed = divisorSpeed = 0;
    // Calculate final output using arithmetic mean
    for (unsigned i = 0; i < outputList.size(); i++) {
        fuzzyValue = outputList[i].second;
        outputType = outputList[i].first;
        dividantAngle += fuzzyValue * angleSetsValues[outputType.first];
        divisorAngle += fuzzyValue;
        dividantSpeed += fuzzyValue * speedSetsValues[outputType.second];
        divisorSpeed += fuzzyValue;
    }
    // Return defuzzified value for angle and speed
    return std::pair<float, float>(
        divisorAngle != 0 ? dividantAngle / divisorAngle : 0, 
        dividantSpeed / divisorSpeed
    );
}