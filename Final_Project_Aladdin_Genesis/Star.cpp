#include "Star.h"


Star::Star()
{
	objType = OBJStar;
	star_image = NULL;
	isDead = false;
}

void Star::setObjectFromID()
{
	collType = CollStar;
}

//init object
void Star::LoadResources()
{
	arx = x + 14;
	ary = y + 6;

	status = _StarStatus::FLING;
	animation_rate = 15;
	isDead = false;
	normalx = 0.0f;
	normaly = 0.0f;
	xmlFilePath = STAR_XMLFILEPATH;

	star_image = new Sprite(TextureManager::GetInstance()->GetJafarTexture(), 24, 26);

}

//process input
void Star::ProcessInput()
{
	switch (status)
	{
	case _StarStatus::DESTROY:
		Destroy();
		break;
	default:
		Fly();
		break;
	}
}


//sprite redering
void Star::Render(int Delta)
{
	//update aladdin position
	arx += vx * Delta;
	ary += vy * Delta;

	//draw sprite
	star_image->Render(xmlFilePath, x, y, w, h, arx, ary, direction, 0);


	//install frame per second (animate rate)
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / animation_rate)
	{
		star_image->Next();
		last_time = now;
	}
}

//collision
void Star::OnCollision(BaseObject* obj, float normalx, float normaly)
{}

//interserct
void Star::OnInterSerct(BaseObject* obj)
{
	if (obj->collType == CollAladdin && !isDie)
	{
		if (this->arx > obj->left() && this->arx < obj->right())
		{
			obj->vx -= this->vx / 20;
			Destroy();
		}
	}
}

//action of Star
void Star::Fly()
{
	switch (status)
	{
	case _StarStatus::FLING:
	{
							   float max;
							   vx = ((Aladdin::GetInstance()->left() + Aladdin::GetInstance()->right()) / 2 - this->arx);
							   vy = ((Aladdin::GetInstance()->top() + Aladdin::GetInstance()->bottom()) / 2 - this->ary);
							   max = (abs(vx) > abs(vy)) ? abs(vx) : abs(vy);
							   vx = vx / max;
							   vy = vy / max;
							   break;
	}
	default:
	{
			   status = _StarStatus::FLING;
			   star_image->setFrame(24, 26);
			   animation_rate = 15;
			   break;
	}
	}
}

void Star::Destroy()
{
	switch (status)
	{
	case _StarStatus::DESTROY:
	{
								 if (star_image->isActionFinish())
								 {
									 vx = 0;
									 vy = 0;
									 isDead = true;
									 boss->deleteStar(this);
								 }
								 break;
	}
	default:
	{
			   status = _StarStatus::DESTROY;
			   xmlFilePath = DISAPPEAR_XMLFILEPATH;
			   star_image->setFrame(0, 2);
			   animation_rate = 7;
			   vx = 0;
			   vy = 0;
			   isDie = true;
			   break;
			   break;
	}
	}

}

//get status aladdin
int Star::getStatus()
{
	return status;
}

//get Star thrower
void Star::GetBoss(Boss *obj)
{
	boss = obj;
}

Star::~Star()
{
	if (star_image != NULL){ delete star_image; star_image = nullptr; }
}
