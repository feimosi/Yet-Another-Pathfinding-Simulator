#include "stdafx.h"
#include "GUIView.h"

using namespace yaps;

GUIView::GUIView(int width, int distance, std::string dataSource) : simulator(width, distance) {
    simulator.initialise(dataSource);
}

GUIView::~GUIView() { }

sf::Uint8 *GUIView::generateMapImage(const DataMatrix<float> &data, sf::Uint8 *pixels) {
    int dataWidth = data.getWidth();
    int dataHeight = data.getHeight();
    int x, y, index;    // Downscaled x, y coordinates
    float cPix;         // Current pixel value according to data
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            y = int(((float)i / MAP_HEIGHT) * dataWidth);
            x = int(((float)j / MAP_WIDTH) * dataHeight);
            index = (j + MAP_HEIGHT * i) * 4;
            cPix = data[y][x];
            pixels[index] = castColor(cPix, RED);       // Red channel
            pixels[index + 1] = castColor(cPix, GREEN); // Green channel
            pixels[index + 2] = castColor(cPix, BLUE);  // Blue channel
            pixels[index + 3] = 255;                    // Alpha channel
        }
    }
    return pixels;
}

sf::Uint8 GUIView::castColor(float value, int rgba) {
    sf::Uint8 c;
    switch (rgba) {
    case 0:
        c = 0; break;
    case 1:
        c = unsigned char(255 - (value / MAX_DEPTH) * 255); break;
    case 2:
        c = 255; break;
    default:
        c = 0; break;
    }
    return c;
}

void GUIView::run() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Yet Another Pathfinding Simulator", 
        sf::Style::Titlebar | sf::Style::Close);
    sf::Event event;
    sf::Image map;
    sf::Texture mapTexture;
    sf::Texture boatTexture;
    sf::Sprite mapSprite;
    sf::Sprite boatSprite;
    sf::Uint8 pixels[MAP_HEIGHT * MAP_WIDTH * 4];

    window.setFramerateLimit(60);  
    simulator.run();

    map.create(MAP_WIDTH, MAP_HEIGHT, generateMapImage(simulator.getRiverBottom(), pixels));
    mapTexture.loadFromImage(map);
    mapSprite.setTexture(mapTexture);
    mapSprite.setPosition(WINDOW_WIDTH / 2 - MAP_WIDTH / 2, WINDOW_HEIGHT / 2 - MAP_HEIGHT / 2);
    
    
    boatTexture.loadFromFile("wood.jpg");
    boatSprite.setTextureRect(sf::IntRect(0, 0, 30, 60));
    boatSprite.setTexture(boatTexture);
    sf::Vector2f boatPosition(mapSprite.getPosition() + sf::Vector2f(MAP_WIDTH / 2 - boatSprite.getGlobalBounds().width / 2, MAP_HEIGHT - boatSprite.getGlobalBounds().height));
    boatSprite.setPosition(boatPosition);

    // Main application loop
    while (window.isOpen()) {
        
        // Event processing
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        /*
            Run simulator to update boat position.
            Then get that value to render it.
            simulator.run();
            simulator.getBoatPosition();
            if needed simulator.getRiverBottom() -> generateMapImage() -> draw
        */

        // Rendering
        window.clear();
        window.draw(mapSprite);
        boatSprite.move(0, -0.4f);
        boatSprite.rotate(0.4f);
        window.draw(boatSprite);
        window.display();
    }
}