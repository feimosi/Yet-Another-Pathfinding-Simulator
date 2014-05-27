#include "stdafx.h"
#include "ApproximationEngine.h"

using namespace yaps;

void ApproximationEngine::prepareData() {
    RADIUS = data.getWidth() >> 2;
#ifdef DEBUG
    std::cout << "---------------------------\n" << "ApproximationEngine\n\n" 
        << "Data matrix height: " << data.getHeight() << '\n'
        << "Data matrix width: " << data.getWidth() << '\n'
        << "Radius: " << RADIUS << '\n';
#endif
    /////// DEPRECATED To remove
    for (int yi = data.getHeight() - 1; yi >= 0; yi--) {
        for (int xi = data.getWidth() - 1; xi >= 0; xi--) {
            if (data[yi][xi] != NULL) {
                paramX.push_back(xi);
                paramY.push_back(yi);
                valueF.push_back(data[yi][xi]);
            }
        }
    }
    ///////
}

float ApproximationEngine::interpolate(const Coordinates &point) {
    int x = point.x;
    int y = point.y;
    float dividend, divisor;    // Final equation components
    float f, w;                 // Temp for function value and weighting for every point
    dividend = divisor = 0;     
    int width = data.getWidth();
    int height = data.getHeight();
    
    // paramX, paramY, valueF have the same size

    for (int yi = (y - RADIUS < 0 ? 0 : y - RADIUS); yi <= y + RADIUS; yi++) {
        int xi = (x - RADIUS < 0 ? 0 : x - RADIUS);
        for (; xi <= x + RADIUS; xi++) {
            if ( yi >= height || xi >= width || !(f = data[yi][xi]) )
                continue;
            w = calculateWeighting(Coordinates(xi, yi), Coordinates(x, y));
            dividend += w * f;
            divisor += w;
        }
    }

    return divisor != 0 ? dividend / divisor : data[x][y];
}

ApproximationEngine::ApproximationEngine(DataMatrix<float> &dataRef) : data(dataRef) { }

ApproximationEngine::~ApproximationEngine() { }

DataMatrix<float> &ApproximationEngine::approximate() {
    prepareData();
    Coordinates point;
    sf::Clock clock;
    for (int yi = data.getHeight() - 1; yi >= 0; yi--) {
        for (int xi = data.getWidth() - 1; xi >= 0; xi--) {
            if (data[yi][xi] == NULL)
                data[yi][xi] = interpolate(point.set(xi, yi));
        }
    }
#ifdef DEBUG
    std::cout << "Approximation time: " << clock.getElapsedTime().asSeconds() 
        << " s\n---------------------------\n";
#endif
    return data;
}

/////// DEPRECATED To remove
float ApproximationEngine::old_interpolate(const Coordinates &point) {
    int x = point.x;
    int y = point.y;
    float dividend, divisor;    // Final equation components
    float f, w;                 // Temp for function value and weighting for every point
    unsigned px, py;            // Temp for every point coordinates
    dividend = divisor = 0;
    int width = data.getWidth();
    int height = data.getHeight();
    // Initialise vector iterators
    auto itX = paramX.cbegin(),
        itY = paramY.cbegin();
    auto itF = valueF.cbegin();

    // paramX, paramY, valueF have the same size
    while (itF != valueF.cend()) {
        px = *itX;
        py = *itY;
        f = *itF;
        itX++, itY++, itF++;

        w = 1 / pow((distanceBetween(Coordinates(px, py), Coordinates(x, y))), POWER_PARAMETER);
        dividend += w * f;
        divisor += w;
    }

    return divisor != 0 ? dividend / divisor : data[x][y];
}
///////