#pragma once

namespace yaps {

    /**
     *  Decision support system using fuzzy logic
     *  @link http://en.wikipedia.org/wiki/Fuzzy_control_system
     *  There are 3 input variables which can belong to 3 different fuzzy sets each, but with the same delimiters:
     *  - Front (LOW, MEDIUM, HIGH)
     *  - Left  (LOW, MEDIUM, HIGH)
     *  - Right (LOW, MEDIUM, HIGH)
     *  They mean depth values of points which border on the boat.
     *  Output: Suggested speed and angle. Where positive angle means to turn right.
     */
    class FuzzyControlSystem {
        static const short INPUT_VARIABLES = 3; // Number of input variables
        static const short FUZZY_SETS = 3;      // Number of fuzzy sets per input variable
        enum inputType {
            FRONT, LEFT, RIGHT
        };
        enum inputValue {
            LOW, MEDIUM, HIGH
        };
        enum outputAngle {
            N_FULL, N_HALF, N_QUARTER,      // Negative angles
            ZERO,
            QUARTER, HALF, FULL             // Positive angles
        };
        enum outputSpeed {
            VERY_SLOW, SLOW, MODERATE, FAST, VERY_FAST
        };

        /**
         *  Inner class which transforms input to fuzzy values
         */
        class Fuzzifier {
            std::function<float(float, float, float, float)> *membershipFunctions;
            DataMatrix<float> fuzzySets;                // Fuzzy values for each variable in every fuzzy set
        public:
            /**
             *  Constructor
             *  Prepare membership functions
             */
            Fuzzifier();

            /**
             *  Fuzzify selected input by calculating membership on each fuzzy set
             *  @param front, left, right Input values to fuzzify
             *  @param lowSet, mediumSet, highSet Different ranges delimiters in fuzzy sets
             *  @return matrix with fuzzified values
             */
            const DataMatrix<float> &fuzzify(float, float, float, float, float, float);

            /**
             *  Print fuzzy sets array (DEBUG)
             */
            void printFuzzySets();
        };

        /**
         *  Fuzzy system rule base of all possible input combinations and decisions to make
         */
        class RuleBase {
            std::pair<outputAngle, outputSpeed> rules[FUZZY_SETS][FUZZY_SETS][FUZZY_SETS];
        public:
            /**
             *  Constructor
             *  Initialize rules array
             */
            RuleBase();

            /**
             *  Return decision corresponding to certain input
             *  @param front
             *  @param left
             *  @param right
             */
            std::pair<outputAngle, outputSpeed> giveOutputSets(inputValue, inputValue, inputValue);
        };

        /**
         *  Inner class which determines which decision to make based on the rule base
         */
        class InferenceEngine {
        public:
            /**
             *  Constructor
             */
            InferenceEngine();

            /**
             *  Return list of all output fuzzy sets and their value
             *  @param fuzzySets    Reference to matrix of fuzzy sets
             *  @param rulebase     Reference to rule base object
             *  @return vector of pairs of outpuy pair and its fuzzy value
             */
            std::vector< std::pair< std::pair<outputAngle, outputSpeed>, float> > processInput(const DataMatrix<float> &, RuleBase &);
        };

        /**
         *  Inner class which transforms fuzzy output decision to final value
         */
        class Defuzzifier {
            static const short ANGLE_SETS = 7;
            static const short SPEED_SETS = 5;
            float angleSetsValues[ANGLE_SETS];
            float speedSetsValues[SPEED_SETS];
        public:
            /**
             *  Constructor
             *  @param maxAngle 
             *  @param maxSpeed 
             */
            Defuzzifier(float, float);

            /**
             *  Defuzzify list output values
             *  @param outputList
             *  @see InferenceEngine::processInput
             *  @return pair of correct angle and speed for the ship
             */
            std::pair<float, float> defuzzify(std::vector< std::pair< std::pair<outputAngle, outputSpeed>, float> > &);
        };

        Settings        &settings;
        Fuzzifier       fuzzifier;
        RuleBase        ruleBase;
        InferenceEngine inferenceEngine;
        Defuzzifier     defuzzifier;
        float angle;        // output angle value
        float speed;        // Output speed value
    public:
        /**
         *  Constructor
         *  @param settings Reference to global settings
         */
        FuzzyControlSystem(Settings &);

        /**
         *  Destructor
         */
        ~FuzzyControlSystem();

        /**
         *  Getters of final output
         */
        float getAngle() const { return angle; }
        float getSpeed() const { return speed; }

        /**
         *  Run the whole process
         *  @param front    Depth values in front of the ship
         *  @param left     Depth values on the left of the ship
         *  @param right    Depth values on the right of the ship
         *  @return true on success, false otherwise. Output values available through getters.
         */
        bool run(std::vector<float>, std::vector<float>, std::vector<float>, float, float);
    };

}