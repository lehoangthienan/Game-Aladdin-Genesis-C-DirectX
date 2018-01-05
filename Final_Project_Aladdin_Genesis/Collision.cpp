#include "Collision.h"

//contructor of Collision
Collision::Collision()
{}

//check collision between 2 BaseObject*(retangle)
float Collision::sweptAABB(BaseObject* b1, BaseObject* b2, float& normalx, float& normaly)
{
	//distance is the nearest between two BaseObject*
	float xInvEntry, yInvEntry;
	//distance is the farest between two BaseObject*
	float xInvExit, yInvExit;

	//find the distance between two BaseObject on near and far BaseObject's side
	//b1 chạy theo hướng từ trái sang phải
	if (b1->vx*GameTime > 0.0f)
	{
		xInvEntry = b2->left() - b1->right();
		xInvExit = b2->right() - b1->left();
	}
	//b1 chạy theo hướng từ phải sang trái (xInvEntry, xExit <= 0)
	else
	{
		xInvEntry = b2->right() - b1->left();
		xInvExit = b2->left() - b1->right();
	}

	//b1 chạy theo hướng từ trên xuống dưới
	if (b1->vy*GameTime > 0.0f)
	{
		yInvEntry = b2->top() - b1->bottom();
		yInvExit = b2->bottom() - b1->top();
	}
	//b1 chạy theo hướng từ dưới lên trên (yInvEntry, yExit <= 0)
	else
	{
		yInvEntry = b2->bottom() - b1->top();
		yInvExit = b2->top() - b1->bottom();
	}

	//find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;

	if (b1->vx*GameTime == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / (b1->vx*GameTime);
		xExit = xInvExit / (b1->vx*GameTime);
	}

	if (b1->vy*GameTime == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / (b1->vy*GameTime);
		yExit = yInvExit / (b1->vy*GameTime);
	}

	//find the earliest/lastest times of collision
	float entryTime = Max(xEntry, yEntry);
	float exitTime = Min(xExit, yExit);

	// if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		// Trả về thời gian bắt đầu va chạm
		return entryTime;
	}
}

//check broad-phasing
BaseObject* Collision::GetSweptBroadphaseBaseObject(BaseObject* b)
{
	BaseObject* broadphaseBaseObject = new BaseObject(0, 0, 0, 0);

	broadphaseBaseObject->x = b->vx*GameTime > 0 ? b->x : b->x + b->vx*GameTime;
	broadphaseBaseObject->y = b->vy*GameTime > 0 ? b->y : b->y + b->vy*GameTime;
	broadphaseBaseObject->w = b->vx*GameTime > 0 ? b->vx*GameTime + b->w : b->w - b->vx*GameTime;
	broadphaseBaseObject->h = b->vy*GameTime > 0 ? b->vy*GameTime + b->h : b->h - b->vy*GameTime;

	return broadphaseBaseObject;
}

//check AABB
bool Collision::AABBCheck(BaseObject* b1, BaseObject* b2)
{
	//return true if collision occur
	return !(b1->right()<b2->left() || b1->left()>b2->right() || b1->bottom()<b2->top() || b1->top()>b2->bottom());
}

//check 2 BaseObject* collised
void Collision::CheckCollision(BaseObject* b1, BaseObject* b2)
{
	//kiểm tra đã đặt lại kích thước box chưa
	bool isResetFrameSize = false;

	if (b1->isDie || b2->isDie || b1 == b2)
		return;

	b1->changeFrameSize(b2);
	b2->changeFrameSize(b1);

	if (AABBCheck(b1, b2))
	{
		b1->resetFrameSize(b2);
		b2->resetFrameSize(b1);
		isResetFrameSize = true;
		b1->OnInterSerct(b2);
		b2->OnInterSerct(b1);
	}

	if (!isResetFrameSize)
	{
		b1->resetFrameSize(b2);
		b2->resetFrameSize(b1);
	}

	if (b1->arx > b2->left() && b1->arx < b2->right() && b2->objType == OBJGround)
	{
		if (b2->top() - b1->ary <= b1->h * 1 / 2 && b2->top() - b1->ary > 0)
			b1->normaly = -1.0;
	}

	//broadphase là đối tượng trong tương lai của b1 (vị trí b1 ở frame sau)
	BaseObject* broadphase = GetSweptBroadphaseBaseObject(b1);
	if (AABBCheck(broadphase, b2))
	{
		float normalx, normaly;
		float collisionTime = sweptAABB(b1, b2, normalx, normaly);
		ExceptionalCase(b1, b2, normalx, normaly, collisionTime);

		//Cập nhật lại normalx, normaly
		if (normalx != 0)
			b1->normalx = normalx;
		if (normaly != 0)
			b1->normaly = normaly;

		//Sử lý va chạm b1 với b2, b2 với b1
		if (collisionTime < 1.0f)
		{
			b1->OnCollision(b2, normalx, normaly);
			b2->OnCollision(b1, normalx, normaly);
		}
	}

	delete broadphase;
}

