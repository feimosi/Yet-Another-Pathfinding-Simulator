#include "stdafx.h"
#include "Simulator.h"

using namespace yaps;

Simulator::Simulator(Settings &settingsRef) : riverBottom(settingsRef.MAP_HEIGHT, settingsRef.MAP_WIDTH), dataBuffer(settingsRef.MAP_HEIGHT, settingsRef.MAP_WIDTH),
        inputCollector(riverBottom, settingsRef), approximationEngine(riverBottom), fuzzyControlSystem(settingsRef), settings(settingsRef) {
    boatPosition.set(settingsRef.MAP_WIDTH / 2, settings.BOAT_LENGTH);
}

Simulator::~Simulator() { }

bool Simulator::initialize(std::string filePath) {
    // If opening file fails
    if (!inputCollector.openFile(filePath))
        return false;
    // On simulator initialization, load data, approximate it and copy to main matrix
    inputCollector.loadData();
    approximationEngine.approximate();
    //riverBottom.copy(dataBuffer);
    //// Then load new data, approximate it and keep in the buffer
    //inputCollector.loadData();
    //approximationEngine.approximate();
    return true;
}

void Simulator::run() {
    // check if we should load new data
    ////
    //updateAdjecentPoints();
    //fuzzyControlSystem.run(frontPoints, leftPoints, rightPoints);
    //moveBoat(fuzzyControlSystem.getAngle(), fuzzyControlSystem.getSpeed());
#ifdef VERBOSE_DEBUG
    printCurrentData();
#endif
}

void Simulator::moveBoat(float angle, float speed) {
    boatAngle += angle;
    boatSpeed = speed;
}

void Simulator::updateAdjecentPoints() {
    std::function<int(float)> round = [](float x) -> int { return static_cast<int>(floor(x + 0.5f)); };
    VECTOR2 boat((float)boatPosition.x, (float)boatPosition.y);
    VECTOR2 front, left, right;
    int halfWidth = settings.BOAT_WIDTH / 2;
    int length = settings.BOAT_LENGTH;
    for (float i = (float)settings.PROXIMITY; i >= 0; i++) {
        front = VECTOR2(0, 2 * i);
        for (int i = -halfWidth; i <= halfWidth; i++) {
            front += VECTOR2((float)i, 0);
            // Rotate by the given angle
            // Positive angle rotates vector counterclockwise so we negate it to keep rule: positive angle rotates the boat to the right
            front %= -boatAngle;           
            // Move to the position relative to boat
            front += boat;
            // Push values at this coordinates to front points vector
            frontPoints.push_back(riverBottom[round(front.y)][round(front.x)]);
        }
        left = VECTOR2(-halfWidth - 1, 0);
        right = VECTOR2(halfWidth + 1, 0);
        for (int i = length; i >= 0; i--) {
            left += VECTOR2(0, -i);
            right += VECTOR2(0, -i);
            left %= -boatAngle;
            right %= -boatAngle;
            leftPoints.push_back(riverBottom[round(left.y)][round(left.x)]);
            rightPoints.push_back(riverBottom[round(right.y)][round(right.x)]);
        }
    }
}

void Simulator::printCurrentData() {
    std::cout << "River Bottom Data: \n";
    for (int i = 0; i < riverBottom.getHeight(); i++) {
        for (int j = 0; j < riverBottom.getWidth(); j++)
            std::cout << std::fixed << std::setprecision(2) << riverBottom[i][j] << "\t";
        std::cout << '\n';
    }
}
