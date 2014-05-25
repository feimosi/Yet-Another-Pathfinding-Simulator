#pragma once

namespace yaps {

    /**
     *  Decision support system using fuzzy logic
     *  @link http://en.wikipedia.org/wiki/Fuzzy_control_system
     *  There are 3 input variables which can belong to 3 different fuzzy sets each, but with the same delimiters:
     *  - Front (LOW, MEDIUM, HIGH)
     *  - Left (LOW, MEDIUM, HIGH)
     *  - Right (LOW, MEDIUM, HIGH)
     *  Output: Speed and angle
     */
	class FuzzyControlSystem {

		class Fuzzifier {
			static const short FRONT = 0, LEFT = 1,	RIGHT = 2;  // Array indexes for specific input and fuzzy set
			static const short LOW = 0,	MEDIUM = 1,	HIGH = 2;   // --||--
			int low, medium, high;                              //  Different ranges in fuzzy sets
			std::function<int(int, int, int, int)> *membershipFunctions;
			int fuzzySets[3][3];                                // 3 input variables x 3 sets
		public:
            /**
             *	Constructor
             *  Prepare membership functions
             */
			Fuzzifier();
            
            /**
             *	Fuzzify selected input by calculating membership on each fuzzy set
             *	@param front
             *	@param left
             *	@param right
             */
			void fuziffy(int, int, int);
		};
		class InferenceEngine;
		class RuleBase;
		class Defuzzifier;

		Fuzzifier fuzzifier;
        int speed;
        int angle;
	public:
        /**
         *	Constructor
         */
        FuzzyControlSystem();
        
        /**
         *	Constructor
         */
		~FuzzyControlSystem();

        /**
         *	Run the whole process
         *	@param front    Vector containing input values
         *	@param left     --||--
         *	@param right    --||--
         */
        bool run(std::vector<int>, std::vector<int>, std::vector<int>);
	};

}