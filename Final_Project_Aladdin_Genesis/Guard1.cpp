#include "Guard1.h"
#define GUARDS_XMLFILEPATH "Xml/Guard1.xml"

//contructor of Guard1 class
Guard1::Guard1()
{
	objType = OBJGuard1;
}

//init object
void Guard1::LoadResources()
{
	arx = x + 20;
	ary = y + 67;

	status = _Guard1Status::STANDING;
	animation_rate = 10;
	xmlFilePath = GUARDS_XMLFILEPATH;
	vx = 0;
	vy = 0;
	blood = 2;

	image = new Sprite(TextureManager::GetInstance()->GetGuardsTexture(), 14, 14);
}

//process input
void Guard1::ProcessInput()
{
	if (isDie)
	{
		Die();
		return;
	}

	if (this->arx < limx_left + 10 && vx < 0 || this->arx > limx_right - 10 && vx > 0)
		Stand();

	switch (status)
	{
	case _Guard1Status::ATTACK:
		Attack();
		break;
	case _Guard1Status::RUNNING:
		Run();
		break;
	case _Guard1Status::HURT:
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
void Guard1::changeFrameSize(BaseObject*obj)
{
	if (obj->collType == CollAladdin)
	{
		x -= 200;
		w += 400;
	}
}

void Guard1::resetFrameSize(BaseObject*obj)
{
	if (obj->collType == CollAladdin)
	{
		x += 200;
		w -= 400;
	}
}

//collision
void Guard1::OnCollision(BaseObject* obj, float normalx, float normaly)
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
void Guard1::OnInterSerct(BaseObject* obj)
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
		status = _Guard1Status::STANDING;
		Hurt();
	}
	if (obj->collType == CollAladdin)
	{
		if (this->arx > limx_left && this->arx < limx_right)
		{
			if (Aladdin::GetInstance()->getStatus() == _AladdinStatus::CUTTING)
			{
				if ((obj->direction && obj->right() > this->left() && obj->arx < this->arx) || (!obj->direction && obj->left()<this->right() && obj->arx>this->arx))
				{
					Hurt();
				}
			}
			else if (status != _Guard1Status::HURT)
			{
				if (obj->arx < this->arx)
					direction = true;
				else
					direction = false;
				if (this->arx - 30 <= obj->arx && obj->arx <= this->arx + 30)
					Attack();
				else if (this->arx - 200 <= obj->arx && obj->arx <= this->arx + 200)
					Run();
				else
					Stand();
			}
			if (this->arx < limx_left + 10 && vx < 0 || this->arx > limx_right - 10 && vx > 0)
				Stand();
		}
	}
}

//action of Guard1
void Guard1::Stand()
{
	switch (status)
	{
	case _Guard1Status::STANDING:
		break;
	default:
	{
			   /*if (status == _Guard1Status::HURT && !image->isActionFinish())
				   break;*/
			   status = _Guard1Status::STANDING;
			   image->setFrame(14, 14);
			   animation_rate = 10;
			   vx = 0;
			   break;
	}
	}
}

void Guard1::Run()
{
	switch (status)
	{
	case _Guard1Status::RUNNING: /*case _Guard1Status::HURT:*/
		break;
	default:
	{
			   status = _Guard1Status::RUNNING;
			   image->setFrame(0, 7);
			   animation_rate = 10;
			   if (direction)
				   vx = -0.5f;
			   else
				   vx = 0.5f;
			   break;
	}
	}
}

void Guard1::Attack()
{
	switch (status)
	{
	case _Guard1Status::ATTACK: /*case _Guard1Status::HURT:*/
		break;
	default:
	{
			   status = _Guard1Status::ATTACK;
			   image->setFrame(8, 13);
			   animation_rate = 15;
			   vx = 0;
			   break;
	}
	}
}

void Guard1::Hurt()
{
	switch (status)
	{
	case _Guard1Status::HURT:
	{
								if (image->isActionFinish())
									Stand();
								break;
	}
	default:
	{
			   status = _Guard1Status::HURT;
			   image->setFrame(15, 22);
			   animation_rate = 15;
			   vx = 0;
			   blood--;
			   if (blood == 1)
				   GameSound::getInstance()->play(GUARD_HIT_MUSIC);
			   if (blood == 0)
			   {
				   Die();
				   status = _Guard1Status::DIE;
			   }
			   break;
	}
	}
}

void Guard1::Die()
{
	Enemy::Die();
}

//get status aladdin
int Guard1::getStatus()
{
	return status;
}

//destructor of Guard1 class
Guard1::~Guard1()
{}
