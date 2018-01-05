#include "Camel.h"
#define CAMEL_XMLFILEPATH "Xml/Camel.xml"

//contructor of Camel class
Camel::Camel()
{
	objType = OBJCamel;
	camel_image = NULL;
}

void Camel::setObjectFromID()
{
	collType = CollCamel;
}

//init object
void Camel::LoadResources()
{
	arx = x + 21;
	ary = y + 38;
	status = LIE;
	direction = true;
	animation_rate = 10;
	isDead = false;
	normalx = 0.0f;
	normaly = 0.0f;
	vx = 0;
	vy = 0;
	isCreateSpittle = false;

	camel_image = new Sprite(TextureManager::GetInstance()->GetCamelTexture(), 0, 0);
}

//process input
void Camel::ProcessInput()
{
	switch (status)
	{
	case SPIT:
		Spit();
		break;
	default:
		Lie();
		break;
	}
}

//sprite redering
void Camel::Render(int Delta)
{
	//update aladdin position
	arx += vx * Delta;
	ary += vy * Delta;

	//draw sprite
	camel_image->Render(CAMEL_XMLFILEPATH, x, y, w, h, arx, ary, direction, 0);

	//install frame per second (animate rate)
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / animation_rate)
	{
		camel_image->Next();
		last_time = now;
	}
}

//collision
void Camel::OnCollision(BaseObject* obj, float normalx, float normaly)
{
	if (normaly == -1.0f)
		Spit();
}

//interserct
void Camel::OnInterSerct(BaseObject* obj)
{}

//action of camel
void Camel::Lie()
{
	switch (status)
	{
	case LIE:
		break;
	default:
	{
			   status = LIE;
			   camel_image->setFrame(0, 0);
			   break;
	}
	}
}

void Camel::Spit()
{
	switch (status)
	{
	case SPIT:
	{

				 if (camel_image->getIndex() == 5 && isCreateSpittle == false)
				 {
					 GameSound::getInstance()->play(CAMEL_MUSIC);

					 createSpittle();
					 isCreateSpittle = true;
				 }
				 if (camel_image->isActionFinish())
					 Lie();
				 break;
	}
	default:
	{
			   status = SPIT;
			   camel_image->setFrame(0, 6);
			   animation_rate = 17;
			   isCreateSpittle = false;
			   break;
	}
	}
}

//get status aladdin
int Camel::getStatus()
{
	return status;
}

//get aladdin direction
bool Camel::getDirection()
{
	return direction;
}

//get list jar
vector<BaseObject*>* Camel::GetList()
{
	return &listSpittle;
}

//create apple
void Camel::createSpittle()
{
	Spittle* obj = new Spittle();
	obj->setObjectFromID();
	obj->GetCamel(this);
	obj->y = (this->bottom() + this->top()) / 2 - 3;
	obj->vy = 0;
	if (direction)
	{
		obj->x = this->right() - 20;
		obj->vx = 1.0f;
	}
	else
	{
		obj->x = this->left() + 20;
		obj->vx = -1.0f;
	}
	obj->direction = this->direction;
	obj->LoadResources();
	listSpittle.push_back(obj);
}

void Camel::deleteSpittle(BaseObject* spittle)
{
	for (int i = 0; i < listSpittle.size(); i++)
	{
		if (listSpittle.at(i) == spittle)
		{
			listSpittle.erase(listSpittle.begin() + i);
			delete spittle;
			spittle = nullptr;
		}
	}
}


//destructor of Camel class
Camel::~Camel()
{
	if (camel_image != NULL){ delete camel_image; camel_image = nullptr; }
}
