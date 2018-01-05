#include "FallingGround.h"


//contructor of FallingGround class
FallingGround::FallingGround()
{
	objType = OBJFallingGround;
	fallingground_image = NULL;
}

void FallingGround::setObjectFromID()
{
	collType = CollLine;
}

//init object
void FallingGround::LoadResources()
{
	arx = x;
	ary = y;
	status = NOTMOVING;
	direction = true;
	animation_rate = 1;
	isDead = false;
	normalx = 0.0f;
	normaly = 0.0f;
	vx = 0;
	vy = 0;

	fallingground_image = new Sprite(TextureManager::GetInstance()->GetFallingGroundTexture(), 0, 0);
}

//process input
void FallingGround::ProcessInput()
{
	switch (status)
	{
	case DESTROY:
		Destroy();
		break;
	case FALLING:
		Fall();
		break;
	default:
		Move();
		break;
	}
}

//sprite redering
void FallingGround::Render(int Delta)
{
	//update aladdin position
	arx += vx * Delta;
	ary += vy * Delta;

	//draw sprite
	fallingground_image->Render(FALLINGGROUND_XMLFILEPATH, x, y, w, h, arx, ary, direction, 0);

	//install frame per second (animate rate)
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / animation_rate)
	{
		fallingground_image->Next();
		last_time = now;
	}
}

//collision
void FallingGround::OnCollision(BaseObject* obj, float normalx, float normaly)
{
	if (obj->collType == CollAladdin && status != FALLING && normaly == -1.0f)
		Fall();
}

//interserct
void FallingGround::OnInterSerct(BaseObject* obj)
{}

//action of FallingGround
void FallingGround::Move()
{
	status = NOTMOVING;
	vx = 0;
	vy = 0;
}

void FallingGround::Fall()
{
	switch (status)
	{
	case FALLING:
	{
					DWORD end_waitfall = GetTickCount();
					if (end_waitfall-start_waitfall > 200)
						vy += 0.05;
					if (vy >= 2.0f)
						Destroy();
					break;
	}
	default:
	{
			   start_waitfall = GetTickCount();
			   status = FALLING;
	}
	}
}

void FallingGround::Destroy()
{
	isDie = true;
	isDead = false;
}


//get status aladdin
int FallingGround::getStatus()
{
	return status;
}

void FallingGround::resetProper()
{
	arx = x;
	ary = y;
	status = NOTMOVING;
	direction = true;
	animation_rate = 1;
	isDie = false;
	isDead = false;
	normalx = 0.0f;
	normaly = 0.0f;
	vx = 0;
	vy = 0;
}

//destructor of FallingGround class
FallingGround::~FallingGround()
{
	if (fallingground_image != NULL){ delete fallingground_image; fallingground_image = nullptr; }
}
