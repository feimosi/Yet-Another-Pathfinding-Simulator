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
        DataMatrix<float> dataBuffer;   // Buffer for next river bottom values
        Coordinates boatPosition;       // Current boat position
        float boatAngle;                // Current boat angle (degrees)
        float boatSpeed;                // Current boat speed
        Settings &settings;             // Global settings
        std::vector<float> leftPoints,  // Left adjecent points to the boat
                           frontPoints, // Front adjecent points to the boat
                           rightPoints; // Right adjecent points to the boat
    public:
        /**
         *  Constructor
         *  @param settings Reference to program global settings
         */
        Simulator(Settings &);

        /**
         *  Destructor
         */
        ~Simulator();

        /**
         *  @return const reference to river bottom matrix
         */
        const DataMatrix<float> &getRiverBottom() const {
            return riverBottom;
        }
        
        /**
         *  Initialise all objects and prepare for simulation
         *  @param filePath Init value for inputCollector
         *  @return true on success, false in case of error
         */
        bool initialize(std::string);
        
        /**
         *  Run simulation (get data if needed -> process it -> keep results in data members)
         */
        void run();

        /**
         *  Move boat coordinates by given angle and one unit straight
         *  @param angle
         *  @param speed
         */
        void moveBoat(float, float);

        /**
         *  Update vectors with points adjecent to the boat
         */
        void updateAdjecentPoints();
        
        /**
         *  Print data to standard output (DEBUG)
         */
        void printCurrentData();
    };

}
