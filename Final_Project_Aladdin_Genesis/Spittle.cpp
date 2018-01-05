#include "Spittle.h"


//contructor of Spittle class
Spittle::Spittle()
{
	objType = OBJSpittle;
	spittle_image = NULL;
	isDead = false;
}

void Spittle::setObjectFromID()
{
	collType = CollEnemy;
}

//init object
void Spittle::LoadResources()
{
	arx = x + 6;
	ary = y + 3;

	status = FLING;
	animation_rate = 15;
	isDead = false;
	normalx = 0.0f;
	normaly = 0.0f;

	spittle_image = new Sprite(TextureManager::GetInstance()->GetCamelTexture(), 7, 7);
}

//process input
void Spittle::ProcessInput()
{
	switch (status)
	{
	case DESTROY:
		Destroy();
		break;
	default:
		Fly();
		break;
	}
}

//sprite redering
void Spittle::Render(int Delta)
{
	//update aladdin position
	arx += vx * Delta;
	ary += vy * Delta;

	//draw sprite
	spittle_image->Render(SPITTLE_XMLFILEPATH, x, y, w, h, arx, ary, direction, 0);

	//install frame per second (animate rate)
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / animation_rate)
	{
		spittle_image->Next();
		last_time = now;
	}
}

//collision
void Spittle::OnCollision(BaseObject* obj, float normalx, float normaly)
{
	switch (obj->collType)
	{
	case CollGround: case CollStair:
		Collision::PreventMove(this, obj, normalx, normaly);
		break;
	}

}

//interserct
void Spittle::OnInterSerct(BaseObject* obj)
{
	if (collType != CollCamel && collType != CollRope && status != DESTROY)
		Destroy();
}

//action of Spittle
void Spittle::Fly()
{
	switch (status)
	{
	case FLING:
		break;
	default:
	{
			   status = FLING;
			   spittle_image->setFrame(0, 5);
			   animation_rate = 15;
			   break;
	}
	}
}

void Spittle::Destroy()
{
	switch (status)
	{
	case DESTROY:
	{
					isDead = true;
					camel->deleteSpittle(this);
					break;
	}
	default:
	{
			   status = DESTROY;
			   break;
	}
	}

}

//get status aladdin
int Spittle::getStatus()
{
	return status;
}

//get Spittle thrower
void Spittle::GetCamel(Camel *obj)
{
	camel = obj;
}

//destructor of Spittle class
Spittle::~Spittle()
{
	if (spittle_image != NULL){ delete spittle_image; spittle_image = nullptr; }
}
