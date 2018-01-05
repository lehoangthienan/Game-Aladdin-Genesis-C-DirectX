#include "Fire.h"
#define FIRE_XMLFILEPATH "Xml/Fire.xml"

//contructor of Fire class
Fire::Fire()
{
	objType = OBJFire;
}

//init object
void Fire::LoadResources()
{
	arx = x + 12;
	ary = y;

	status = _FireStatus::MOVING;
	animation_rate = 10;
	xmlFilePath = FIRE_XMLFILEPATH;
	vx = 0;
	vy = 0;

	if (typeFire == 1)
		image = new Sprite(TextureManager::GetInstance()->GetJafarTexture(), 25, 29);
	else
		image = new Sprite(TextureManager::GetInstance()->GetJafarTexture(), 30, 30);
}

//process input
void Fire::ProcessInput()
{
	switch (status)
	{
	case _FireStatus::DESTROY:
		Destroy();
		return;
	default:
		Move();
		break;
	}

	//simulate fall down (gravity)
	if (typeFire == 2)
		vy += 0.1f;
}

//change and reset frame size
void Fire::changeFrameSize(BaseObject*obj)
{}

void Fire::resetFrameSize(BaseObject*obj)
{}

//collision
void Fire::OnCollision(BaseObject* obj, float normalx, float normaly)
{
	switch (obj->collType)
	{
	case CollGround:
	{
					   Collision::PreventMove(this, obj, normalx, normaly);
					   if (normalx != 0 && status != _FireStatus::DESTROY && typeFire == 2)
						   Destroy();
					   break;
	}
	}
}

//interserct
void Fire::OnInterSerct(BaseObject* obj)
{}

//action of Fire
void Fire::Move()
{
	switch (status)
	{
	case _FireStatus::MOVING:
	{
								if (image->isActionFinish() && typeFire == 1)
									Destroy();
								if (normaly == -1.0f && typeFire == 2 && image->getLastFrame() == 30)
								{
									image->setFrame(30, 37);
									if (direction)
										vx = 0.5f;
									else
										vx = -0.5f;
									vy = 0;
								}
								break;
	}
	default:
	{
			   status = _FireStatus::MOVING;
			   if (typeFire == 1)
			   {
				   image->setFrame(25, 29);
				   animation_rate = 10;
				   vx = 0;
			   }
			   else
			   {
				   image->setFrame(30, 30);
				   animation_rate = 15;
			   }
			   break;
	}
	}
}

void Fire::Destroy()
{
	switch (status)
	{
	case _FireStatus::DESTROY:
	{
								 isDead = true;
								 vx = 0;
								 vy = 0;
								 if (fireCarpet != NULL)
									 fireCarpet->deleteFire(this);
								 else if (boss != NULL)
									 boss->deleteFire(this);
								 break;
	}
	default:
	{
			   status = _FireStatus::DESTROY;
			   break;
	}
	}
}

//get status aladdin
int Fire::getStatus()
{
	return status;
}

//get Fire Carpet
void Fire::GetFireCarpet(FireCarpet *obj)
{
	this->fireCarpet = obj;
}

//get Boss
void Fire::GetBoss(Boss*obj)
{
	this->boss = obj;
}

//destructor of Fire class
Fire::~Fire()
{}
