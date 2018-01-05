#include "GenieFace.h"
#define GENIEFACE_XMLFILEPATH "Xml/GenieFace.xml"
#define ENEMYEXPLOSIONS1 "Xml/EnemyExplosions1.xml"

//contructor of GenieFace class
GenieFace::GenieFace()
{
	objType = OBJGenieFace;
}

//init object
void GenieFace::LoadResources()
{
	arx = x + 19;
	ary = y + 25;

	Item::LoadResources();
	animation_rate = 1;
	xmlFilePath = GENIEFACE_XMLFILEPATH;

	image = new Sprite(TextureManager::GetInstance()->GetItemsTexture(), 0, 0);
}

//action of GenieFace
void GenieFace::Active()
{
	switch (status)
	{
	case ACTIVED:
	{
					if (image->isActionFinish())
						isDead = true;
					break;
	}
	default:
	{
			   status = ACTIVED;
			   xmlFilePath = ENEMYEXPLOSIONS1;
			   image->setImage(TextureManager::GetInstance()->GetEnemyExplosionTexture());
			   image->setFrame(5, 23);
			   animation_rate = 15;
			   vy = 0;
			   vx = 0;
			   arx = (this->left() + this->right()) / 2;
			   ary = (this->top() + this->bottom()) / 2;
			   isDie = true;
			   isActive = true;
			   break;
	}
	}
}

void GenieFace::NonActive()
{
	if (image->isActionFinish())
	{
		DWORD end_wait = GetTickCount();
		if (end_wait - start_wait > 3000)
		{
			image->setFrame(0, 3);
			animation_rate = 7;
			start_wait = GetTickCount();
		}
		else
		{
			image->setFrame(0, 0);
		}
	}
}

//destructor of GenieFace class
GenieFace::~GenieFace()
{}