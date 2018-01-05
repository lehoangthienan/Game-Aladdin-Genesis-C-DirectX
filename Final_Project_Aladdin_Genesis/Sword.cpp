#include "Sword.h"

//contructor of Sword class
Sword::Sword()
{
	objType = OBJSword;
	swordsMan = NULL;
	guard3 = NULL;
}

//init object
void Sword::LoadResources()
{
	arx = x + 5;
	ary = y + 15;

	status = _SwordStatus::FLING;
	animation_rate = 15;
	xmlFilePath = SWORD_XMLFILEPATH;

	Enemy::LoadResources();
	image = new Sprite(TextureManager::GetInstance()->GetGuardsTexture(), 0, 6);
}

//process input
void Sword::ProcessInput()
{
	if (isDie)
	{
		Die();
		return;
	}

	switch (status)
	{
	case _SwordStatus::DESTROY:
		Destroy();
		return;
	default:
		Fly();
		break;
	}

	//simulate fall down (gravity)
	vy += 0.1f;
}

//collision
void Sword::OnCollision(BaseObject* obj, float normalx, float normaly)
{
	switch (obj->collType)
	{
	case CollGround: case CollStair:
		Collision::PreventMove(this, obj, normalx, normaly);
		break;
	}

}

//interserct
void Sword::OnInterSerct(BaseObject* obj)
{
	if (obj->collType == CollGround || obj->collType == CollStair|| obj->collType == CollLine)
	{
		if (status != _SwordStatus::DESTROY)
			Destroy();
	}
	if (obj->collType == CollApple || obj->objType == OBJSpittle)
	{
		Die();
		status = _SwordStatus::DIE;
	}
	if (obj->collType == CollAladdin && Aladdin::GetInstance()->getStatus() == _AladdinStatus::CUTTING && status == _SwordStatus::FLING)
	{
		GameSound::getInstance()->play(SWORD_SWORD_MUSIC);

		if (obj->getLastStatus() != 12 && obj->getLastStatus() != 13 && obj->getLastStatus() != 14 && obj->getLastStatus() != 15)
		{

			if (obj->direction && obj->right() - 2 < this->arx)
			{
				this->vx = 1.0f;
				this->vy = -2.0f;

			}
			if (!obj->direction && obj->left() + 2 > this->arx)
			{
				this->vx = -1.0f;
				this->vy = -2.0f;
			}
		}
		else
		{
			if (obj->direction && obj->left() + 2 > this->arx)
			{
				this->vx = -1.0f;
				this->vy = -2.0f;
			}
			if (!obj->direction &&  obj->right() - 2 < this->arx)
			{
				this->vx = 1.0f;
				this->vy = -2.0f;
			}
		}
	}
}

//action of Sword
void Sword::Fly()
{
	switch (status)
	{
	case _SwordStatus::FLING:
		break;
	default:
	{
			   status = _SwordStatus::FLING;
			   image->setFrame(0, 6);
			   animation_rate = 15;
			   break;
	}
	}
}

void Sword::Destroy()
{
	switch (status)
	{
	case _SwordStatus::DESTROY:
	{
								  if (image->isActionFinish())
								  {
									  isDead = true;
									  vx = 0;
									  vy = 0;
									  GameSound::getInstance()->play(SWORD_SWORD_MUSIC);

									  if (swordsMan != NULL)
										  swordsMan->deleteSword(this);
									  else if (guard3 != NULL)
										  guard3->deleteSword(this);
								  }
								  break;
	}
	default:
	{
			   status = _SwordStatus::DESTROY;
			   xmlFilePath = DISAPPEAR_XMLFILEPATH;
			   image->setImage(TextureManager::GetInstance()->GetJafarTexture());
			   image->setFrame(0, 2);
			   animation_rate = 7;
			   vx = 0;
			   vy = 0;
			   break;
	}
	}

}

void Sword::Die()
{
	Enemy::Die();
	if (isDead)
	{
		if (swordsMan != NULL)
			swordsMan->deleteSword(this);
		else if (guard3 != NULL)
			guard3->deleteSword(this);
	}
}

//get status aladdin
int Sword::getStatus()
{
	return status;
}

//get Sword thrower
void Sword::GetSwordsman(Swordsman *obj)
{
	swordsMan = obj;
}

//get Guard3
void Sword::GetGuard3(Guard3 *obj)
{
	this->guard3 = obj;
}

//destructor of Sword class
Sword::~Sword()
{
	if (image != NULL){ delete image; image = nullptr; }
}
