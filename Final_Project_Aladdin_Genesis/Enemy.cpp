#include "Enemy.h"

//contructor of enemy class
Enemy::Enemy()
{
	image = NULL;
	xmlFilePath = "";
}

//set type collision from object's id
void Enemy::setObjectFromID()
{
	collType = CollEnemy;
}

//init object
void Enemy::LoadResources()
{
	direction = true;
	isDead = false;
	isDie = false;
	normalx = 0.0f;
	normaly = 0.0f;
}

//process input
void Enemy::ProcessInput()
{

}

//sprite redering
void Enemy::Render(int Delta)
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
void Enemy::OnCollision(BaseObject* obj, float normalx, float normaly)
{}

//interserct
void Enemy::OnInterSerct(BaseObject* obj)
{}

//get list object
vector<BaseObject*>* Enemy::GetList()
{
	return NULL;
}

//change and reset frame size
void Enemy::changeFrameSize(BaseObject*obj)
{}

void Enemy::resetFrameSize(BaseObject*obj)
{}

//action when enemy die
void Enemy::Die()
{
	//enemy rơi vào trạng thái chết
	if (!isDie)
	{
		xmlFilePath = ENEMYDIE_XMLFILEPATH;
		image->setImage(TextureManager::GetInstance()->GetEnemyDieTexture());
		image->setFrame(0, 7);
		animation_rate = 15;
		vy = 0;
		vx = 0;
		ary = (this->top() + this->bottom()) / 2;
		isDie = true;
	}
	else
	{
		//Thực hiện animation chết xong đặt isDead = true để xóa enemy ra khỏi danh sách
		if (image->isActionFinish())
			isDead = true;
	}
}

//get status of enemy
int Enemy::getStatus()
{
	return 0;
}

//destructor of enemy class
Enemy::~Enemy()
{
	if (image != NULL)
	{
		delete image;
		image = nullptr;
	}
}