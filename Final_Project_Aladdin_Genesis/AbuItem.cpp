#include "AbuItem.h"
#define ABUITEM_XMLFILEPATH "Xml/AbuItem.xml"

//contructor of AbuItem class
AbuItem::AbuItem()
{
	objType = OBJAbuItem;
}

//init object
void AbuItem::LoadResources()
{
	arx = x + 9;
	ary = y + 9;

	Item::LoadResources();
	animation_rate = 1;
	xmlFilePath = ABUITEM_XMLFILEPATH;

	image = new Sprite(TextureManager::GetInstance()->GetItemsTexture(), 0, 0);
}

//action of AbuItem
void AbuItem::Active()
{
	Item::Active();
}

void AbuItem::NonActive()
{
	if (image->isActionFinish())
	{
		DWORD end_wait = GetTickCount();
		if (end_wait - start_wait > 3500)
		{
			image->setFrame(0, 9);
			animation_rate = 12;
			start_wait = GetTickCount();
		}
		else
		{
			image->setFrame(0, 0);
		}
	}
}

//destructor of AbuItem class
AbuItem::~AbuItem()
{}
