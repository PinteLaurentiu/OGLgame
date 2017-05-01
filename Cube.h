#ifndef CUBE_H
#define CUBE_H

#include "Color.h"
#include "Vector3.h"

class Cube
{
public:
	Cube(float size, const Vector3& pos, const Color& color);
	Cube();
	virtual ~Cube();
	void draw();
private:
	float size;
	Vector3 pos;
	Color color;
};

#endif // CUBE_H
