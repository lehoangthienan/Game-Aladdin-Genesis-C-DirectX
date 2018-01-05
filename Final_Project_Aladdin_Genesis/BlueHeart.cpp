#include "BlueHeart.h"
#define BLUEHEART_XMLFILEPATH "Xml/BlueHeart.xml"

//contructor of BlueHeart class
BlueHeart::BlueHeart()
{
	objType = OBJBlueHeart;
}

//init object
void BlueHeart::LoadResources()
{
	arx = x + 9;
	ary = y + 12;

	Item::LoadResources();
	animation_rate = 1;
	xmlFilePath = BLUEHEART_XMLFILEPATH;

	image = new Sprite(TextureManager::GetInstance()->GetItemsTexture(), 0, 0);
}

//action of BlueHeart
void BlueHeart::Active()
{
	Item::Active();
}

void BlueHeart::NonActive()
{
	if (image->isActionFinish())
	{
		DWORD end_wait = GetTickCount();
		if (end_wait - start_wait > 2500)
		{
			image->setFrame(0, 7);
			animation_rate = 10;
			start_wait = GetTickCount();
		}
		else
		{
			image->setFrame(0, 0);
		}
	}
}

//destructor of BlueHeart class
BlueHeart::~BlueHeart()
{}
