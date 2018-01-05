#ifndef _COLLISION_H
#define _COLLISION_H

#include <algorithm>
#include "BaseObject.h"

#define Max(a,b) a>b? a:b
#define Min(a,b) a>b? b:a
#define GameTime 4

class Collision
{
public:
	//contructor of SweptAABB
	Collision();

	//check collision between 2 BaseObject(retangle)
	static float sweptAABB(BaseObject* b1, BaseObject* b2, float& normalx, float& normaly);
	static void ExceptionalCase(BaseObject* b1, BaseObject* b2, float& normalx, float& normaly, float& collisionTime);

	//check broad-phasing
	static BaseObject* GetSweptBroadphaseBaseObject(BaseObject* b);

	//check AABB
	static bool AABBCheck(BaseObject* b1, BaseObject* b2);

	//check collision
	static void CheckCollision(BaseObject* b1, BaseObject* b2);
	static void PreventMove(BaseObject* b1, BaseObject* b2, float normalx, float normaly);
	static void CollisionLine(BaseObject* b1, BaseObject* b2, float normalx, float normaly);
	
	//destructor of SweptAABB
	~Collision();
};

#endif