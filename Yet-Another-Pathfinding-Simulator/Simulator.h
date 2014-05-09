#pragma once
#include "DataMatrix.h"
#include "InputCollector.h"
#include "Fuzzifier.h"
#include "ApproximationEngine.h"
#include "RouteScheduler.h"

namespace yaps {

	/**
	 *  Main class responsible for handling data, calculations and routing of the boat
	 */
	class Simulator {
		InputCollector inputCollector;
		Fuzzifier fuzzifier;
		ApproximationEngine approximationEngine;
		RouteScheduler routeScheduler;
		std::string dataFilePath; // String with path to the data file for inputCollector
		DataMatrix<float> riverBottom; // Matrix, which contains depth of the river in certain points.
	public:
		/**
		 *	Constructor
		 *	@param width	Init value for riverBottom constructor
		 *	@param distance	Init value for riverBottom constructor
		 */
		Simulator(int, int);
		~Simulator();
		/**
		 *	Initialise all objects and prepare for simulation
		 *	@param filePath Init value for inputCollector
		 *	@return true on success, false in case of error
 		 */
		bool initialise(std::string);
		/**
		 *	Program main loop
		 */
		void run();
		/**
		 *	Print data to standard output (DEBUG)
		 */
		void printCurrentData();
	};

}
