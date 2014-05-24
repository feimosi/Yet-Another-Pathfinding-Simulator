#include "stdafx.h"
#include "Simulator.h"

using namespace yaps;

Simulator::Simulator(int width, int distance) : riverBottom(width, distance), inputCollector(riverBottom),
	    approximationEngine(riverBottom) {
    boatPosition.x = width / 2;
}

Simulator::~Simulator() { }

bool Simulator::initialise(std::string filePath) {
	if (!inputCollector.openFile(filePath))
		return false;

	return true;
}

void Simulator::run() {
	inputCollector.loadData();
	approximationEngine.approximate();
#ifdef DEBUG
    printCurrentData();
#endif
}

void Simulator::printCurrentData() {
	std::cout << "River Bottom Data: \n";
	for (int i = 0; i < riverBottom.getHeight(); i++) {
		for (int j = 0; j < riverBottom.getHeight(); j++)
			std::cout << std::fixed << std::setprecision(2) << riverBottom[i][j] << "\t";
		std::cout << std::endl;
	}
}