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
                       BOAT_LENGTH;
        const float MAX_ANGLE,
                    MAX_SPEED;
        float getMaxDepth() { return maxDepth; }
        void setMaxDepth(float newMaxDepth) { maxDepth = newMaxDepth; }

        Settings(unsigned mapWidth, unsigned mapHeight, unsigned boatWidth = 1, unsigned boatLength = 1, float maxAngle = 45.f, float maxSpeed = 60.f) 
            : MAP_WIDTH(mapWidth), MAP_HEIGHT(mapHeight), BOAT_WIDTH(boatWidth), BOAT_LENGTH(boatLength), MAX_ANGLE(maxAngle), MAX_SPEED(maxSpeed) { }
        
        ~Settings() { }

    };

}
