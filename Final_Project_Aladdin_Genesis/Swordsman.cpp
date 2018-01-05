#include "Swordsman.h"
#define SWORDSMAN_XMLFILEPATH "Xml/Swordsman.xml"

//contructor of Swordsman class
Swordsman::Swordsman()
{
	objType = OBJSwordsman;
}

//init object
void Swordsman::LoadResources()
{
	arx = x + 25;
	ary = y + 81;

	status = _SwordsmanStatus::STANDING;
	animation_rate = 10;
	isCreateSword = false;
	typeThrow = false;
	xmlFilePath = SWORDSMAN_XMLFILEPATH;
	vx = 0;
	vy = 0;

	Enemy::LoadResources();
	image = new Sprite(TextureManager::GetInstance()->GetCivilianEnemiesTexture(), 0, 4);
}

//process input
void Swordsman::ProcessInput()
{
	if (isDie)
	{
		Die();
		return;
	}
	
	switch (status)
	{
	case _SwordsmanStatus::THROWING:
		Throw();
		break;
	default:
		Stand();
		break;
	}

}

//change and reset frame size
void Swordsman::changeFrameSize(BaseObject *obj)
{
	if (obj->collType == CollAladdin)
	{
		x -= 200;
		w += 400;
		h += 100;
	}
}

void Swordsman::resetFrameSize(BaseObject *obj)
{
	if (obj->collType == CollAladdin)
	{
		x += 200;
		w -= 400;
		h -= 100;
	}
}

//collision
void Swordsman::OnCollision(BaseObject* obj, float normalx, float normaly)
{}

//interserct
void Swordsman::OnInterSerct(BaseObject* obj)
{
	if (obj->collType == CollAladdin)
	{
		if (obj->arx < this->arx)
			direction = false;
		else
			direction = true;
		if (this->left() - 120 <= obj->arx&&obj->arx <= this->right() + 120)
		{
			typeThrow = true;
			Throw();
		}
		else if (this->left() - 200 <= obj->arx&&obj->arx <= this->right() + 200)
		{
			typeThrow = false;
			Throw();
		}
		else
			Stand();
	}
	if (obj->collType == CollApple || obj->objType == OBJSpittle)
	{
		/*Die();
		status = _SwordsmanStatus::DIE;*/
	}
	if (obj->collType == CollAladdin && Aladdin::GetInstance()->getStatus()==_AladdinStatus::CUTTING)
	{
		if (obj->direction && obj->right() > this->left() && obj->arx<this->arx)
		{
			Die();
			status = _SwordsmanStatus::DIE;
		}
		if (!obj->direction && obj->left()<this->right() && obj->arx>this->arx)
		{
			Die();
			status = _SwordsmanStatus::DIE;
		}
	}
}

//action of Swordsman
void Swordsman::Stand()
{
	switch (status)
	{
	case _SwordsmanStatus::STANDING:
		break;
	default:
	{
			   status = _SwordsmanStatus::STANDING;
			   image->setFrame(0, 4);
			   animation_rate = 10;
			   break;
	}
	}
}

void Swordsman::Throw()
{
	switch (status)
	{
	case _SwordsmanStatus::THROWING:
	{
				 if (image->getIndex() == 8 && isCreateSword == false)
				 {
					 createSword();
					 isCreateSword = true;
				 }
				 if (image->getIndex() != 8)
					 isCreateSword = false;
				 break;
	}
	default:
	{
			   status = _SwordsmanStatus::THROWING;
			   image->setFrame(5, 10);
			   animation_rate = 10;
			   isCreateSword = false;
			   break;
	}
	}
}

void Swordsman::Die()
{
	Enemy::Die();
}

//get status aladdin
int Swordsman::getStatus()
{
	return status;
}

//get list jar
vector<BaseObject*>* Swordsman::GetList()
{
	return &listSword;
}

//create apple
void Swordsman::createSword()
{
	Sword* obj = new Sword();
	obj->setObjectFromID();
	obj->GetSwordsman(this);
	obj->y = (this->bottom() + this->top()) / 2 - 3;
	if (typeThrow)
	{
		obj->vy = 0;
		if (direction)
		{
			obj->x = this->right();
			obj->vx = 2.0f;
		}
		else
		{
			obj->x = this->left();
			obj->vx = -2.0f;
		}
	}
	else
	{
		obj->vy = -2.5f;
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
	}
	obj->direction = this->direction;
	obj->LoadResources();
	listSword.push_back(obj);
}

void Swordsman::deleteSword(BaseObject* sword)
{
	for (int i = 0; i < listSword.size();)
	{
		if (listSword.at(i) == sword)
		{
			listSword.erase(listSword.begin() + i);
			delete sword;
			sword = nullptr;
		}
		else
			i++;
	}
}

//destructor of Swordsman class
Swordsman::~Swordsman()
{}
