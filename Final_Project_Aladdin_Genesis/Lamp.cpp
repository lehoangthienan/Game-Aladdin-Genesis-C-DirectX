#include "Lamp.h"
#define LAMP_XMLFILEPATH "Xml/Lamp.xml"
#define ENEMYEXPLOSIONS2 "Xml/EnemyExplosions2.xml"

//contructor of Lamp class
Lamp::Lamp()
{
	objType = OBJLamp;
}

//init object
void Lamp::LoadResources()
{
	arx = x + 17;
	ary = y + 16;

	Item::LoadResources();
	animation_rate = 1;
	xmlFilePath = LAMP_XMLFILEPATH;

	image = new Sprite(TextureManager::GetInstance()->GetItemsTexture(), 0, 0);
}

//action of Lamp
void Lamp::Active()
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
			   GameSound::getInstance()->play(LAMP_MUSIC);
			   status = ACTIVED;
			   xmlFilePath = ENEMYEXPLOSIONS2;
			   image->setImage(TextureManager::GetInstance()->GetEnemyExplosionTexture());
			   image->setFrame(0, 14);
			   animation_rate = 12;
			   vy = 0;
			   vx = 0;
			   arx = (this->left() + this->right()) / 2;
			   ary = (this->top() + this->bottom()) / 2 - 20;
			   isDie = true;
			   isActive = true;
			   break;
	}
	}
}

void Lamp::NonActive()
{}

//destructor of Lamp class
Lamp::~Lamp()
{}