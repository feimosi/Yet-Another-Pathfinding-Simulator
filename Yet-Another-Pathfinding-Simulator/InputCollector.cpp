#include "stdafx.h"
#include "MapParse.h"
#include "InputCollector.h"

using namespace yaps;

bool InputCollector::loadDataFromFile() {
    float maxValue = FLT_MIN;
    if (dataFile.is_open() && !dataFile.eof()) {
        for (int i = 0; i < riverBottom.getHeight(); i++)
            for (int j = 0; j < riverBottom.getWidth(); j++)
                if (!dataFile.eof()) {
                    dataFile >> riverBottom[i][j];
                    maxValue = std::max(maxValue, riverBottom[i][j]);
                }
        settings.setMaxDepth(maxValue);
    } else
        return false;
    return true;
}

bool InputCollector::loadDataFromImage() {
    MapParse parse (dataImage);
    float maxValue = FLT_MIN;
    float depth;
    int mapWidth = (int)(dataImage.getSize().x / scale) - 1;
    int mapHeight = std::min(settings.MAP_HEIGHT, (unsigned)(dataImage.getSize().y / scale)) - 1;
    for (int i = settings.MAP_HEIGHT; mapHeight > 0 && i > 0; mapHeight--, i--) {
        for (int j = mapWidth; j > 0; j--){
            depth = parse.avarageValue(mapHeight, j, scale);
            riverBottom[mapHeight][j] = depth;
            maxValue = std::max(maxValue, riverBottom[mapHeight][j]);
        }
    }
    settings.setMaxDepth(maxValue);
    return true;
}

InputCollector::InputCollector(DataMatrix<float> &riverBottomRef, Settings &settingsRef) 
        : riverBottom(riverBottomRef), settings(settingsRef), errorCode(0) { }

InputCollector::~InputCollector() { }

bool InputCollector::openFile(std::string filePath) {
    std::smatch match;
    std::regex_match(filePath, match, std::regex("(.*?)([^\\\\\\/]+?)\\.(jpe?g|png|txt)$")); // Test file path for regex match

    // Check if regex match was successful
    if (match.ready()){
        /*
          Regex groups:
            match[0] - entire match
            match[1] - path to the file (before / or \)
            match[2] - file name
            match[3] - file extension
        */
        if (match[3] == "jpg" || match[3] == "png") {
            parseImage = true;
            if (dataImage.loadFromFile(filePath) == true){
                scale = (float) dataImage.getSize().x / (float) riverBottom.getWidth();
                return true;
            } else 
                return false;
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
