#include "stdafx.h"
#include "GUIView.h"
#include <sstream>

using namespace yaps;

GUIView::GUIView(int width, int distance, std::string dataSource)
        : settings(width, distance, 5, 5, 40, 60, 4, 4, width / 8 > 10 ? width / 8 : 6), simulator(settings) {
    simulator.initialize(dataSource);
}

GUIView::~GUIView() { }

sf::Uint8 *GUIView::generateMapImage(const DataMatrix<float> &data, sf::Uint8 *pixels) {
    int dataWidth = data.getWidth();
    int dataHeight = data.getHeight();
    int index;          // Current pixel index
    int displacement = 0;   // For shifting image data and maintaining continuity of displayed data segments
    float cPix;         // Current pixel value according to data
    if (settings.getimageHeight() > 0 && settings.getimageHeight() < settings.MAP_HEIGHT)
    {
        displacement = dataWidth * 4 * (settings.MAP_HEIGHT - settings.getimageHeight() + 1);
    }
    for (int i = dataHeight -1; i > 0 ; i--) {
        for (int j = 0; j < dataWidth; j++) {
            cPix = data[dataHeight - i - 1][j];
            index = (dataWidth * i + j) * 4 + displacement;
            auto temp = castColor(cPix);
            pixels[index] = std::get<0>(temp);      // Red channel
            pixels[index + 1] = std::get<1>(temp);  // Green channel
            pixels[index + 2] = std::get<2>(temp);  // Blue channel
            pixels[index + 3] = 255;                // Alpha channel
        }
    }
    return pixels;
}

std::tuple<sf::Uint8, sf::Uint8, sf::Uint8> GUIView::castColor(float value) {
    std::tuple<sf::Uint8, sf::Uint8, sf::Uint8> temp;
    if (value == 0){
        temp = std::make_tuple(255, 255, 255);
        return temp;
    }
    double minimum = 0;
    double maximum = settings.getMaxDepth();
    double halfmax = (minimum + maximum) / 2;
    int r = (int)(std::max(0.0, 255 * (1 - value / halfmax)));
    int b = (int)(std::max(0.0, 255 * (value / halfmax - 1)));
    int g = 255 - b - r;
    temp = std::make_tuple(r, g, b);
    return temp;
}

