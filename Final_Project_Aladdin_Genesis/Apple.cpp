#include "Apple.h"
#define APPLE_XMLFILEPATH "Xml/Apple.xml"
#define APPLEITEM_XMLFILEPATH "Xml/AppleItem.xml"
#define ITEMACTIVED_XMLFILEPATH "Xml/ItemActived.xml"

//contructor of Apple class
Apple::Apple()
{
	apple_image = NULL;
	isDead = false;
	objType = OBJApple;
}

void Apple::setObjectFromID()
{
	if (id == 6)
		collType = CollApple;
	else
		collType = CollItem;
}

//init object
void Apple::LoadResources()
{
	initx = x;
	inity = y;
	if (collType == CollApple)
	{
		arx = x + 7;
		ary = y + 6;
		status = FLING;
		xmlFilePath = APPLE_XMLFILEPATH;
		typeSplit_Half = true;
		apple_image = new Sprite(TextureManager::GetInstance()->GetAladdinTexture(), 0, 0);
	}
	else
	{
		arx = x + 5;
		ary = y + 6;
		status = NOTMOVING;
		isActive = false;
		direction = true;
		xmlFilePath = APPLEITEM_XMLFILEPATH;
		apple_image = new Sprite(TextureManager::GetInstance()->GetItemsTexture(), 0, 0);
	}
	animation_rate = 10;
	isDie = false;
	isDead = false;
	normalx = 0.0f;
	normaly = 0.0f;
}

//process input
void Apple::ProcessInput()
{
	switch (status)
	{
	case SPLIT_HALF:
		Split_Half();
		break;
	case BURST:
		Burst();
		return;
	case ACTIVED:
		Active();
		break;
	default:
		Move();
		break;
	}

	//simulate fall down (gravity)
	if (collType == CollApple)
		vy += 0.1f;
}

//sprite redering
void Apple::Render(int Delta)
{
	//update aladdin position
	arx += vx * Delta;
	ary += vy * Delta;

	//draw sprite
	apple_image->Render(xmlFilePath, x, y, w, h, arx, ary, direction, 0);

	//install frame per second (animate rate)
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / animation_rate)
	{
		apple_image->Next();
		last_time = now;
	}
}

//collision
void Apple::OnCollision(BaseObject* obj, float normalx, float normaly)
{
	switch (obj->collType)
	{
	case CollGround: case CollStair:
		Collision::PreventMove(this, obj, normalx, normaly);
		break;
	}

}

//interserct
void Apple::OnInterSerct(BaseObject* obj)
{
	if (collType == CollApple && obj->collType != CollStar && obj->collType != CollItem)
	{
		if (obj->objType == OBJSword)
		{
			Split_Half();
		}
		else
		{
			if (!(obj->collType == CollLine && vy < 0))
				Burst();
		}
		GameSound::getInstance()->play(APPLE_POP_MUSIC);

	}
	if (collType == CollItem && obj->collType == CollAladdin)
	{
		GameSound::getInstance()->play(APPLE_MUSIC);
		Active();
	}
}

//action of Apple
void Apple::Move()
{
	if (collType == CollApple)
		status = FLING;
	else
	{
		vy = 0;
		vx = 0;
	}
}

void Apple::Burst()
{
	switch (status)
	{
	case BURST:
	{
				  if (apple_image->isActionFinish())
				  {
					  isDead = true;
					  Aladdin::GetInstance()->deleteApple(this);
				  }
				  break;
	}
	default:
	{
			   status = BURST;
			   apple_image->setFrame(1, 5);
			   animation_rate = 12;
			   isDie = true;
			   vx = 0;
			   vy = 0;
			   break;
	}
	}
}

void Apple::Active()
{
	switch (status)
	{
	case ACTIVED:
	{
					if (apple_image->isActionFinish())
						isDead = true;
					break;
	}
	default:
	{
			   status = ACTIVED;
			   xmlFilePath = ITEMACTIVED_XMLFILEPATH;
			   apple_image->setImage(TextureManager::GetInstance()->GetItemActivedTexture());
			   apple_image->setFrame(0, 3);
			   animation_rate = 10;
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

void Apple::Split_Half()
{
	switch (status)
	{
	case SPLIT_HALF:
	{
					   if (apple_image->getIndex() == 6)
					   {
						   apple_image->setFrame(7, 10);
						   apple_image->setIndex(8);
						   Apple*obj = new Apple();
						   obj->id = 6;
						   obj->x = this->x;
						   obj->y = this->y;
						   obj->direction = this->direction;
						   if (direction)
							   obj->vx = -0.7f;
						   else
							   obj->vx = 0.7f;
						   obj->vy = -1.2f;
						   obj->setObjectFromID();
						   obj->LoadResources();
						   Aladdin::GetInstance()->createApple(obj);
						   obj->typeSplit_Half = false;
						   obj->Split_Half();
					   }
					   break;
	}	
	default:
	{
			   if (typeSplit_Half)
			   {
				   status = SPLIT_HALF;
				   apple_image->setFrame(6, 10);
				   animation_rate = 5;
				   if (direction)
					   vx = -1.0f;
				   else
					   vx = 1.0f;
				   vy = -1.5f;
			   }
			   else
			   {
				   status = SPLIT_HALF;
				   apple_image->setFrame(7, 8);
				   animation_rate = 5;
			   }
			   break;
	}
	}
}

//get status aladdin
int Apple::getStatus()
{
	return status;
}

//get sprite
Sprite* Apple::getSprite()
{
	return apple_image;
}

//reset
void Apple::resetProper()
{
	x = initx;
	y = inity;
	if (collType == CollApple)
	{
		arx = x + 7;
		ary = y + 6;
		status = FLING;
		xmlFilePath = APPLE_XMLFILEPATH;
		typeSplit_Half = true;
		apple_image->setImage(TextureManager::GetInstance()->GetAladdinTexture());
		apple_image->setFrame(0, 0);
	}
	else
	{
		arx = x + 5;
		ary = y + 6;
		status = NOTMOVING;
		isActive = false;
		direction = true;
		xmlFilePath = APPLEITEM_XMLFILEPATH;
		apple_image->setImage(TextureManager::GetInstance()->GetItemsTexture());
		apple_image->setFrame(0, 0);
	}
	animation_rate = 10;
	isDie = false;
	isDead = false;
	normalx = 0.0f;
	normaly = 0.0f;
}

//destructor of Apple class
Apple::~Apple()
{
	if (apple_image != NULL){ delete apple_image; apple_image = nullptr; }
}
