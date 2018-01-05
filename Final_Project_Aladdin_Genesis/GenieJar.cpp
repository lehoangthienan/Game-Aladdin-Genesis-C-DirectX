#include "GenieJar.h"
#define GENIEJAR_XMLFILEPATH "Xml/GenieJar.xml"

//contructor of GenieJar class
GenieJar::GenieJar()
{
	objType = OBJGenieJar;
}

//init object
void GenieJar::LoadResources()
{
	arx = x + 9;
	ary = y + 33;

	Item::LoadResources();
	animation_rate = 1;
	xmlFilePath = GENIEJAR_XMLFILEPATH;

	image = new Sprite(TextureManager::GetInstance()->GetItemsTexture(), 0, 0);
}

//action of GenieJar
void GenieJar::Active()
{
	switch (status)
	{
	case ACTIVED:
	{
					if (image->isActionFinish())
						image->setFrame(image->getLastFrame(), image->getLastFrame());
					break;
	}
	default:
	{
			   GameSound::getInstance()->play(COMEOUT_MUSIC);
			   status = ACTIVED;
			   image->setFrame(1, 9);
			   animation_rate = 10;
			   vy = 0;
			   vx = 0;
			   isDie = true;
			   isActive = true;
			   break;
	}
	}
}

void GenieJar::NonActive()
{}

//destructor of GenieJar class
GenieJar::~GenieJar()
{}
