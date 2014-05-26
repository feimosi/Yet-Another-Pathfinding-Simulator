#include "MapParse.h"
#include <iostream>
#include <SFML\Graphics.hpp>

MapParse::MapParse(sf::Image imgz)
{
    MapParse::img = imgz;
}

MapParse::~MapParse()
{
}

float MapParse::avarageValue(int x, int y)
{
    float h, s, v, value, tempz;
    int counter = 0;
    sf::Color color;
    int scale = 4; // how many pixels represent 0,5m
    for (int i = x * scale; i > (x - 1) * scale; i--)
    {
        counter = 0;
        tempz = 0;
        for (int j = y * scale; j > (y - 1) * scale; j--)
        {
            color = img.getPixel(i, j);
            rgbtohsv(color.r, color.g, color.b, h, s, v);
            hsvtoint(h, s, v, value);
            if (value < 0 || value > 264) continue;
            counter++;
            tempz += (value/264) * 20;
        }

    }
    return tempz/counter;

}

void MapParse::hsvtoint(float h, float s, float v, float &value)
{
    h *= 360;
    if (h > 2) h += 24;
    v /= 255;
    v = 60 * v - 36;
    if (h <= 24) value = h + v;
    else if (h >= 239) value = h - v;
    else value = h;
}


void MapParse::rgbtohsv(int r, int g, int b,
                        float &h, float &s, float &v)
{
    float rgb_max = std::max(r, std::max(g, b));
    float rgb_min = std::min(r, std::min(g, b));
    float delta = rgb_max - rgb_min;
    s = delta / (rgb_max + 1e-20f);
    v = rgb_max;

    float hue;
    if (r == rgb_max)
        hue = (g - b) / (delta + 1e-20f);
    else if (g == rgb_max)
        hue = 2 + (b - r) / (delta + 1e-20f);
    else
        hue = 4 + (r - g) / (delta + 1e-20f);
    if (hue < 0)
        hue += 6.f;
    h = hue * (1.f / 6.f);

}
