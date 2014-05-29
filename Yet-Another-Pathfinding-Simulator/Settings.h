#pragma once

namespace yaps {

    /**
     *  Class which stores main program settings
     */
    class Settings {
        float maxDepth;
    public:
        const unsigned MAP_WIDTH,
                       MAP_HEIGHT,
                       BOAT_WIDTH,
                       BOAT_LENGTH,
                       PROXIMITY,   // Number of fields distant from the boat to consider in fuzzy control system 
                       STEP;        // Number to fields to step forward in every simulation cycle
        const float MAX_ANGLE,
                    MAX_SPEED;
        float getMaxDepth() { return maxDepth; }
        void setMaxDepth(float newMaxDepth) { maxDepth = newMaxDepth; }

        Settings(unsigned mapWidth, unsigned mapHeight, unsigned boatWidth = 1, unsigned boatLength = 1, float maxAngle = 45.f, float maxSpeed = 60.f, unsigned proximity = 2, unsigned step = 2) 
            : MAP_WIDTH(mapWidth), MAP_HEIGHT(mapHeight), BOAT_WIDTH(boatWidth), BOAT_LENGTH(boatLength), MAX_ANGLE(maxAngle), MAX_SPEED(maxSpeed), PROXIMITY(proximity), STEP(step) { }
        
        ~Settings() { }

    };

}
