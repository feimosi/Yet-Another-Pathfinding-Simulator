#include "stdafx.h"
#include "MapParse.h"

using namespace yaps;

MapParse::MapParse(sf::Image imgz)
{
    MapParse::img = imgz;
}

MapParse::~MapParse()
{
}

float MapParse::avarageValue(int x, int y, float scale)
{
    float r, g, b, h, s, v, value, tempz = 0;
    int counter = 0;
    sf::Color color;
    for (int j = y * scale; j > (y - 1) * scale; j --){
        for (int i = x * scale; i > (x - 1) * scale; i --){
            color = img.getPixel(j, i);
            r = (int) color.r;
            g = (int) color.g;
            b = (int) color.b;
            if (r + g + b < 153) continue;
            r = round(r);
            g = round(g);
            b = round(b);
            rgbtohsv(r, g, b, h, s, v);
            hsvtoint(h, s, v, value);
            if (value < 0 || value > 264) continue;
            counter++;
            tempz += (value/264) * 10;
        }

    }
    if (counter == 0 || tempz == 0) return 0;
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


int MapParse::round(int number){
    int values [6] = {0, 51, 102, 153, 204, 255};
    for (int i = 0; i < 5; i++){
        if (number < values[i] && number > values[i + 1]){
            int x = (values[i] + values[i + 1]) / 2;
            if (number > x) return values[i + 1];
            else return values[i];
        }
    }
    return number;
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
