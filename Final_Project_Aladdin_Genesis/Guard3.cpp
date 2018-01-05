#include "Guard3.h"
#define Guard3_XMLFILEPATH "Xml/Guard3.xml"

//contructor of Guard3 class
Guard3::Guard3()
{
	objType = OBJGuard3;
}

//init object
void Guard3::LoadResources()
{
	arx = x + 21;
	ary = y + 50;

	status = _Guard3Status::STANDING;
	animation_rate = 10;
	xmlFilePath = Guard3_XMLFILEPATH;
	vx = 0;
	vy = 0;
	blood = 2;
	start_waiteat = GetTickCount();

	image = new Sprite(TextureManager::GetInstance()->GetGuardsTexture(), 63, 63);
}

//process input
void Guard3::ProcessInput()
{
	if (isDie)
	{
		Die();
		return;
	}
	
	if (this->arx < limx_left + 20 && vx < 0 || this->arx > limx_right - 20 && vx > 0)
		Stand();

	switch (status)
	{		
	case _Guard3Status::EAT:
		Eat();
		break;
	case _Guard3Status::THROWING:
		Throw();
		break;
	case _Guard3Status::RUNNING:
		Run();
		break;
	case _Guard3Status::HURT:
		Hurt();
		break;
	default:
		Stand();
		break;
	}

	//simulate fall down (gravity)
	//vy += 0.1f;
}

//change and reset frame size
void Guard3::changeFrameSize(BaseObject*obj)
{
	if (obj->collType == CollAladdin)
	{
		x -= 200;
		w += 400;
	}
}

void Guard3::resetFrameSize(BaseObject*obj)
{
	if (obj->collType == CollAladdin)
	{
		x += 200;
		w -= 400;
	}
}

//collision
void Guard3::OnCollision(BaseObject* obj, float normalx, float normaly)
{
	switch (obj->collType)
	{
	case CollGround:
		Collision::PreventMove(this, obj, normalx, normaly);
		break;
	case CollStair: case CollLine:
		Collision::CollisionLine(this, obj, normalx, normaly);
		break;
	}
}

//interserct
void Guard3::OnInterSerct(BaseObject* obj)
{
	/*if (obj->collType == CollStair)
	{
		if (ary != obj->top())
		{
			if (vx != 0)
				vy = -0.5f;
			normaly = -1.0f;
		}
		else if (ary == obj->top() && vy < 0 && vy > -0.5)
			vy = 0.1f;
	}*/
	if (obj->collType == CollApple || obj->objType == OBJSpittle)
	{
		status = _Guard3Status::STANDING;
		Hurt();
	}
	if (obj->collType == CollAladdin)
	{
		if (this->arx > limx_left && this->arx < limx_right)
		{
			if (Aladdin::GetInstance()->getStatus() == _AladdinStatus::CUTTING && !Aladdin::GetInstance()->isCutted)
			{
				if ((obj->direction && obj->right() > this->left() && obj->arx < this->arx) || (!obj->direction && obj->left()<this->right() && obj->arx>this->arx))
				{
					Aladdin::GetInstance()->isCutted = true;
					status = _Guard3Status::STANDING;
					Hurt();
					return;
				}
			}
			if (status != _Guard3Status::HURT && status != _Guard3Status::EAT)
			{
				if (obj->arx < this->arx)
					direction = true;
				else
					direction = false;
				if (this->arx - 150 <= obj->arx && obj->arx <= this->arx + 150)
					Throw();
				else if (this->arx - 200 <= obj->arx&&obj->arx <= this->arx + 200)
					Run();
				else
					Stand();
			}
			if (this->arx < limx_left + 20 && vx < 0 || this->arx > limx_right - 20 && vx > 0)
				Stand();
		}
	}
}

//action of Guard3
void Guard3::Stand()
{
	switch (status)
	{
	case _Guard3Status::STANDING:
	{
									DWORD  end_waiteat = GetTickCount();
									if (end_waiteat - start_waiteat > 5000)
									{
										Eat();
										start_waiteat = end_waiteat;
									}
									break;
	}
	default:
	{
			   status = _Guard3Status::STANDING;
			   image->setFrame(63, 63);
			   animation_rate = 1;
			   vx = 0;
			   start_waiteat = GetTickCount();
			   break;
	}
	}
}

void Guard3::Run()
{
	switch (status)
	{
	case _Guard3Status::RUNNING:
		break;
	default:
	{
			   status = _Guard3Status::RUNNING;
			   image->setFrame(78, 85);
			   animation_rate = 10;
			   if (direction)
				   vx = -0.5f;
			   else
				   vx = 0.5f;
			   break;
	}
	}
}

void Guard3::Throw()
{
	switch (status)
	{
	case _Guard3Status::THROWING:
	{
									if (image->getIndex() == 88 && isCreateSword == false)
									{
										animation_rate = 20;
										createSword();
										isCreateSword = true;
									}
									if (image->getIndex() != 88)
									{
										animation_rate = 7;
										isCreateSword = false;
									}
									break;

	}
	default:
	{
			   status = _Guard3Status::THROWING;
			   image->setFrame(86, 90);
			   animation_rate = 7;
			   vx = 0;
			   isCreateSword = false;
			   break;
	}
	}
}

void Guard3::Hurt()
{
	switch (status)
	{
	case _Guard3Status::HURT:
	{
								if (image->getIndex() == 96)
									animation_rate = 1;
								if (image->getIndex() == 97)
									animation_rate = 10;
								if (image->isActionFinish())
									Stand();
								break;
	}
	default:
	{
			   status = _Guard3Status::HURT;
			   image->setFrame(91, 97);
			   animation_rate = 10;
			   vx = 0;
			   blood--;
			   if (blood==1)
					GameSound::getInstance()->play(GUARD_HIT_MUSIC);

			   if (blood == 0)
			   {
				   Die();
				   status = _Guard3Status::DIE;
			   }
			   break;
	}
	}
}

void Guard3::Eat()
{
	switch (status)
	{
	case _Guard3Status::EAT:
	{
							   if (image->getIndex() == 75 && image->isActionFinish())
								   Stand();
							   break;
	}
	default:
	{
			   status = _Guard3Status::EAT;
			   image->setFrame(71, 77);
			   image->setIndex(75);
			   animation_rate = 10;
			   vx = 0;
			   break;
	}
	}
}

void Guard3::Die()
{
	Enemy::Die();
}

//get status aladdin
int Guard3::getStatus()
{
	return status;
}

//get list jar
vector<BaseObject*>* Guard3::GetList()
{
	return &listSword;
}

//create apple
void Guard3::createSword()
{
	Sword* obj = new Sword();
	obj->setObjectFromID();
	obj->GetGuard3(this);
	obj->y = (this->bottom() + this->top()) / 2 - 3;
	obj->vy = -0.5f;
	if (!direction)
	{
		obj->x = this->right();
		obj->vx = 2.5f;
	}
	else
	{
		obj->x = this->left();
		obj->vx = -2.5f;
	}
	obj->direction = this->direction;
	obj->LoadResources();
	listSword.push_back(obj);
}

void Guard3::deleteSword(BaseObject* sword)
{
	for (int i = 0; i < listSword.size(); i++)
	{
		if (listSword.at(i) == sword)
		{
			listSword.erase(listSword.begin() + i);
			delete sword;
			sword = nullptr;
		}
	}
}

//destructor of Guard3 class
Guard3::~Guard3()
{}
