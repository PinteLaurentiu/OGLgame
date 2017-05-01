#include <assert.h>
#include "Color.h"
#include "glhs.h"

float Color::getR() const
{
    return r;
}

float Color::getG() const
{
    return g;
}

float Color::getB() const
{
    return b;
}

float Color::getA() const
{
    return a;
}

void Color::setR(float specter)
{
    r = specter;
}

void Color::setG(float specter)
{
    g = specter;
}

void Color::setB(float specter)
{
    b = specter;
}

void Color::setA(float specter)
{
    a = specter;
}

bool Color::equal(const Color& c1, const Color& c2)
{
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}

bool Color::operator==(const Color& other) const
{
    return Color::equal(*this, other);
}

bool Color::operator!=(const Color& other) const
{
    return !Color::equal(*this, other);
}

Color Color::Red = Color(1.0f, 0.25f, 0.25f, 1.0f),
      Color::Green = Color(0.25f, 1.0f, 0.25f, 1.0f),
      Color::Blue = Color(0.25f, 0.25f, 1.0f, 1.0f),
      Color::Cyan = Color(1.0f, 0.25f, 0.25f, 1.0f),
      Color::Orange = Color(0.25f, 1.0f, 1.0f, 1.0f),
      Color::Purple = Color(1.0f, 0.25f, 1.0f, 1.0f),
      Color::Yellow = Color(1.0f, 1.0f, 0.25f, 1.0f),
      Color::Black = Color(0.0f, 0.0f, 0.0f, 1.0f),
      Color::White = Color(1.0f, 1.0f, 1.0f, 1.0f),
      Color::Gray = Color(0.5f, 0.5f, 0.5f, 1.0f),
      Color::TranslucidBlack = Color(0.0f, 0.0f, 0.0f, 0.75f);

Color::Color() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}

Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

void Color::set()
{
	glColor4f(r, g, b, a);
}

void Color::unset()
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}
