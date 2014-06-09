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
        Settings &settings;             // Global settings
        InputCollector inputCollector;
        FuzzyControlSystem fuzzyControlSystem;
        ApproximationEngine approximationEngine;
        RouteScheduler routeScheduler;
        DataMatrix<float> riverBottom;  // Matrix, which contains depth of the river in certain points
        DataMatrix<float> dataBuffer;   // Buffer for next river bottom values
        std::string dataFilePath;       // String with path to the data file for inputCollector
        Coordinates boatPosition;       // Current boat position
        float boatAngle;                // Current boat angle (degrees)
        float boatSpeed;                // Current boat speed
        std::vector<float> leftPoints,  // Left adjecent points to the boat
                           frontPoints, // Front adjecent points to the boat
                           rightPoints; // Right adjecent points to the boat
        float maxValue, minValue;       // Currently (on every step) the min and max values

        /**
         *  Round passed float value
         *  @param x 
         *  @return rounded value
         */
        int round(float x) { return static_cast<int>(floor(x + 0.5f)); };
        
        /**
         *  Add point at given coordinates to the passed vector
         *  @param src  Reference to vector
         *  @param x    X coordinate
         *  @param y    Y coordinate
         *  @return true on success, false otherwise
         */
        bool addPointToVector(std::vector<float> &src, int x, int y) {
            if (x >= 0 && x < riverBottom.getWidth() && y >= 0 && y < riverBottom.getHeight()) {
                src.push_back(riverBottom[y][x]);
                maxValue = std::max(maxValue, riverBottom[y][x]);
                minValue = std::min(minValue, riverBottom[y][x]);
                return true;
            } else
                return false;
        }

        /**
         *  Move boat coordinates by given angle and one unit straight
         *  @param angle
         *  @param speed
         *  @return true on success, false otherwise
         */
        void moveBoat(float, float);

        /**
         *  Update vectors with points adjecent to the boat
         */
        void updateAdjecentPoints();

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
        const DataMatrix<float> &getRiverBottom() const { return riverBottom; }

        /**
         *  @return const reference to boat coordinates
         */
        const Coordinates &getBoatPositoin() const { return boatPosition; }

        /**
         *  Getters of boat properties
         */
        float getBoatAngle() const { return boatAngle; }
        float getBoatSpeed() const { return boatSpeed; }

        /**
         *  Initialise all objects and prepare for simulation
         *  @param filePath Init value for inputCollector
         *  @return true on success, false in case of error
         */
        bool initialize(std::string);
        
        /**
         *  Run simulation (get data if needed -> process it -> keep results in data members)
         */
        bool run();
        
        /**
         *  Print data to standard output (DEBUG)
         */
        void printCurrentData();
    };

}
