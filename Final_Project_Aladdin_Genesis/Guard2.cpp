#include "Guard2.h"
#define GUARD2_XMLFILEPATH "Xml/Guard2.xml"

//contructor of Guard2 class
Guard2::Guard2()
{
	objType = OBJGuard2;
}

//init object
void Guard2::LoadResources()
{
	arx = x + 24;
	ary = y + 52;

	status = _Guard2Status::STANDING;
	animation_rate = 10;
	xmlFilePath = GUARD2_XMLFILEPATH;
	vx = 0;
	vy = 0;
	blood = 2;
	isBurn = false;

	image = new Sprite(TextureManager::GetInstance()->GetGuardsTexture(), 37, 37);
}

//process input
void Guard2::ProcessInput()
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
	case _Guard2Status::PROVOKE:
		Provoke();
		break;
	case _Guard2Status::BE_BURN:
		break;
	case _Guard2Status::CUTTING_1: case _Guard2Status::CUTTING_2:
		Cut();
		break;
	case _Guard2Status::RUNNING:
		Run();
		break;
	case _Guard2Status::HURT:
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
void Guard2::changeFrameSize(BaseObject*obj)
{
	if (obj->collType == CollAladdin)
	{
		x -= 250;
		w += 500;
	}
}

void Guard2::resetFrameSize(BaseObject*obj)
{
	if (obj->collType == CollAladdin)
	{
		x += 250;
		w -= 500;
	}
}

//collision
void Guard2::OnCollision(BaseObject* obj, float normalx, float normaly)
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
void Guard2::OnInterSerct(BaseObject* obj)
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
	if (obj->collType == CollFireCarpet)
	{
		if (obj->left() < this->arx && this->arx < obj->right())
		{
			Be_Burn();
			isBurn = true;
		}
		else
			isBurn = false;
	}
	if (obj->collType == CollApple || obj->objType == OBJSpittle)
		Hurt();
	if (obj->collType == CollAladdin)
	{
		if (this->arx > limx_left && this->arx < limx_right)
		{
			if (Aladdin::GetInstance()->getStatus() == _AladdinStatus::CUTTING)
			{
				if ((obj->direction && obj->right() > this->left() && obj->arx < this->arx) || (!obj->direction && obj->left()<this->right() && obj->arx>this->arx))
					Hurt();
			}
			else if (status != _Guard2Status::HURT)
			{
				if (obj->arx < this->arx)
					direction = true;
				else
					direction = false;
				if (!isBurn)
				{
					if (this->arx - 50 <= obj->arx && obj->arx <= this->arx + 50)
						Cut();
					else if (this->arx - 90 <= obj->arx&&obj->arx <= this->arx + 90)
						Provoke();
					else if (this->arx - 230 <= obj->arx&&obj->arx <= this->arx + 230)
						Run();
					else
						Stand();
				}
			}
			if (this->arx < limx_left + 20 && vx < 0 || this->arx > limx_right - 20 && vx > 0)
			{
				if (!isBurn)
				Stand();
			}
		}
	}
}

//action of Guard2
void Guard2::Stand()
{
	switch (status)
	{
	case _Guard2Status::STANDING:
		break;
	default:
	{
			   status = _Guard2Status::STANDING;
			   image->setFrame(37, 37);
			   animation_rate = 10;
			   vx = 0;
			   break;
	}
	}
}

void Guard2::Run()
{
	switch (status)
	{
	case _Guard2Status::RUNNING:
		break;
	default:
	{
			   status = _Guard2Status::RUNNING;
			   image->setFrame(23, 30);
			   animation_rate = 10;
			   if (direction)
				   vx = -0.5f;
			   else
				   vx = 0.5f;
			   break;
	}
	}
}

void Guard2::Cut()
{
	switch (status)
	{
	case _Guard2Status::CUTTING_2:
	{
								 srand(time(0));
								 if (image->isActionFinish() && rand() % 4 == 1)
								 {
									 status = _Guard2Status::CUTTING_1;
									 Cut();
								 }
								 break;
	}
	case _Guard2Status::CUTTING_1:
	{
								 if (image->isActionFinish())
								 {
									 if (image->getLastFrame() == 13)
									 {
										 status = _Guard2Status::CUTTING_2;
										 image->setFrame(37, 42);
										 animation_rate = 12;
										 vx = 0;
									 }
									 else
									 {
										 status = _Guard2Status::STANDING;
										 Cut();
									 }
								 }
								 break;
	}
	default:
	{
			   status = _Guard2Status::CUTTING_2;
			   image->setFrame(43, 47);
			   animation_rate = 12;
			   vx = 0;
			   break;
	}
	}
}

void Guard2::Hurt()
{
	switch (status)
	{
	case _Guard2Status::HURT:
	{
								if (image->isActionFinish())
									Stand();
								break;
	}
	default:
	{
			   status = _Guard2Status::HURT;
			   image->setFrame(48, 53);
			   animation_rate = 15;
			   vx = 0;
			   blood--;
			   if (blood == 1)
				   GameSound::getInstance()->play(GUARD_HIT_MUSIC);

			   if (blood == 0)
			   {
				   Die();
				   status = _Guard2Status::DIE;
			   }
			   break;
	}
	}
}

void Guard2::Be_Burn()
{
	switch (status)
	{
	case _Guard2Status::BE_BURN:
	{
								   if (direction)
									   vx = -0.1f;
								   else
									   vx = 0.1f;
								   break;
	}
	default:
	{
			   status = _Guard2Status::BE_BURN;
			   image->setFrame(54, 62);
			   animation_rate = 10;
			   break;
	}
	}
}

void Guard2::Provoke()
{
	switch (status)
	{
	case _Guard2Status::PROVOKE:
	{
								   if (image->isActionFinish() && image->getFirstFrame() == 31)
									   image->setFrame(33, 36);
								   break;
	}
	default:
	{
			   status = _Guard2Status::PROVOKE;
			   image->setFrame(31, 36);
			   animation_rate = 10;
			   vx = 0;
			   break;
	}
	}
}

void Guard2::Die()
{
	Enemy::Die();
}

//get status aladdin
int Guard2::getStatus()
{
	return status;
}

//destructor of Guard2 class
Guard2::~Guard2()
{}
