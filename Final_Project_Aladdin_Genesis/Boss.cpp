#include "Boss.h"

Boss::Boss()
{
	objType = OBJBoss;
}

void Boss::LoadResources()
{
	arx = x + 22;
	ary = y + 71;
	status = _BossStatus::STANDING;
	animation_rate = 10;
	vx = 0;
	vy = 0;
	isCreate = false;
	startCut = GetTickCount();
	xmlFilePath = BOSS_XMLFILEPATH;
	typeBoss = 0;
	blood = 20;
	isHurt = false;

	Enemy::LoadResources();
	image = new Sprite(TextureManager::GetInstance()->GetJafarTexture(), 0, 0);
}

void Boss::ProcessInput()
{
	if (blood > 10)
		typeBoss = 0;
	else
		typeBoss = 1;

	if (isDie)
	{
		Die();
		return;
	}
	
	switch (status)
	{
	case _BossStatus::ATTACK:
		Attack();
		break;
	default:
		Stand();
		break;
	}

	//simulate fall down (gravity)
	//vy += 0.1f;

}

void Boss::changeFrameSize(BaseObject*obj)
{
	if (obj->collType == CollAladdin)
	{
		this->x -= 700;
		this->w += 1400;
	}
}

void Boss::resetFrameSize(BaseObject*obj)
{
	if (obj->collType == CollAladdin)
	{
		this->x += 700;
		this->w -= 1400;
	}
}

void Boss::OnCollision(BaseObject* obj, float normalx, float normaly)
{
	switch (obj->collType)
	{
	case CollGround:
		Collision::PreventMove(this, obj, normalx, normaly);
		break;
	case CollLine:
		Collision::CollisionLine(this, obj, normalx, normaly);
		break;
	}
}

void Boss::OnInterSerct(BaseObject* obj)
{
	if (obj->collType == CollAladdin)
	{
		if (Aladdin::GetInstance()->getStatus() == _AladdinStatus::CUTTING && !isHurt)
		{
			if ((obj->direction && obj->right() > this->left() && obj->arx < this->arx) || (!obj->direction && obj->left() < this->right() && obj->arx > this->arx))
			{
				blood--;
				GameSound::getInstance()->play(JAFAR_HURT_MUSIC);
			}
			if (blood == 0)
			{
				Die();
				status = _BossStatus::DIE;
				return;
			}
			isHurt = true;
		}
		if (Aladdin::GetInstance()->getStatus() != _AladdinStatus::CUTTING)
			isHurt = false;
		if (arx < obj->arx)
		{
			direction = true;
		}
		else
		{
			direction = false;
		}
		if ((obj->arx > this->right() - 20 && obj->arx < this->left() + 20) || (obj->arx > this->arx - 20 && obj->arx < this->arx + 20))
			Stand();
		else
			Attack();

		//if (obj->GetAttack())
		//{
		//	blood--;
		//	GameSound::getInstance()->play(BOSS_HURT_MUSIC);
		//}
	}
	if (obj->collType == CollApple)
	{
		blood--;
		GameSound::getInstance()->play(JAFAR_HURT_MUSIC);
		if (blood == 0)
		{
			Die();
			status = _BossStatus::DIE;
			return;
		}
	}
}

void Boss::Stand()
{
	switch (status)
	{
	case _BossStatus::STANDING:
		break;
	default:
	{
			   status = _BossStatus::STANDING;
			   if (typeBoss == 0)
				   image->setFrame(0, 0);
			   else
				   image->setFrame(8, 8);
			   break;
	}
	}

}

void Boss::Attack()
{
	switch (status)
	{
	case _BossStatus::ATTACK:
	{
								if (typeBoss == 0)
								{
									if (image->getIndex() == 6 /*&& isCreate == false*/)
									{
										DWORD endCut = GetTickCount();
										if (endCut - startCut > 150)
										{
											startCut = GetTickCount();
											createStar();
										}
									}
									if (image->getIndex() == 6)
									{
										image->setFrame(6, 6);
										animation_rate = 1;
									}
								}
								else
								{
									if (image->getIndex() == 17 && isCreate == false)
									{
										createFire();
										isCreate = true;
									}
									if (image->isActionFinish())
										Stand();
									break;
								}
								break;
	}
	default:
	{
			   isCreate = false;
			   status = _BossStatus::ATTACK;
			   if (typeBoss == 0)
			   {
				   image->setFrame(0, 7);
				   animation_rate = 11;
			   }
			   else
			   {
				   image->setFrame(8, 18);
				   animation_rate = 6;
			   }
			   break;
	}
	}
}

void Boss::Die()
{
	Enemy::Die();
}

int Boss::getStatus()
{
	return status;
}

vector<BaseObject*>* Boss::GetList()
{
	return &list;
}

//list fire
void Boss::createFire()
{
	Fire* obj = new Fire();
	obj->setObjectFromID();
	obj->GetBoss(this);
	obj->y = (this->bottom() + this->top()) / 2 - 3;
	obj->vy = 1.0f;
	if (direction)
	{
		obj->x = this->right();
		obj->vx = 1.0f;
	}
	else
	{
		obj->x = this->left();
		obj->vx = -1.0f;
	}
	obj->direction = this->direction;
	obj->typeFire = 2;
	obj->LoadResources();
	list.push_back(obj);
}

void Boss::deleteFire(BaseObject* fire)
{
	for (int i = 0; i < list.size();)
	{
		if (list.at(i) == fire)
		{
			list.erase(list.begin() + i);
			delete fire;
			fire = nullptr;
			return;
		}
		else
			i++;
	}
}

//list star
void Boss::createStar()
{
	Star* obj = new Star();
	obj->setObjectFromID();
	obj->GetBoss(this);
	obj->y = (this->bottom() + this->top()) / 2 - 3;
	if (direction)
		obj->x = this->right() + 2;
	else
		obj->x = this->left() - 2;
	obj->direction = !this->direction;
	obj->LoadResources();
	list.push_back(obj);
}

void Boss::deleteStar(BaseObject* star)
{
	for (int i = 0; i < list.size();)
	{
		if (list.at(i) == star)
		{
			list.erase(list.begin() + i);
			delete star;
			star = nullptr;
			return;
		}
		else
			i++;
	}
}

int Boss::getTypeObj()
{
	return typeBoss;
}


Boss::~Boss()
{}
