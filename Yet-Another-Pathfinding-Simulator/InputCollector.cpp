#include "stdafx.h"
#include "InputCollector.h"

using namespace yaps;

InputCollector::InputCollector(DataMatrix<float> &riverBottomRef) : riverBottom(riverBottomRef), errorCode(0) { }

InputCollector::~InputCollector() {
	dataFile.close();
}

bool InputCollector::openFile(std::string filePath) {
	dataFile.open(filePath);
	return dataFile.is_open() ? true : false;
}

bool InputCollector::loadDataFromFile() {
	if (dataFile.is_open()) {
		for (int i = 0; i < riverBottom.getHeight(); i++)
			for (int j = 0; j < riverBottom.getWidth(); j++)
				if (!dataFile.eof())
					dataFile >> riverBottom[i][j];
		dataFile.close();
	} else 
		return false;
	return true;
}

bool InputCollector::openImage(std::string filePath) {
	return dataImage.loadFromFile(filePath) ? true : false;
}

bool InputCollector::loadDataFromImage() {
	// TODO
	return false;
}
