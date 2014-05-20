#include "stdafx.h"
#include "ApproximationEngine.h"

using namespace yaps;

void ApproximationEngine::prepareData() {
	for (int i = data.getHeight() - 1; i >= 0; i--) {
		for (int j = data.getWidth() - 1; j >= 0; j--) {
			if (data[i][j] != NULL) {
				paramX.push_back(j);
				paramY.push_back(i);
				valueF.push_back(data[i][j]);
			}
		}
	}
}

float ApproximationEngine::calculateWeighting(unsigned xi, unsigned yi, unsigned xj, unsigned yj) {
	/* 
		w = 1 / d^p 
		where d - Euclidean distance between 2 points and p - power parameter
	*/
	return 1 / pow(static_cast<float>( sqrt((xi - xj) * (xi - xj) + (yi - yj) * (yi - yj)) ), POWER_PARAMETER);
}

float ApproximationEngine::interpolate(unsigned x, unsigned y) {
	float dividend, divisor;	
	float f, w;				// Temp for function value and weighting for every point
	unsigned px, py;		// Temp for every point coordinates
	dividend = divisor = 0;		

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

		w = calculateWeighting(px, py, x, y);
		dividend += w * f;
		divisor += w;
	}

	return divisor != 0 ? dividend / divisor : data[x][y];
}

ApproximationEngine::ApproximationEngine(DataMatrix<float> &dataRef) : data(dataRef) { }

ApproximationEngine::~ApproximationEngine() { }

DataMatrix<float> &ApproximationEngine::approximate() {
	prepareData();
	for (int i = data.getHeight() - 1; i >= 0; i--) {
		for (int j = data.getWidth() - 1; j >= 0; j--) {
			if (data[i][j] == NULL) {
				data[i][j] = interpolate(j, i);
			}
		}
	}
	return data;
}