#ifndef _GUARD1_H
#define _GUARD1_H

#include "Enemy.h"

//status of Guard1
namespace _Guard1Status
{
	enum Guard1Status
	{
		RUNNING,
		STANDING,
		ATTACK,
		HURT,
		DIE
	};
}

class Guard1 : public Enemy
{
private:
	//Số lượng máu của guard 1
	int blood;
	_Guard1Status::Guard1Status status;

public:
	//contructor of Guard1 class
	Guard1();

	//init object
	void LoadResources();

	//process input
	void ProcessInput();
	
	//collision
	void OnCollision(BaseObject* obj, float normalx, float normaly);
	//interserct
	void OnInterSerct(BaseObject* obj);

	//action of Guard1
	void Attack();
	void Run();
	void Stand();
	void Hurt();
	void Die();

	//get status aladdin
	int getStatus();

	//change and reset frame size
	void changeFrameSize(BaseObject*obj);
	void resetFrameSize(BaseObject*obj);

	//destructor of Guard1 class
	~Guard1();
};

#endif