#include "BloodBar.h"


//contructor of BloodBar class
BloodBar::BloodBar()
{
	bloodbar_image = NULL;
	this->x = 0;
	this->y = 0;
}

void BloodBar::setObjectFromID()
{}

//init object
void BloodBar::LoadResources()
{
	arx = x + 26;
	ary = y + 14;
	direction = true;
	animation_rate = 9;
	isDead = false;
	normalx = 0.0f;
	normaly = 0.0f;
	vx = 0;
	vy = 0;
	isBlink = 0;
	old_blood = Aladdin::GetInstance()->blood;
	startBlink = GetTickCount();

	bloodbar_image = new Sprite(TextureManager::GetInstance()->GetBloodBarTexture(), 1, 4);

	switch (old_blood)
	{
	case 1:
		bloodbar_image->setFrame(0, 0);
		break;
	case 2:
		bloodbar_image->setFrame(22, 23);
		break;
	case 3:
		bloodbar_image->setFrame(20, 21);
		break;
	case 4:
		bloodbar_image->setFrame(17, 19);
		break;
	case 5:
		bloodbar_image->setFrame(13, 16);
		break;
	case 6:
		bloodbar_image->setFrame(9, 12);
		break;
	case 7:
		bloodbar_image->setFrame(5, 8);
		break;
	}

}

//process input
void BloodBar::ProcessInput()
{
	if (isBlink != 0)
	{
		DWORD endBlink = GetTickCount();
		if (endBlink - startBlink > 350)
		{
			isBlink = isBlink % 2 + 1;
			startBlink = endBlink;
		}
	}
	if (old_blood != Aladdin::GetInstance()->blood)
	{
		switch (Aladdin::GetInstance()->blood)
		{
		case 1:
		{
				  bloodbar_image->setFrame(0, 0);
				  isBlink = 1;
				  animation_rate = 9;
				  break;
		}
		case 2:
		{
				  bloodbar_image->setFrame(22, 23);
				  isBlink = 1;
				  animation_rate = 9;
				  break;
		}
		case 3:
		{
				  bloodbar_image->setFrame(20, 21);
				  isBlink = 0;
				  animation_rate = 9;
				  break;
		}
		case 4:
		{
				  bloodbar_image->setFrame(17, 19);
				  isBlink = 0;
				  animation_rate = 9;
				  break;

		}
		case 5:
		{
				  bloodbar_image->setFrame(13, 16);
				  isBlink = 0;
				  animation_rate = 9;
				  break;
		}
		case 6:
		{
				  bloodbar_image->setFrame(9, 12);
				  isBlink = 0;
				  animation_rate = 9;
				  break;
		}
		case 7:
		{
				  bloodbar_image->setFrame(5, 8);
				  isBlink = 0;
				  animation_rate = 9;
				  break;
		}
		default:
		{
				  bloodbar_image->setFrame(1, 4);
				  isBlink = 0;
				  animation_rate = 9;
				  break;
		}
		}
		old_blood = Aladdin::GetInstance()->blood;
	}
	if (bloodbar_image->isActionFinish())
	{
		int firstframe, lastframe;
		firstframe = bloodbar_image->getFirstFrame();
		lastframe = bloodbar_image->getLastFrame();
		bloodbar_image->setFrame(lastframe, firstframe);
	}
}

//sprite redering
void BloodBar::Render(int Delta)
{
	//update aladdin position
	arx += vx * Delta;
	ary += vy * Delta;

	if (bloodbar_image->getIndex() > 0)
	{
		arx += 29;
		ary -= 8;
		bloodbar_image->Render(BLOODBAR_XMLFILEPATH, x, y, w, h, arx, ary, direction, isBlink);

		arx -= 29;
		ary += 8;
	}

	int currentIndex;
	currentIndex = bloodbar_image->getIndex();
	bloodbar_image->setIndex(0);

	//draw sprite
	bloodbar_image->Render(BLOODBAR_XMLFILEPATH, x, y, w, h, arx, ary, direction, isBlink);
	bloodbar_image->setIndex(currentIndex);

	//install frame per second (animate rate)
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / animation_rate)
	{
		bloodbar_image->Next();
		last_time = now;
	}
}

//collision
void BloodBar::OnCollision(BaseObject* obj, float normalx, float normaly)
{}

//interserct
void BloodBar::OnInterSerct(BaseObject* obj)
{}

//destructor of BloodBar class
BloodBar::~BloodBar()
{
	if (bloodbar_image != NULL){ delete bloodbar_image; bloodbar_image = nullptr; }
}
