#include "stdafx.h"
#include "InputCollector.h"
#include "MapParse.h"
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

bool InputCollector::loadDataFromImage()
{
    MapParse parse (dataImage);
    float temp;
    for (int i = 1; i < riverBottom.getHeight(); i++){
        for (int j = 1; j < riverBottom.getWidth(); j++){
            temp =parse.avarageValue(i, j);
            if (temp != temp)
            {
                riverBottom[i][j] = 0;
            }
            else
            {
                riverBottom[i][j] = temp;
                if (temp < riverBottom.getMin()) riverBottom.setMin(temp);
                if (temp > riverBottom.getMax()) riverBottom.setMax(temp);
            }
        }
    }
    return false;
}

InputCollector::InputCollector(DataMatrix<float> &riverBottomRef) : riverBottom(riverBottomRef), errorCode(0) { }

InputCollector::~InputCollector() { }

bool InputCollector::openFile(std::string filePath) {
    std::smatch match;
    std::regex_match(filePath, match, std::regex("(.*?)([^\\\\\\/]+?)\\.(jpe?g|png|txt)$")); // Test file path for regex match

    // Check if regex match was successful
    if (match.ready()) {
        /*
          Regex groups:
            match[0] - entire match
            match[1] - path to the file (before / or \)
            match[2] - file name
            match[3] - file extension
        */
        if (match[3] == "jpg" || match[3] == "png") {
            parseImage = true;
            return dataImage.loadFromFile(filePath) ? true : false;
        } else if (match[3] == "txt") {
            parseImage = false;
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
