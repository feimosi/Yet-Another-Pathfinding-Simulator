#include "stdafx.h"
#include "Simulator.h"
#include "DataMatrix.h"

using namespace yaps;

Simulator::Simulator(int width, int distance) : riverBottom(width, distance), inputCollector(riverBottom) {

}

Simulator::~Simulator() {

}

bool Simulator::initialise(std::string filePath) {
	if (!inputCollector.openFile(filePath))
		return false;
	return true;
}

void Simulator::run() {
	inputCollector.loadDataFromFile();
}

void Simulator::printCurrentData() {
	std::cout << "River Bottom Data: \n";
	for (int i = 0; i < riverBottom.getHeight(); i++) {
		for (int j = 0; j < riverBottom.getHeight(); j++)
			std::cout << riverBottom[i][j] << " ";
		std::cout << std::endl;
	}
}