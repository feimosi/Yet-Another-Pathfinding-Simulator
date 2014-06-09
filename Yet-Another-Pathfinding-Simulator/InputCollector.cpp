#include "stdafx.h"
#include "MapParse.h"
#include "InputCollector.h"

using namespace yaps;

bool InputCollector::loadDataFromFile() {
    float maxValue = FLT_MIN;
    if (dataFile.is_open() && !dataFile.eof()) {
        int i = 0, j = 0;
        for (i = 0; i < riverBottom.RESERVED_HEIGHT; i++)
            for (j = 0; j < riverBottom.RESERVED_WIDTH; j++)
                if (!dataFile.eof()) {
                    dataFile >> riverBottom[i][j];
                    maxValue = std::max(maxValue, riverBottom[i][j]);
                }
        riverBottom.setHeight(i);
        riverBottom.setWidth(j);
        settings.setMaxBufferDepth(maxValue);
    } else
        return false;
    return true;
}

bool InputCollector::loadDataFromImage() {
    MapParse parse(dataImage);
    float maxValue = FLT_MIN;
    int mapWidth = (int)(dataImage.getSize().x / scale);
    int mapHeight = std::min(settings.MAP_HEIGHT, (unsigned)(dataImage.getSize().y / scale) - currentHeight - 1);

    for (int i = mapHeight - 1; i >= 0;  currentHeight++, i--) {
        for (int j = mapWidth - 1; j >= 0; j--){
            riverBottom[i][j] = parse.avarageValue(currentHeight, j, scale);
            maxValue = std::max(maxValue, riverBottom[i][j]);
        }

    }

    riverBottom.setHeight(mapHeight);
    riverBottom.setWidth(mapWidth);
    settings.setMaxBufferDepth(maxValue);
    return mapHeight > 0 ? true : false;
}

InputCollector::InputCollector(DataMatrix<float> &riverBottomRef, Settings &settingsRef)
        : riverBottom(riverBottomRef), settings(settingsRef), errorCode(0) { }

InputCollector::~InputCollector() { }

bool InputCollector::openFile(std::string filePath) {
    path = filePath;

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
                scale = (float) dataImage.getSize().x / (float) riverBottom.RESERVED_WIDTH;
                settings.setimageHeight(dataImage.getSize().y/ scale);
                currentHeight = 1;
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


std::string InputCollector::getPath()
{
    return path;
}
