#pragma once
#include "ApproximationEngine.h"
#include "FuzzyControlSystem.h"
#include "InputCollector.h"
#include "RouteScheduler.h"

namespace yaps {

	/**
	 *  Main class responsible for handling data, calculations and routing of the boat
	 */
	class Simulator {
		InputCollector inputCollector;
		FuzzyControlSystem fuzzyControlSystem;
		ApproximationEngine approximationEngine;
		RouteScheduler routeScheduler;
		std::string dataFilePath;       // String with path to the data file for inputCollector
		DataMatrix<float> riverBottom;  // Matrix, which contains depth of the river in certain points
		Coordinates boatPosition;       // Current boat position
	public:
		/**
		 *	Constructor
		 *	@param width                Init value for riverBottom constructor
		 *	@param distance             Init value for riverBottom constructor
		 *	@param currentBoatPosition  Init value for boatPosition
		 */
		Simulator(int, int);

		/**
		 *	Destructor
		 */
		~Simulator();

        /**
         *	@return const pointer to riverBottom
         */
        const DataMatrix<float> &getRiverBottom() const {
            return riverBottom;
        }
		
		/**
		 *	Initialise all objects and prepare for simulation
		 *	@param filePath Init value for inputCollector
		 *	@return true on success, false in case of error
 		 */
		bool initialise(std::string);
		
		/**
		 *	Run simulation (get data -> process it -> output result)
		 */
		void run();
		
		/**
		 *	Print data to standard output (DEBUG)
		 */
		void printCurrentData();
	};

}
