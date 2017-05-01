/*
 * Cube.cpp
 *
 *  Created on: May 1, 2017
 *      Author: lau
 */

#include "Cube.h"
#include "glhs.h"

Cube::Cube(float size, const Vector3& pos, const Color& color) : size(size/2.0f), pos(pos), color(color) {}

Cube::Cube() : size(0.0f) {}

Cube::~Cube() {}

void Cube::draw()
{
	color.set();
	glBegin(GL_QUADS);

    glVertex3f(pos.getX() - size, pos.getY() + size, pos.getZ() - size); //BACK
	glVertex3f(pos.getX() + size, pos.getY() + size, pos.getZ() - size);
	glVertex3f(pos.getX() + size, pos.getY() - size, pos.getZ() - size);
	glVertex3f(pos.getX() - size, pos.getY() - size, pos.getZ() - size);

	glVertex3f(pos.getX() - size, pos.getY() + size, pos.getZ() + size); //FRONT
	glVertex3f(pos.getX() + size, pos.getY() + size, pos.getZ() + size);
	glVertex3f(pos.getX() + size, pos.getY() - size, pos.getZ() + size);
	glVertex3f(pos.getX() - size, pos.getY() - size, pos.getZ() + size);

	glVertex3f(pos.getX() + size, pos.getY() + size, pos.getZ() - size); //RIGHT
	glVertex3f(pos.getX() + size, pos.getY() + size, pos.getZ() + size);
	glVertex3f(pos.getX() + size, pos.getY() - size, pos.getZ() + size);
	glVertex3f(pos.getX() + size, pos.getY() - size, pos.getZ() - size);

	glVertex3f(pos.getX() - size, pos.getY() + size, pos.getZ() - size); //LEFT
	glVertex3f(pos.getX() - size, pos.getY() + size, pos.getZ() + size);
	glVertex3f(pos.getX() - size, pos.getY() - size, pos.getZ() + size);
	glVertex3f(pos.getX() - size, pos.getY() - size, pos.getZ() - size);

	glVertex3f(pos.getX() - size, pos.getY() + size, pos.getZ() - size); //TOP
	glVertex3f(pos.getX() + size, pos.getY() + size, pos.getZ() - size);
	glVertex3f(pos.getX() + size, pos.getY() + size, pos.getZ() + size);
	glVertex3f(pos.getX() - size, pos.getY() + size, pos.getZ() + size);

	glVertex3f(pos.getX() - size, pos.getY() - size, pos.getZ() - size); //BOTTOM
	glVertex3f(pos.getX() + size, pos.getY() - size, pos.getZ() - size);
	glVertex3f(pos.getX() + size, pos.getY() - size, pos.getZ() + size);
	glVertex3f(pos.getX() - size, pos.getY() - size, pos.getZ() + size);


	glEnd();
}
