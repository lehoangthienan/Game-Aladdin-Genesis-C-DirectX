#include "JarThrower.h"
#define JARTHROWER_XMLFILEPATH "Xml/JarThrower.xml"

//contructor of JarThrower class
JarThrower::JarThrower()
{
	objType = OBJJarThrower;
}

//init object
void JarThrower::LoadResources()
{
	arx = x;
	ary = y;
	
	status = _JarThrowerStatus::NOTMOVING;
	animation_rate = 15;
	isCreateJar = false;
	xmlFilePath = JARTHROWER_XMLFILEPATH;
	vx = 0;
	vy = 0;

	Enemy::LoadResources();
	image = new Sprite(TextureManager::GetInstance()->GetCivilianEnemiesTexture(), 0, 0);
}

//process input
void JarThrower::ProcessInput()
{
	if (isDie)
	{
		Die();
		return;
	}

	switch (status)
	{
	case _JarThrowerStatus::THROWING:
		Throw();
		break;
	default:
		Move();
		break;
	}
}

//change and reset frame size
void JarThrower::changeFrameSize(BaseObject *obj)
{
	if (obj->collType == CollAladdin)
	{
		h += 200;
		w += 50;
		x -= 25;
	}
}

void JarThrower::resetFrameSize(BaseObject *obj)
{
	if (obj->collType == CollAladdin)
	{
		h -= 200;
		w -= 50;
		x += 25;
	}
}

//collision
void JarThrower::OnCollision(BaseObject* obj, float normalx, float normaly)
{}

//interserct
void JarThrower::OnInterSerct(BaseObject* obj)
{
	if (obj->collType == CollAladdin)
	{
		if (Aladdin::GetInstance()->getStatus() == _AladdinStatus::CUTTING)
		{
			if (obj->bottom() > this->top() && obj->top()<this->bottom())
			{
				if ((obj->direction && obj->right() > this->left() && obj->arx < this->arx) || (!obj->direction && obj->left()<this->right() && obj->arx>this->arx))
				{
					Die();
					status = _JarThrowerStatus::DIE;
					return;
				}
			}
		}
		Throw();
	}
	if (obj->collType == CollApple)
	{
		Die();
		status = _JarThrowerStatus::DIE;
		return;
	}
}

//action of JarThrower
void JarThrower::Move()
{
	switch (status)
	{
	case _JarThrowerStatus::NOTMOVING:
		break;
	default:
	{
			   status = _JarThrowerStatus::NOTMOVING;
			   image->setFrame(0, 0);
			   animation_rate = 15;
			   break;
	}
	}
}

void JarThrower::Throw()
{
	switch (status)
	{
	case _JarThrowerStatus::THROWING:
	{
					 if (image->getIndex() == 7 && isCreateJar == false)
					 {
						 createJar();
						 isCreateJar = true;
					 }
					 if (image->isActionFinish())
						 Move();
					 break;
	}
	default:
	{
			   status = _JarThrowerStatus::THROWING;
			   image->setFrame(1, 10);
			   animation_rate = 10;
			   isCreateJar = false;
			   break;
	}
	}
}

void JarThrower::Die()
{
	Enemy::Die();
}

//get status aladdin
int JarThrower::getStatus()
{
	return status;
}

//get list jar
vector<BaseObject*>* JarThrower::GetList()
{
	return &listJar;
}

//create apple
void JarThrower::createJar()
{
	Jar* obj = new Jar();
	obj->setObjectFromID();
	obj->GetJarThrower(this);
	obj->y = this->bottom() - 18;
	obj->vy = 0;
	if (direction)
	{
		obj->x = this->right() - 18;
		obj->vx = 0.2f;
	}
	else
	{
		obj->x = this->left() + 18;
		obj->vx = -0.2f;
	}
	obj->direction = this->direction;
	obj->LoadResources();
	listJar.push_back(obj);
}

void JarThrower::deleteJar(BaseObject* jar)
{
	for (int i = 0; i < listJar.size(); i++)
	{
		if (listJar.at(i) == jar)
		{
			listJar.erase(listJar.begin() + i);
			delete jar;
			jar = NULL;
		}
	}
}

//destructor of JarThrower class
JarThrower::~JarThrower()
{

}
