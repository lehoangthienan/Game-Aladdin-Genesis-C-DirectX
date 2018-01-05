#include "Item.h"


Item::Item()
{
	image = NULL;
	xmlFilePath = "";
}

//set type collision from object's id
void Item::setObjectFromID()
{
	collType = CollItem;
}

//init object
void Item::LoadResources()
{
	status = NONACTIVED;
	animation_rate = 1;
	direction = true;
	isDead = false;
	isDie = false;
	isActive = false;
	normalx = 0.0f;
	normaly = 0.0f;
	vx = 0;
	vy = 0;
	start_wait = GetTickCount();
}

//process input
void Item::ProcessInput()
{
	switch (status)
	{
	case ACTIVED:
		Active();
		break;
	case NONACTIVED:
		NonActive();
		break;
	}
}

//sprite redering
void Item::Render(int Delta)
{
	//update aladdin position
	arx += vx * Delta;
	ary += vy * Delta;

	//draw sprite
	image->Render(xmlFilePath, x, y, w, h, arx, ary, direction, 0);

	//install frame per second (animate rate)
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / animation_rate)
	{
		image->Next();
		last_time = now;
	}
}

//collision
void Item::OnCollision(BaseObject* obj, float normalx, float normaly)
{}

//interserct
void Item::OnInterSerct(BaseObject* obj)
{
	if (obj->collType == CollAladdin&&status != ACTIVED)
		Active();
}

//action when item actived
void Item::Active()
{
	switch (status)
	{
	case ACTIVED:
	{
					//Thực hiện animation actived xong đặt isDead = true để xóa item ra khỏi danh sách
					if (image->isActionFinish())
						isDead = true;
					break;
	}
	default:
	{
			   status = ACTIVED;
			   xmlFilePath = ITEMACTIVED_XMLFILEPATH;
			   image->setImage(TextureManager::GetInstance()->GetItemActivedTexture());
			   image->setFrame(0, 3);
			   animation_rate = 10;
			   vy = 0;
			   vx = 0;
			   arx = (this->left() + this->right()) / 2;
			   ary = (this->top() + this->bottom()) / 2;
			   isDie = true;
			   isActive = true;
			   break;
	}
	}
}

void Item::NonActive()
{}

//get status item
int Item::getStatus()
{
	return status;
}

Item::~Item()
{
	if (image != NULL)
	{
		delete image;
		image = nullptr;
	}
}
