#include "Abu.h"
#define ABU_XMLFILEPATH "Xml/Abu.xml"

//contructor of abu class
Abu::Abu()
{
	abu_image = NULL;
	collType = CollUnknown;
	objType = OBJAbu;
}

void Abu::LoadResources()
{
	initx = x;
	inity = y;
	arx = x;
	ary = y;
	direction = true;
	isDie = false;
	isDead = false;
	normalx = 0.0f;
	normaly = 0.0f;
	vx = 0;
	vy = 0;
	animation_rate = 8;
	last_time = GetTickCount();
	abu_image = new Sprite(TextureManager::GetInstance()->GetAbuTexture(), 0, 5);

	if (begin_stat == 0)
	{
		status = RUN;
		Fan();
	}
	else
	{
		status = FAN;
		Run();
	}
}


void Abu::ProcessInput()
{
	switch (status)
	{
	case _AbuStatus::RUN:
		Run();
		break;
	default:
		Fan();
		break;
	}

}

void Abu::Render(int Delta)
{
	//update aladdin position
	arx += vx * Delta;
	ary += vy * Delta;

	//draw sprite
	abu_image->Render(ABU_XMLFILEPATH, x, y, w, h, arx, ary, direction, 0);

	//install frame per second (animate rate)
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / animation_rate)
	{
		abu_image->Next();
		last_time = now;
	}
}

//run action
void Abu::Run()
{
	switch (status)
	{
	case _AbuStatus::RUN:
	{
							break;
	}
	default:
	{		   
			   status = _AbuStatus::RUN;
			   abu_image->setFrame(6, 13);
			   animation_rate = 20;
			   vx = -0.45f;
			   vy = 0;
			   break;
	}
	}
}

//fan action
void Abu::Fan()
{
	switch (status)
	{
	case FAN:
	{
				break;
	}
	default:
	{
			   status = FAN;
			   abu_image->setFrame(0, 5);
			   animation_rate = 15;
			   vx = 0;
			   vy = 0;
			   break;
	}
	}
}

void Abu::resetProper()
{
	x = initx;
	y = inity;
	arx = x;
	ary = y;
	direction = true;
	isDie = false;
	isDead = false;
	normalx = 0.0f;
	normaly = 0.0f;
	vx = 0;
	vy = 0;
	animation_rate = 8;
	last_time = GetTickCount();

	if (begin_stat == 0)
	{
		status = RUN;
		Fan();
	}
	else
	{
		status = FAN;
		Run();
	}
}

//destructor of abu class
Abu::~Abu()
{
	if (abu_image != NULL) { delete abu_image; abu_image = nullptr; }
}
