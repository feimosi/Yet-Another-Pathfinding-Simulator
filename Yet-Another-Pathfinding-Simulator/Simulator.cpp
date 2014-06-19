#include "stdafx.h"
#include "Simulator.h"

using namespace yaps;

Simulator::Simulator(Settings &settingsRef) : riverBottom(settingsRef.MAP_HEIGHT, settingsRef.MAP_WIDTH), dataBuffer(settingsRef.MAP_HEIGHT, settingsRef.MAP_WIDTH),
        inputCollector(dataBuffer, settingsRef), approximationEngine(dataBuffer, settingsRef), fuzzyControlSystem(settingsRef), 
        settings(settingsRef), graph(riverBottom), refToGraphPath(graph.getPath()) {}

Simulator::~Simulator() { }

bool Simulator::initialize(std::string filePath) {
    // If opening file fails
    if (!inputCollector.openFile(filePath))
        return false;
    // On simulator initialization, load data and approximate it
    inputCollector.loadData();
    approximationEngine.approximate();
    boatPosition.set(settings.MAP_WIDTH / 2, settings.BOAT_LENGTH);
    // Next copy it to the buffer
    riverBottom.copy(dataBuffer);
    settings.setMaxDepth(settings.getMaxBufferDepth());
    //Find the path using A*
    graph.findPath(boatPosition);
    graphPathIndex = 0;
    refToGraphPath = graph.getPath();
    // Then load new data, approximate it and keep in the buffer
    inputCollector.loadData();
    approximationEngine.approximate();
    return true;
}

Coordinates Simulator::nextGraphPoint() {
    if (refToGraphPath[graphPathIndex].y < (int)settings.MAP_HEIGHT && graphPathIndex + settings.STEP < refToGraphPath.size()) {
        return refToGraphPath[ graphPathIndex = (graphPathIndex + settings.STEP) ];
    } else return refToGraphPath[refToGraphPath.size() - 1];
}

bool Simulator::run() {
    // Check if we come to the end of data matrix
    if (boatPosition.y >= (int)settings.MAP_HEIGHT) {
        // If there is no more data to process, return with false
        if (dataBuffer.getHeight() == 0) {
        #ifdef DEBUG
            std::cout << "FINISHED!\n";
        #endif
            return false;
        }
        // Copy data from buffer
        riverBottom.copy(dataBuffer);
        settings.setMaxDepth(settings.getMaxBufferDepth());
        // Load and prepare next data
        inputCollector.loadData();
        approximationEngine.approximate();
        settings.setImageHeight(settings.getimageHeight() - settings.MAP_HEIGHT);
        // Update boat position
        boatPosition.set(boatPosition.x, settings.BOAT_LENGTH);
        // Update graph path
        graph.findPath(boatPosition);
        graphPathIndex = 0;
        return true;
    }
    sf::Clock clock;
    updateAdjecentPoints();
    fuzzyControlSystem.run(frontPoints, leftPoints, rightPoints, minValue, maxValue);
    moveBoat(fuzzyControlSystem.getAngle(), fuzzyControlSystem.getSpeed());

#ifdef DEBUG
    std::cout << "---------------------------\n" << "Simulator\n\n"
        << "Boat Position: [" << boatPosition.x << "][" << boatPosition.y << "]\n"
        << "Current boat angle: " << boatAngle << '\n'
        << "Current boat speed: " << boatSpeed << '\n'
        << "Simulation time: " << clock.getElapsedTime().asSeconds()
        << " s\n---------------------------\n";
#endif
#ifdef VERBOSE_DEBUG
    printCurrentData();
#endif

    return true;
}

void Simulator::moveBoat(float angle, float speed) {
    boatAngle += angle;
    boatAngle = boatAngle > settings.MAX_ANGLE ? settings.MAX_ANGLE : boatAngle < -settings.MAX_ANGLE ? -settings.MAX_ANGLE : boatAngle;
    boatSpeed += speed * 0.25f;
    boatSpeed = speed > settings.MAX_SPEED ? settings.MAX_SPEED : speed <= settings.MAX_SPEED * 0.1f ? settings.MAX_SPEED * 0.1f : speed;
    VECTOR2 boat((float)boatPosition.x, (float)boatPosition.y);
    VECTOR2 relative(0.f, (float)settings.STEP);
    if (abs(refToGraphPath[graphPathIndex].x - boatPosition.x) > settings.MAP_WIDTH * 0.1f) {
        if (refToGraphPath[graphPathIndex].x - boatPosition.x < 0) {
            boatAngle += -settings.MAX_ANGLE * 0.25f;
        } else 
            boatAngle += settings.MAX_ANGLE * 0.25f;
    }
    relative %= -boatAngle;
    relative += boat;
    boatPosition.x = round(relative.x);
    boatPosition.y = round(relative.y);
}

void Simulator::updateAdjecentPoints() {
    VECTOR2 boat((float)boatPosition.x, (float)boatPosition.y);
    VECTOR2 front, left, right;
    int halfWidth = settings.BOAT_WIDTH / 2;
    int length = settings.BOAT_LENGTH;

    frontPoints.clear();
    leftPoints.clear();
    rightPoints.clear();

    // Initialize min and max values, which will be updated in addPointToVector method
    maxValue = FLT_MIN;
    minValue = FLT_MAX;

    for (int j = settings.PROXIMITY; j > 0; j--) {
        // Iterate along the width of the boat
        for (int i = -halfWidth; i <= halfWidth; i++) {
            front = VECTOR2((float)i, (float)j);
            // Rotate by the given angle
            // Positive angle rotates vector counterclockwise so we negate it to keep rule:
            // positive angle rotates the boat to the right
            front %= -boatAngle;
            // Move to the position relative to boat
            front += boat;
            // Push value at this coordinates to front points vector
            addPointToVector(frontPoints, round(front.x), round(front.y));
        }
        // Iterate along the length
        for (int i = length - 1; i >= 0; i--) {
            left = VECTOR2((float)(-halfWidth - j), (float)(i));
            right = VECTOR2((float)(halfWidth + j), (float)(i));
            left %= -boatAngle;
            right %= -boatAngle;
            left += boat;
            right += boat;
            addPointToVector(leftPoints, round(left.x), round(left.y));
            addPointToVector(rightPoints, round(right.x), round(right.y));
        }
    }
}

void Simulator::printCurrentData() {
    std::cout << "River Bottom Data: \n";
    for (int yi = riverBottom.getHeight() - 1; yi >= 0; yi--) {
        for (int xi = riverBottom.getWidth() - 1; xi >= 0; xi--) {
            if (yi == (int)boatPosition.y && xi == (int)boatPosition.x)
                std::cout << 'X' << "\t";
            else
                std::cout << std::fixed << std::setprecision(2) << riverBottom[yi][xi] << "\t";
        }
        std::cout << '\n';
    }
}

void Simulator::reset() {
    initialize(inputCollector.getPath());
}
