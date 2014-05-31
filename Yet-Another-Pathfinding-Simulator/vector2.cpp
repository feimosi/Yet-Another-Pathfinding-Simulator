#include "stdafx.h"
#include "vector2.h"

using namespace yaps;

VECTOR2::VECTOR2(void) : x(0), y(0) { }

VECTOR2::VECTOR2(float x, float y) : x(x), y(y) { }

VECTOR2::VECTOR2(int x, int y) : x((float)x), y((float)y) { }

VECTOR2::VECTOR2(unsigned x, unsigned y) : x((float)x), y((float)y) { }

VECTOR2::~VECTOR2(void) { }

void VECTOR2::reassign(float x, float y)
{
    this->x = x;
    this->y = y;
}

void VECTOR2::reassign(VECTOR2 otr)
{
    reassign(otr.x, otr.y);
}

VECTOR2& VECTOR2::operator=(const VECTOR2 otr)
{
    this->x = otr.x;
    this->y = otr.y;
    return *this;
}

VECTOR2& VECTOR2::operator+=(const VECTOR2 otr)
{
    this->x += otr.x;
    this->y += otr.y;
    return *this;
}

VECTOR2& VECTOR2::operator-=(const VECTOR2 otr)
{
    this->x -= otr.x;
    this->y -= otr.y;
    return *this;
}

VECTOR2& VECTOR2::operator*=(float scl)
{
    this->x *= scl;
    this->y *= scl;
    return *this;
}

VECTOR2& VECTOR2::operator/=(float scl)
{
    this->x /= scl;
    this->y /= scl;
    return *this;
}

VECTOR2& VECTOR2::operator%=(float theta)
{
    float radians = theta * (PI / 180);

    float cs = std::cos(radians);
    float sn = std::sin(radians);

    float px = x * cs - y * sn; 
    float py = x * sn + y * cs;

    this->x = px;
    this->y = py;
    return *this;
}

VECTOR2 VECTOR2::operator+(const VECTOR2 otr) const
{
    return VECTOR2(this->x + otr.x, this->y + otr.y);
}

VECTOR2 VECTOR2::operator-(const VECTOR2 otr) const
{
    return VECTOR2(this->x - otr.x, this->y - otr.y);
}

VECTOR2 VECTOR2::operator*(float scl) const
{
    return VECTOR2(this->x * scl, this->y * scl);
}

VECTOR2 VECTOR2::operator/(float scl) const
{
    return VECTOR2(this->x / scl, this->y / scl);
}

VECTOR2 VECTOR2::operator%(float theta) const
{
    float radians = theta * (PI / 180);

    float cs = std::cos(radians);
    float sn = std::sin(radians);

    float px = x * cs - y * sn; 
    float py = x * sn + y * cs;

    return VECTOR2(px, py);
}

bool VECTOR2::operator==(const VECTOR2 otr)
{
    return this->x == otr.x && this->y == otr.y;
}

bool VECTOR2::operator!=(const VECTOR2 otr)
{
    return !(*this == otr);
}

float VECTOR2::dot(const VECTOR2 otr)
{
    return this->x * otr.x + this->y * otr.y; 
}

VECTOR2 VECTOR2::norm()
{
    return *this / this->mag();
}

VECTOR2& VECTOR2::trunc(float max) 
{
    if (this->mag() > max)
        this->reassign(this->norm() * max);
    return *this;
}

float VECTOR2::ang()
{
    return std::atan2(this->x, this->y);
}

float VECTOR2::mag()
{
    return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2));
}

const std::string VECTOR2::to_str() 
{
    char tmpbuf[256];
    std::cout << "[" << x << ", " << y << "] \n";
    return tmpbuf;
}