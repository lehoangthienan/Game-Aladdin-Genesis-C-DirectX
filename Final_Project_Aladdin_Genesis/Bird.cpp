#include "Bird.h"
#define BIRD_XMLFILEPATH "Xml/Bird.xml"

Bird::Bird()
{
	bird_image = NULL;
	collType = CollUnknown;
	objType = OBJBird;
}

void Bird::LoadResources()
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

	bird_image = new Sprite(TextureManager::GetInstance()->GetBirdTexture(), 0, 0);
}

void Bird::ProcessInput()
{
	//formular gravity
	vy += 0.05f;
}

void Bird::Render(int Delta)
{
	arx += vx*Delta;
	ary += vy*Delta;
	
	bird_image->Render(BIRD_XMLFILEPATH, x, y, w, h, arx, ary, direction, 0);
}

void Bird::resetProper()
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
}

Bird::~Bird()
{
	if (bird_image != NULL) { delete bird_image; bird_image = nullptr; }
}