//trường hợp ngoại lệ của va chạm, trả về collisionTime
void Collision::ExceptionalCase(BaseObject* b1, BaseObject* b2, float& normalx, float& normaly, float& collisionTime)
{

	if (b2->collType == CollCollarBeam || b2->collType == CollItem)
	{
		normaly = 0;
		normalx = 0;
		collisionTime = 1.0f;
		return;
	}

	if (b1->arx > b2->left() && b1->arx < b2->right())
	{
		if ((int)b1->ary >= (int)b2->top() && (int)b1->ary <= (int)b2->top() + 35 && b1->vy > 0)
		{
			normaly = -1.0f;
			normalx = 0;
			collisionTime = 0.0f;
			return;
		}
	}

	if (b1->top()<b2->bottom() - 30 && b1->bottom()>b2->top() + 30 && b2->collType == CollGround)
	{
		if (b1->right() >= b2->left() && b1->right() < b2->right() && b1->vx > 0 && b1->direction)
		{
			normalx = -1.0f;
			normaly = 0;
			collisionTime = 0.0f;
			return;
		}

		if (b1->left() <= b2->right() && b1->left() > b2->left() && b1->vx < 0 && !b1->direction)
		{
			normalx = 1.0f;
			normaly = 0;
			collisionTime = 0.0f;
			return;
		}
	}
}

//obj b1 là đối tượng di chuyển, obj b2 là đối tượng tĩnh
void Collision::PreventMove(BaseObject* b1, BaseObject* b2, float normalx, float normaly)
{
	if (b1->arx > b2->left() && b1->arx < b2->right())
	{
		if ((int)b1->ary == (int)b2->top() && b1->ary < b1->bottom() && b1->vy > 0)
		{
			b1->vy = 0;
			return;
		}
		if ((int)b1->ary >= (int)b2->top() && (int)b1->ary <= (int)b2->top() + 35 && b1->vy > 0)
		{
			b1->ary = b2->top();
			b1->vy = 0;
			return;
		}
	}

	//Xét va chạm theo phương ngang, bên trái bên phải obj1
	if (normalx != 0)
	{
			//obj1 va chạm phía bên TRÁI obj2
			if (normalx == -1.0f)
				b1->arx += b2->left() - b1->right();
			else //obj1 va chạm phía bên PHẢI obj2, cạnh phải obj2 - cạnh trái obj1 < 0 
				b1->arx += b2->right() - b1->left();
			b1->vx = 0;
	}

	//Xét va chạm theo phương dọc, bên trên bên dưới obj1
	if (normaly != 0)
	{
		if (normaly == -1.0f)
			b1->ary += b2->top() - b1->bottom();
		else
			b1->ary += b2->bottom() - b1->top() + 1;
		b1->vy = 0;
	}

}

void Collision::CollisionLine(BaseObject* b1, BaseObject* b2, float normalx, float normaly)
{

	if (b1->arx > b2->left() && b1->arx < b2->right())
	{
		if ((int)b1->ary == (int)b2->top() && b1->ary < b1->bottom() && b1->vy > 0)
		{
			b1->vy = 0;
			return;
		}
		if ((int)b1->ary >= (int)b2->top() && (int)b1->ary <= (int)b2->top() + 35 && b1->vy > 0)
		{
			b1->ary = b2->top();
			b1->vy = 0;
			return;
		}
	}

	if (normaly == -1.0f)
	{
		b1->ary += b2->top() - b1->bottom();
		b1->vy = 0;
	}
}

//destructor of Collision
Collision::~Collision()
{}
