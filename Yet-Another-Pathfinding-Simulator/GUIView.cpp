#include "stdafx.h"
#include "GUIView.h"

using namespace yaps;

GUIView::GUIView(int width, int distance, std::string dataSource) : simulator(width, distance) {
    simulator.initialise(dataSource);
}

GUIView::~GUIView() { }

sf::Uint8 *GUIView::generateMapImage(const DataMatrix<float> &data, sf::Uint8 *pixels)
{
    int dataWidth = data.getWidth();
    int dataHeight = data.getHeight();
    int index;
    float cPix;         // Current pixel value according to data
    for (int i = 0; i < dataHeight; i++)
    {
        for (int j = 0; j < dataWidth; j++)
        {
            index = (i + dataHeight * j) * 4;
            cPix = data[i][j];
            auto temp = castColor(cPix);
            pixels[index] = std::get<0>(temp);
            pixels[index + 1] = std::get<1>(temp); // Green channel
            pixels[index + 2] = std::get<2>(temp);  // Blue channel
            pixels[index + 3] = 255;                    // Alpha channel
        }
    }
    return pixels;
}

std::tuple<sf::Uint8, sf::Uint8, sf::Uint8> GUIView::castColor(float value)
{
    std::tuple<sf::Uint8, sf::Uint8, sf::Uint8> temp;
    if (value == 0){
        temp = std::make_tuple(0, 0, 0);
        return temp;
    }
    double minimum = 0;
    double maximum = simulator.getRiverBottom().getMax();
    double halfmax = (minimum + maximum) / 2;
    int b = (int) (std::max(0.0, 255*(1 - value/halfmax)));
    int r = (int) (std::max(0.0, 255*(value/halfmax - 1)));
    int g = 255 - b - r;
    temp = std::make_tuple(r, g, b);
    return temp;
}

void GUIView::run() {
    int MAP_HEIGHT = simulator.getRiverBottom().getWidth();
    int MAP_WIDTH = simulator.getRiverBottom().getHeight();

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
    float scale = std::min(((float) WINDOW_HEIGHT / (float) MAP_HEIGHT), (float) WINDOW_WIDTH / (float) MAP_WIDTH);
    mapSprite.scale(scale, scale);

    mapSprite.setPosition((float) WINDOW_WIDTH / 2 - (scale * (float) MAP_WIDTH)/ 2,
                          (float) WINDOW_HEIGHT / 2 - (scale * (float) MAP_HEIGHT)/ 2);


    boatTexture.loadFromFile("wood.jpg");
    boatSprite.setTextureRect(sf::IntRect(0, 0, 30, 60));
    boatSprite.setTexture(boatTexture);
    sf::Vector2f boatPosition(mapSprite.getPosition() + sf::Vector2f(MAP_WIDTH * scale / 2 - boatSprite.getGlobalBounds().width / 2, MAP_HEIGHT * scale - boatSprite.getGlobalBounds().height));
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
