#ifndef _Fire_H
#define _Fire_H

#include "Enemy.h"
#include "FireCarpet.h"
#include "Boss.h"

class FireCarpet;
class Boss;

//status of Fire
namespace _FireStatus
{
	enum FireStatus
	{
		MOVING,
		DESTROY
	};
}

class Fire : public Enemy
{
private:
	//Số lượng máu của guard 1
	_FireStatus::FireStatus status;
	FireCarpet *fireCarpet;
	Boss *boss;

public:
	//loại của fire
	int typeFire;

	//contructor of Fire class
	Fire();

	//init object
	void LoadResources();

	//process input
	void ProcessInput();

	//collision
	void OnCollision(BaseObject* obj, float normalx, float normaly);
	//interserct
	void OnInterSerct(BaseObject* obj);

	//action of Fire
	void Move();
	void Destroy();

	//get status aladdin
	int getStatus();

	//get Fire Carpet
	void GetFireCarpet(FireCarpet *obj);
	//get Boss
	void GetBoss(Boss*obj);

	//change and reset frame size
	void changeFrameSize(BaseObject*obj);
	void resetFrameSize(BaseObject*obj);

	//destructor of Fire class
	~Fire();
};

#endif