#include "Ruby.h"
#define RUBY_XMLFILEPATH "Xml/Ruby.xml"

//contructor of Ruby class
Ruby::Ruby()
{
	objType = OBJRuby;
}

//init object
void Ruby::LoadResources()
{
	arx = x + 8;
	ary = y + 8;

	Item::LoadResources();
	animation_rate = 1;
	xmlFilePath = RUBY_XMLFILEPATH;

	image = new Sprite(TextureManager::GetInstance()->GetItemsTexture(), 0, 0);
}

//action of Ruby
void Ruby::Active()
{
	Item::Active();
}

void Ruby::NonActive()
{
	if (image->isActionFinish())
	{
		DWORD end_wait = GetTickCount();
		if (end_wait - start_wait > 3500)
		{
			image->setFrame(0, 8);
			animation_rate = 12;
			start_wait = GetTickCount();
		}
		else
		{
			image->setFrame(0, 0);
		}
	}
}

//get sprite
Sprite* Ruby::getSprite()
{
	return image;
}

//destructor of Ruby class
Ruby::~Ruby()
{}
