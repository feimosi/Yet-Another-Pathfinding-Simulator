#include "stdafx.h"
#include "ApproximationEngine.h"

using namespace yaps;

float ApproximationEngine::interpolate(const Coordinates &point) {
    int x = point.x;
    int y = point.y;
    float dividend, divisor;    // Final equation components
    float f, w;                 // Temp for function value and weighting for every point
    dividend = divisor = 0;     
    int width = data.getWidth();
    int height = data.getHeight();

    for (int yi = (y - RADIUS < 0 ? 0 : y - RADIUS); yi <= y + RADIUS; yi++) {
        for (int xi = (x - RADIUS < 0 ? 0 : x - RADIUS); xi <= x + RADIUS; xi++) {
            if ( yi >= height || xi >= width || !(f = data[yi][xi]) )
                continue;
            w = calculateWeighting(Coordinates(xi, yi), Coordinates(x, y));
            dividend += w * f;
            divisor += w;
        }
    }
    return divisor != 0 ? dividend / divisor : data[y][x];
}

ApproximationEngine::ApproximationEngine(DataMatrix<float> &dataRef) : data(dataRef) { }

ApproximationEngine::~ApproximationEngine() { }

DataMatrix<float> &ApproximationEngine::approximate() {
    Coordinates point;
    sf::Clock clock;
    RADIUS = data.getWidth() / 8 > 10 ? data.getWidth() / 8 : 10;
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
        << "Radius: " << RADIUS << '\n'
        << "Approximation time: " << clock.getElapsedTime().asSeconds()
        << " s\n---------------------------\n";
#endif
    return data;
}
