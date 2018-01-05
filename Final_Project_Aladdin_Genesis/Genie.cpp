#include "Genie.h"
#define GENIE_XMLFILEPATH "Xml/Genie.xml"

Genie::Genie()
{
	genie_image = NULL;
	collType = CollUnknown;
	objType = OBJGenie;
}

void Genie::LoadResources()
{
	initx = x;
	inity = y;
	direction = true;
	isDead = false;
	normalx = 0.0f;
	normaly = 0.0f;
	vx = 0;
	vy = 0;
	animation_rate = 10;
	last_time = GetTickCount();

	genie_image = new Sprite(TextureManager::GetInstance()->GetGenieTexture(), 8, 20);

	if (begin_stat == 0)
	{
		status = _GenieStatus::SHOOT;
		arx = x + 61;
		ary = y + 51;
		Fly();
	}
	else
	{
		status = _GenieStatus::FLY;
		arx = x + 33;
		ary = y + 114;
		Shoot();
	}
}

void Genie::Render(int Delta)
{
	//update genie position
	arx += vx * Delta;
	ary += vy * Delta;

	//draw sprite
	genie_image->Render(GENIE_XMLFILEPATH, x, y, w, h, arx, ary, direction, 0);
	
	//install frame per second (animate rate)
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / animation_rate)
	{
		genie_image->Next();
		last_time = now;
	}
}


void Genie::ProcessInput()
{
	switch (status)
	{
	case _GenieStatus::SHOOT:
		Shoot();
		break;
	default:
		Fly();
		break;
	}
}

void Genie::Shoot()
{
	switch (status)
	{
	case _GenieStatus::SHOOT:
	{
				  if (genie_image->getIndex() == 20)
				  {
					  genie_image->setFrame(20, 25);
				  }
				  break;
	}
	default:
	{
			   status = _GenieStatus::SHOOT;
			   genie_image->setFrame(8, 20);
			   break;
	}
	}
}

void Genie::Fly()
{
	switch (status)
	{
	case _GenieStatus::FLY:
	{
				  break;
	}
	default:
	{
			   vx = 0.3f;
			   status = _GenieStatus::FLY;
			   genie_image->setFrame(0, 7);
			   break;
	}
	}
}

void Genie::resetProper()
{
	x = initx;
	y = inity;
	direction = true;
	isDie = false;
	isDead = false;
	normalx = 0.0f;
	normaly = 0.0f;
	vx = 0;
	vy = 0;
	animation_rate = 10;
	last_time = GetTickCount();

	if (begin_stat == 0)
	{
		status = _GenieStatus::SHOOT;
		arx = x + 61;
		ary = y + 51;
		Fly();
	}
	else
	{
		status = _GenieStatus::FLY;
		arx = x + 33;
		ary = y + 114;
		Shoot();
	}
}

Genie::~Genie()
{
	if (genie_image != NULL) { delete genie_image; genie_image = nullptr; }
}
