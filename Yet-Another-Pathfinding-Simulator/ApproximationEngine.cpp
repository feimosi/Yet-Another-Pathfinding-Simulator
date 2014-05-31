#include "stdafx.h"
#include "ApproximationEngine.h"

using namespace yaps;

float ApproximationEngine::interpolate(const Coordinates &point) {
    int x = point.x;
    int y = point.y;
    int width = data.getWidth();
    int height = data.getHeight();
    int radius = settings.RADIUS;
    float dividend, divisor;    // Final equation components
    float f, w;                 // Temp for function value and weighting for every point
    dividend = divisor = 0;     

    for (int yi = (y - radius > 0 ? y - radius : 0); yi <= y + radius; yi++) {
        for (int xi = (x - radius > 0 ? x - radius : 0); xi <= x + radius; xi++) {
            if ( yi >= height || xi >= width || !(f = data[yi][xi]) )
                continue;
            w = calculateWeighting(Coordinates(xi, yi), Coordinates(x, y));
            dividend += w * f;
            divisor += w;
        }
    }

    return divisor != 0 ? dividend / divisor : data[y][x];
}

ApproximationEngine::ApproximationEngine(DataMatrix<float> &dataRef, Settings &settingsRef) : data(dataRef), settings(settingsRef) { }

ApproximationEngine::~ApproximationEngine() { }

DataMatrix<float> &ApproximationEngine::approximate() {
    Coordinates point;
    sf::Clock clock;
    // Iterate through every element in the matrix and interpolate NULL points
    for (int yi = data.getHeight() - 1; yi >= 0; yi--) {
        for (int xi = data.getWidth() - 1; xi >= 0; xi--) {
            if (data[yi][xi] == NULL)
                data[yi][xi] = interpolate(point.set(xi, yi));
        }
    }

#ifdef DEBUG
    std::cout << "---------------------------\n" << "ApproximationEngine\n\n"
        << "Data matrix height: " << data.getHeight() << '\n'
        << "Data matrix width: " << data.getWidth() << '\n'
        << "Radius: " << settings.RADIUS << '\n'
        << "Approximation time: " << clock.getElapsedTime().asSeconds()
        << " s\n---------------------------\n";
#endif

    return data;
}
