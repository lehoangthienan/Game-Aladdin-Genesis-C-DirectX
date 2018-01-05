#ifndef _GUARD2_H
#define _GUARD2_H

#include "Enemy.h"

//status of Guard2
namespace _Guard2Status
{
	enum Guard2Status
	{
		RUNNING,
		STANDING,
		CUTTING_1,
		CUTTING_2,
		HURT,
		PROVOKE,
		BE_BURN,
		DIE
	};
}

class Guard2 : public Enemy
{
private:
	//Số lượng máu của guard 1
	int blood;
	_Guard2Status::Guard2Status status;
	bool isBurn;

public:
	//contructor of Guard2 class
	Guard2();

	//init object
	void LoadResources();

	//process input
	void ProcessInput();

	//collision
	void OnCollision(BaseObject* obj, float normalx, float normaly);
	//interserct
	void OnInterSerct(BaseObject* obj);

	//action of Guard2
	void Cut();
	void Run();
	void Stand();
	void Hurt();
	void Be_Burn();
	void Provoke();
	void Die();

	//get status aladdin
	int getStatus();

	//change and reset frame size
	void changeFrameSize(BaseObject*obj);
	void resetFrameSize(BaseObject*obj);

	//destructor of Guard2 class
	~Guard2();
};

#endif