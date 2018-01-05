#include "Rod.h"


//contructor of Rod class
Rod::Rod()
{
	objType = OBJRod;
	rod_image = NULL;
}

void Rod::setObjectFromID()
{
	collType = CollRod;
}

//init object
void Rod::LoadResources()
{
	arx = x;
	ary = y + 11;
	status = NOTMOVING;
	direction = true;
	animation_rate = 10;
	isDead = false;
	normalx = 0.0f;
	normaly = 0.0f;
	vx = 0;
	vy = 0;

	rod_image = new Sprite(TextureManager::GetInstance()->GetRodTexture(), 0, 0);
}

//process input
void Rod::ProcessInput()
{
	switch (status)
	{
	case MOVING:
		Move();
		break;
	default:
		NotMove();
		break;
	}
}

//sprite redering
void Rod::Render(int Delta)
{
	//update aladdin position
	arx += vx * Delta;
	ary += vy * Delta;

	//draw sprite
	rod_image->Render(ROD_XMLFILEPATH, x, y, w, h, arx, ary, direction, 0);

	//install frame per second (animate rate)
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / animation_rate)
	{
		rod_image->Next();
		last_time = now;
	}
}

//collision
void Rod::OnCollision(BaseObject* obj, float normalx, float normaly)
{
	if (normaly == -1.0f)
	{
		GameSound::getInstance()->play(COMEIN_MUSIC);
		Move();
	}
}

//interserct
void Rod::OnInterSerct(BaseObject* obj)
{}

//action of Rod
void Rod::NotMove()
{
	switch (status)
	{
	case NOTMOVING:
		break;
	default:
	{
			   status = NOTMOVING;
			   rod_image->setFrame(0, 0);
			   break;
	}
	}
}

void Rod::Move()
{
	switch (status)
	{
	case MOVING:
	{
				 if (rod_image->isActionFinish())
					 NotMove();
				 break;
	}
	default:
	{
			   status = MOVING;
			   rod_image->setFrame(0, 4);
			   animation_rate = 15;
			   break;
	}
	}
}

//get status aladdin
int Rod::getStatus()
{
	return status;
}

//destructor of Rod class
Rod::~Rod()
{
	if (rod_image != NULL) { delete rod_image; rod_image = nullptr; }
}
