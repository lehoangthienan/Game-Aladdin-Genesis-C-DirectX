#include "FireCarpet.h"

//contructor of FireCarpet class
FireCarpet::FireCarpet()
{
	objType = OBJFireCarpet;
	collType = CollFireCarpet;
}

//init object
void FireCarpet::LoadResources()
{
	isDie = false;
	isDead = false;
	start_delay = GetTickCount();
}

//process input
void FireCarpet::ProcessInput()
{}

//change and reset frame size
void FireCarpet::changeFrameSize(BaseObject*obj)
{
	if (obj->objType == OBJGuard2)
	{
		w += 20;
		x -= 10;
	}
}

void FireCarpet::resetFrameSize(BaseObject*obj)
{
	if (obj->objType == OBJGuard2)
	{
		w -= 20;
		x += 10;
	}
}

//collision
void FireCarpet::OnCollision(BaseObject* obj, float normalx, float normaly)
{}

//interserct
void FireCarpet::OnInterSerct(BaseObject* obj)
{
	if (obj->collType == CollAladdin && obj->ary == this->top())
	{
		if (obj->arx > this->left() && obj->arx<this->right())
		{
			DWORD end_delay = GetTickCount();
			if (end_delay - start_delay > 500)
			{
				GameSound::getInstance()->play(FIRE_MUSIC);
				createFire(obj);
				start_delay = end_delay;
			}
		}

	}
}

//get status aladdin
int FireCarpet::getStatus()
{
	return 0;
}

//get list jar
vector<BaseObject*>* FireCarpet::GetList()
{
	return &listFire;
}

//create apple
void FireCarpet::createFire(BaseObject*obj)
{
	Fire* fire = new Fire();
	fire->setObjectFromID();
	fire->GetFireCarpet(this);
	fire->y = obj->ary;
	/*if (obj->arx < this->left())
		fire->x = this->left() + 24;
	else if (obj->arx>this->right())
		fire->x = this->right() - 24;
	else*/
		fire->x = obj->arx - 24;
	fire->typeFire = 1;
	fire->LoadResources();
	listFire.push_back(fire);
}

void FireCarpet::deleteFire(BaseObject* sword)
{
	for (int i = 0; i < listFire.size(); i++)
	{
		if (listFire.at(i) == sword)
		{
			listFire.erase(listFire.begin() + i);
			delete sword;
			sword = nullptr;
		}
	}
}

//destructor of FireCarpet class
FireCarpet::~FireCarpet()
{}
