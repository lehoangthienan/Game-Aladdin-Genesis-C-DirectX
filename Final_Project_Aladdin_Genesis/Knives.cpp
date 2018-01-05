#include "Knives.h"
#define KNIVES_XMLFILEPATH "Xml/Knives.xml"

Knives::Knives()
{
	collType = CollUnknown;
	objType = OBJKnives;
	knives_image = NULL;
	trans_left = false;
}

void Knives::LoadResources()
{
	initx = x;
	inity = y;
	arx = x;
	ary = y;
	direction = true;
	isDie = false;
	isDead = false;
	isKeyUpUp = true;
	isKeyDownUp = true;
	normalx = 0.0f;
	normaly = 0.0f;
	vx = 0;
	vy = 0;

	knives_image = new Sprite(TextureManager::GetInstance()->GetKnivesTexture(), 0, 0);
}

void Knives::UpdateKey()
{
	if (!dx.Key_Down(DIK_UP))
		isKeyUpUp = true;
	if (!dx.Key_Down(DIK_DOWN))
		isKeyDownUp = true;

	KeyDown = dx.Key_Down(DIK_DOWN);
	KeyUp = dx.Key_Down(DIK_UP);
}

void Knives::ProcessInput()
{
	UpdateKey();

	if (KeyUp && ary - 16 > limy_top && isKeyUpUp)
	{
		this->ary -= 16;
		isKeyUpUp = false;
	}
	if (KeyDown && ary + 16 < limy_bottom && isKeyDownUp)
	{
		this->ary += 16;
		isKeyDownUp = false;
	}
}

void Knives::Render(int Delta)
{
	knives_image->Render(KNIVES_XMLFILEPATH, x, y, w, h, arx, ary, direction, 0);
	
	DWORD now = GetTickCount();
	if (now - last_time > 200)
	{
		if (trans_left)
		{
			arx -= 10;
			trans_left = false;
		}
		else
		{
			arx += 10;
			trans_left = true;
		}
		last_time = now;
	}
}

void Knives::resetProper()
{
	x = initx;
	y = inity;
	arx = x;
	ary = y;
	direction = true;
	isDie = false;
	isDead = false;
	isKeyUpUp = true;
	isKeyDownUp = true;
	normalx = 0.0f;
	normaly = 0.0f;
	vx = 0;
	vy = 0;
}

Knives::~Knives()
{
	if (knives_image != NULL) { delete knives_image; knives_image = nullptr; }
}
