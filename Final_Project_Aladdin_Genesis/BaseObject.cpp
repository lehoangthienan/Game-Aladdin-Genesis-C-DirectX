#include "BaseObject.h"

//contructor of BaseObject class
BaseObject::BaseObject()
{
	isDead = false;
	isActive = false;
	isDie = false;
}

BaseObject::BaseObject(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

//init object
void BaseObject::LoadResources()
{}

//process input
void BaseObject::ProcessInput()
{}

//sprite redering
void BaseObject::Render(int Delta)
{}

//set type object from object's id
void BaseObject::setObjectFromID()
{}

void BaseObject::OnCollision(BaseObject*obj, float normalx, float normaly)
{}

void BaseObject::OnInterSerct(BaseObject*obj)
{}

void BaseObject::setPosition(float arx, float ary)
{
	float distance_x = this->arx - x;
	float distance_y = this->ary - y;

	this->arx = arx;
	this->ary = ary;
	x = arx - distance_x;
	y = ary - distance_y;
}

float BaseObject::top()
{
	return y;
}

float BaseObject::bottom()
{
	return y + h;
}

float BaseObject::left()
{
	return x;
}

float BaseObject::right()
{
	return x + w;
}

vector<BaseObject*>* BaseObject::GetList()
{
	return NULL;
}

//change and reset frame size
void BaseObject::changeFrameSize(BaseObject*obj)
{}

void BaseObject::resetFrameSize(BaseObject*obj)
{}

//when object die
void BaseObject::Die()
{}

//get status of object
int BaseObject::getStatus()
{
	return 0;
}

int BaseObject::getLastStatus()
{
	return 0;
}

void BaseObject::resetProper()
{}

int BaseObject::getTypeObj()
{
	return 0;
}


//destructor of BaseObject class
BaseObject::~BaseObject(){}