#include "Ground.h"


Ground::Ground()
{
	objType = OBJGround;
	isDead = false;
}

void Ground::setObjectFromID()
{
	switch (id)
	{
	case 3:
		collType = CollStair; 
		break;
	case 25:
		collType = CollLine;
		break;
	default:
		collType = CollGround;
		break;
	}
}

//init object
void Ground::LoadResources()
{}

//sprite redering
void Ground::Render(int Delta)
{}

//change and reset frame size
void Ground::changeFrameSize(BaseObject*obj)
{
	if (this->collType == CollStair && obj->collType == CollAladdin)
	{
		y -= 20;
		h += 20;
	}
}

void Ground::resetFrameSize(BaseObject*obj)
{
	if (this->collType == CollStair && obj->collType == CollAladdin)
	{
		y += 20;
		h -= 20;
	}
}

Ground::~Ground()
{}
