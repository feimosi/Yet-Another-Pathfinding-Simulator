#pragma once


namespace yaps {

	class FuzzyControlSystem {
		class Fuzzifier {
			static const short FRONT = 0, LEFT = 1,	RIGHT = 2;	// Array indexes for specific input and fuzzy set
			static const short LOW = 0,	MEDIUM = 1,	HIGH = 2;	// --||--
			int frontLow, frontMedium, frontHigh;				//	|
			int leftLow, leftMedium, leftHigh;					//	Different ranges in fuzzy sets 
			int rightLow, rightMedium, rightHigh;				//	|
			std::function<int(int, int, int, int)> *membershipFunctions;
			int fuzzySets[3][3];								// 3 input variables x 3 sets
		public:
			Fuzzifier();
			void fuziffy(int, int, int);
		};
		class InferenceEngine;
		class RuleBase;
		class Defuzzifier;

		Fuzzifier fuzzifier;
	public:
		FuzzyControlSystem();
		~FuzzyControlSystem();
	};

}