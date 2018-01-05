#ifndef _THEFT_H
#define _THEFT_H

#include "Enemy.h"
#include "Sword.h"

//status of Theft
namespace _TheftStatus
{
	enum TheftStatus
	{
		RUNNING,
		STANDING,
		HIT,
		DIE
	};
}

class Theft : public Enemy
{
private:
	//Số lượng máu của guard 1
	int blood;
	_TheftStatus::TheftStatus status;

public:
	//contructor of Theft class
	Theft();

	//init object
	void LoadResources();

	//process input
	void ProcessInput();

	//collision
	void OnCollision(BaseObject* obj, float normalx, float normaly);
	//interserct
	void OnInterSerct(BaseObject* obj);

	//action of Theft
	void Hit();
	void Run();
	void Stand();
	void Die();

	//get status aladdin
	int getStatus();

	//change and reset frame size
	void changeFrameSize(BaseObject*obj);
	void resetFrameSize(BaseObject*obj);

	//destructor of Theft class
	~Theft();
};

#endif