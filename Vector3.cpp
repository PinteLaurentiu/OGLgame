#include "Vector3.h"

Vector3::Vector3() : x(0.0f),  y(0.0f),  z(0.0f) {}

Vector3::Vector3(float x, float y, float z) : x(x),  y(y),  z(z) {}

Vector3::~Vector3() {}

float Vector3::getX() const
{
    return x;
}

float Vector3::getY() const
{
    return y;
}

float Vector3::getZ() const
{
    return z;
}

void Vector3::setX(float data)
{
    x = data;
}

void Vector3::setY(float data)
{
    y = data;
}

void Vector3::setZ(float data)
{
    z = data;
}

bool Vector3::equal(const Vector3& v1, const Vector3& v2)
{
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

bool Vector3::operator==(const Vector3& other) const
{
    return Vector3::equal(*this, other);
}

bool Vector3::operator!=(const Vector3& other) const
{
    return !Vector3::equal(*this, other);
}

