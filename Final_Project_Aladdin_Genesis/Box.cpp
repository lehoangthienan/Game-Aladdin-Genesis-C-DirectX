#include "Box.h"

//contructor of box class
Box::Box()
{}

Box::Box(float x, float y, float w, float h, float vx, float vy)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->vx = vx;
	this->vy = vy;
}

Box::Box(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

//set properties of the box
void Box::setBox(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

//destructor of box class
Box::~Box()
{}
