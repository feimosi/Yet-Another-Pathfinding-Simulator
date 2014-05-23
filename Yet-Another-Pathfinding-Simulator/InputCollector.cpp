#include "stdafx.h"
#include "InputCollector.h"

using namespace yaps;

bool InputCollector::loadDataFromFile() {
	if (dataFile.is_open() && !dataFile.eof()) {
		for (int i = 0; i < riverBottom.getHeight(); i++)
			for (int j = 0; j < riverBottom.getWidth(); j++)
				if (!dataFile.eof())
					dataFile >> riverBottom[i][j];
		dataFile.close();
	}
	else
		return false;
	return true;
}

bool InputCollector::loadDataFromImage() {
	// TODO
	return false;
}

InputCollector::InputCollector(DataMatrix<float> &riverBottomRef) : riverBottom(riverBottomRef), errorCode(0), parseImage(false) { }

InputCollector::~InputCollector() { }

bool InputCollector::openFile(std::string filePath) {
	std::smatch match;
	std::regex_match(filePath, match, std::regex("(.*?)([^\\\\\\/]+?)\\.(jpe?g|png|txt)$")); // Test file path for regex match

	// Check if regex match was successful
	if (match.ready()) {
		/* Regex groups:
			match[0] - entire match
			match[1] - path to the file (before / or \)
			match[2] - file name
			match[3] - file extension
		*/
		if (match[3] == "jpg" || match[3] == "png") {
			parseImage = true;
			return dataImage.loadFromFile(filePath) ? true : false;
		} else if (match[3] == "txt") {
			if (dataFile.is_open())
				dataFile.close();
			dataFile.open(filePath);
			return dataFile.is_open() ? true : false;
		}
	}

	return false;
}

bool InputCollector::loadData() {
	return parseImage ? loadDataFromImage() : loadDataFromFile();
}