void GUIView::run() {
    // Initialise GUI variables
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Yet Another Pathfinding Simulator",
        sf::Style::Titlebar | sf::Style::Close);
    sf::Event event;
    sf::Image map;
    sf::Texture mapTexture;
    sf::Texture boatTexture;
    sf::Sprite mapSprite;
    sf::Sprite boatSprite;
    sf::Uint8 *pixels = new sf::Uint8[settings.MAP_HEIGHT * settings.MAP_WIDTH * 4];
    sf::Uint8 *blackPixels = new sf::Uint8[16]{
        0, 0, 0, 255,
        0, 0, 0, 255,
        0, 0, 0, 255,
        0, 0, 0, 255
    };

    sf::Uint8 *graphPixels = new sf::Uint8[16]{
        255, 0, 0, 255,
        255, 0, 0, 255,
        255, 0, 0, 255,
        255, 0, 0, 255
    };
    window.setFramerateLimit(60);

    scale = std::min(((float)WINDOW_HEIGHT / (float)settings.MAP_HEIGHT), (float)WINDOW_WIDTH / (float)settings.MAP_WIDTH);
    map.create(settings.MAP_WIDTH, settings.MAP_HEIGHT, generateMapImage(simulator.getRiverBottom(), pixels));
    map.saveToFile("map.jpg");
    mapTexture.loadFromImage(map);
    mapSprite.setTexture(mapTexture);
    mapSprite.scale(scale, scale);
    mapSprite.setPosition((float) WINDOW_WIDTH / 2 - (scale * (float) settings.MAP_WIDTH)/ 2,
                          (float) WINDOW_HEIGHT / 2 - (scale * (float) settings.MAP_HEIGHT)/ 2);

    const Coordinates &boatPosition = simulator.getBoatPositoin();
    Coordinates prevBoatPosition = boatPosition;
    sf::Vector2f mapPos(mapSprite.getPosition() + sf::Vector2f(0, settings.MAP_HEIGHT * scale - boatSprite.getGlobalBounds().height));
    sf::Clock clock;

    boatTexture.loadFromFile("wood.jpg");
    boatSprite.setTextureRect(sf::IntRect(0, 0, int(settings.BOAT_WIDTH * scale), int(settings.BOAT_LENGTH * scale)));
    boatSprite.setTexture(boatTexture);
    boatSprite.setPosition(converBoatCoordinates(mapSprite.getPosition(), sf::Vector2f((float)boatPosition.x, (float)boatPosition.y)));

    std::ostringstream oss;
    sf::Font droidSans;
    droidSans.loadFromFile("DroidSans.ttf");
    sf::Text angleText(" Angle: ", droidSans);
    sf::Text speedText(" Speed: ", droidSans);
    angleText.setCharacterSize(30);
    speedText.setCharacterSize(30);
    angleText.setPosition(10, 10);
    speedText.setPosition(10, 80);

    bool stop = false;
    bool pause = false;


    std::vector<Coordinates> path; //For displaying the path
    simulator.graph.getPath(path);
    int index  = 0;

    // Main application loop
    while (window.isOpen()) {

        // Event processing
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Space)
                    pause = !pause;
            }

            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::R)
                {
                    stop = false;
                    simulator.reset();
                    map.create(settings.MAP_WIDTH, settings.MAP_HEIGHT, generateMapImage(simulator.getRiverBottom(), pixels));
                    mapTexture.loadFromImage(map);

                }

            }
        }

        if (boatPosition.y >= settings.getimageHeight()) stop = true;

        if (clock.getElapsedTime().asMilliseconds() > 100 && !pause && !stop &&
            simulator.run()) {
                if (boatPosition.y <= settings.BOAT_LENGTH) {
                pixels = new sf::Uint8[settings.MAP_HEIGHT * settings.MAP_WIDTH * 4] {0};
                map.create(settings.MAP_WIDTH, settings.MAP_HEIGHT, generateMapImage(simulator.getRiverBottom(), pixels));
                map.saveToFile("map.jpg");
                mapTexture.loadFromImage(map);
                mapSprite.setTexture(mapTexture);

                simulator.graph.getPath(path); //Loading path for new data segment
            }
            if (prevBoatPosition.y < settings.MAP_HEIGHT) {
                mapTexture.update(blackPixels, 2, 2, prevBoatPosition.x, settings.MAP_HEIGHT - prevBoatPosition.y);
                mapSprite.setTexture(mapTexture);
                mapTexture.update(graphPixels, 2, 2, path.at(index).x, settings.MAP_HEIGHT - path.at(index).y); //Graph path
                if (index + settings.STEP + 1 < path.size()) index += settings.STEP + 1; //Graph path
            }

            boatSprite.setPosition(converBoatCoordinates(mapSprite.getPosition(), sf::Vector2f((float)boatPosition.x, (float)boatPosition.y)));
            boatSprite.setRotation(simulator.getBoatAngle());
            prevBoatPosition = boatPosition;

            oss.str("");
            oss << " Angle: " << std::fixed << std::setprecision(2) << simulator.getBoatAngle();
            angleText.setString(oss.str());
            oss.str("");
            oss << " Speed: " << std::fixed << std::setprecision(2) << simulator.getBoatSpeed();
            speedText.setString(oss.str());
            clock.restart();
        }

        // Rendering
        window.clear();
        window.draw(mapSprite);
        window.draw(boatSprite);
        window.draw(speedText);
        window.draw(angleText);
        window.display();
    }
}

sf::Vector2f GUIView::converBoatCoordinates(const sf::Vector2f &map, const sf::Vector2f &boatPosition) {
    return map + sf::Vector2f(0.f, settings.MAP_HEIGHT * scale) + (sf::Vector2f(boatPosition.x, -boatPosition.y) - sf::Vector2f(settings.BOAT_WIDTH / 2.f, 0.f)) * scale;
}
