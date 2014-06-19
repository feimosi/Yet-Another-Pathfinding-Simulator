#pragma once

namespace yaps {

    /**
     *  Class which stores main program settings
     */
    class Settings {
        float maxDepth;
        float maxBufferDepth;
        unsigned imageHeight;       //For deciding the value of displacement for the last image data portion
    public:
        // Default values
        static const unsigned DEF_BOAT_WIDTH = 2,
                              DEF_BOAT_LENGTH = 2,
                              DEF_PROXIMITY = 2,   
                              DEF_STEP = 2,
                              DEF_RADIUS = 10,
                              DEF_MAX_ANGLE = 45,
                              DEF_MAX_SPEED = 60;
        // Settings values
        const unsigned MAP_WIDTH,
                       MAP_HEIGHT,
                       BOAT_WIDTH,
                       BOAT_LENGTH,
                       PROXIMITY,   // Number of fields distant from the boat to consider in fuzzy control system
                       STEP,        // Number to fields to step forward in every simulation cycle
                       RADIUS;      // Radius in which we probe the data.
        const float MAX_ANGLE,
                    MAX_SPEED;

        float getMaxDepth() { return maxDepth; }
        void setMaxDepth(float newMaxDepth) { maxDepth = newMaxDepth; }
        float getMaxBufferDepth() { return maxBufferDepth; }
        void setMaxBufferDepth(float newMaxDepth) { maxBufferDepth = newMaxDepth; }

        unsigned getimageHeight() { return imageHeight; }
        void setImageHeight(unsigned newimageHeight) { imageHeight = newimageHeight; }

        Settings(unsigned mapWidth, unsigned mapHeight, unsigned boatWidth = DEF_BOAT_WIDTH, unsigned boatLength = DEF_BOAT_LENGTH, 
            float maxAngle = DEF_MAX_ANGLE, float maxSpeed = DEF_MAX_SPEED, unsigned proximity = DEF_PROXIMITY, unsigned step = DEF_STEP, 
            unsigned radius = DEF_RADIUS)
            : MAP_WIDTH(mapWidth), MAP_HEIGHT(mapHeight), BOAT_WIDTH(boatWidth), BOAT_LENGTH(boatLength), MAX_ANGLE(maxAngle),
            MAX_SPEED(maxSpeed), PROXIMITY(proximity), STEP(step), RADIUS(radius) { }

        ~Settings() { }

    };

}
