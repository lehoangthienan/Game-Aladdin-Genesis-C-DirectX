#include "Theft.h"
#define Theft_XMLFILEPATH "Xml/Theft.xml"

//contructor of Theft class
Theft::Theft()
{
	objType = OBJTheft;
}

//init object
void Theft::LoadResources()
{
	arx = x + 18;
	ary = y + 39;

	status = _TheftStatus::STANDING;
	animation_rate = 10;
	xmlFilePath = Theft_XMLFILEPATH;
	vx = 0;
	vy = 0;

	image = new Sprite(TextureManager::GetInstance()->GetCivilianEnemiesTexture(), 59, 59);
}

//process input
void Theft::ProcessInput()
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
	case _TheftStatus::HIT:
		Hit();
		break;
	case _TheftStatus::RUNNING:
		Run();
		break;
	default:
		Stand();
		break;
	}

	//simulate fall down (gravity)
	//vy += 0.1f;
}

//change and reset frame size
void Theft::changeFrameSize(BaseObject*obj)
{
	if (obj->collType == CollAladdin)
	{
		x -= 100;
		w += 200;
	}
}

void Theft::resetFrameSize(BaseObject*obj)
{
	if (obj->collType == CollAladdin)
	{
		x += 100;
		w -= 200;
	}
}

//collision
void Theft::OnCollision(BaseObject* obj, float normalx, float normaly)
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
void Theft::OnInterSerct(BaseObject* obj)
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
		Die();
		status = _TheftStatus::DIE;
	}
	if (obj->collType == CollAladdin && this->left() > limx_left && this->right()<limx_right)
	{
		if (Aladdin::GetInstance()->getStatus() == _AladdinStatus::CUTTING)
		{
			if ((obj->direction && obj->right() > this->left() && obj->arx < this->arx) || (!obj->direction && obj->left()<this->right() && obj->arx>this->arx))
			{
				Die();
				status = _TheftStatus::DIE;
			}
		}
		else if (status != _TheftStatus::DIE)
		{
			if (obj->arx < this->arx)
				direction = false;
			else
				direction = true;
			if (this->arx - 20 <= obj->arx && obj->arx <= this->arx + 20)
				Hit();
			else if (this->arx - 100 <= obj->arx&&obj->arx <= this->arx + 100)
				Run();
			else
				Stand();
		}
		if (this->arx < limx_left + 20 && vx < 0 || this->arx > limx_right - 20 && vx > 0)
			Stand();
	}
}

//action of Theft
void Theft::Stand()
{
	switch (status)
	{
	case _TheftStatus::STANDING:
		break;
	default:
	{
			   status = _TheftStatus::STANDING;
			   image->setFrame(59, 59);
			   animation_rate = 1;
			   vx = 0;
			   break;
	}
	}
}

void Theft::Run()
{
	switch (status)
	{
	case _TheftStatus::RUNNING:
		break;
	default:
	{
			   status = _TheftStatus::RUNNING;
			   image->setFrame(69, 80);
			   animation_rate = 10;
			   if (direction)
				   vx = 0.1f;
			   else
				   vx = -0.1f;
			   break;
	}
	}
}

void Theft::Hit()
{
	switch (status)
	{
	case _TheftStatus::HIT:
		break;
	default:
	{
			   status = _TheftStatus::HIT;
			   image->setFrame(65, 68);
			   animation_rate = 10;
			   vx = 0;
			   break;
	}
	}
}

void Theft::Die()
{
	Enemy::Die();
}

//get status aladdin
int Theft::getStatus()
{
	return status;
}

//destructor of Theft class
Theft::~Theft()
{}
