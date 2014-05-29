#pragma once

namespace yaps {

    /**
     *  Class which interpolates 2D data with a known scattered set of points.
     *  For now it uses Inverse distance weighting (IDW) algorithm, Modified Shepard's method.
     *  @link http://en.wikipedia.org/wiki/Inverse_distance_weighting
     */
    class ApproximationEngine {
        int RADIUS;                     // Radius in which we probe the data. For now it's 1/8 of the data width assigned in a constructor
        DataMatrix<float> &data;        // Reference to data matrix that should be interpolated (values 0 are considered missing)
        std::vector<unsigned> paramX;   // Vector of function x arguments
        std::vector<unsigned> paramY;   // Vector of function y arguments
        std::vector<float> valueF;      // Vector of function values in x, y
        
        /**
         *  Calculate weighting parameter from Shepard's method
         *  @param i, j first and second point coordinates
         *  @return value of weighting
         */
        float calculateWeighting(const Coordinates &i, const Coordinates &j) {
            float distance = distanceBetween(i, j);
            return pow( (RADIUS - distance) / (RADIUS * distance), 2 );
        }

        /**
         *  Calculate distance between two points
         *  @param i, j first and second point coordinates
         *  @return distance between two points
         */
        float distanceBetween(const Coordinates &i, const Coordinates &j) {
            return static_cast<float>(sqrt((i.x - j.x) * (i.x - j.x) + (i.y - j.y) * (i.y - j.y)));
        }

        /**
         *  Calculate interpolation value for a certain point
         *  @param point
         */
        float interpolate(const Coordinates &);
 
    public:
        /**
         *  Constructor
         *  @param dataRef Reference to data matrix, which shoud be approximated
         */
        ApproximationEngine(DataMatrix<float> &);
        
        /**
         *  Destructor
         */
        ~ApproximationEngine();
        
        /**
         *  Prepare data and run interpolation algorithm
         *  @return reference to data matrix (passed to the constructor) filled with approximated values
         */
        DataMatrix<float> &approximate();
    };

}