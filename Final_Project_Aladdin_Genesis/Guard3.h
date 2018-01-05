#ifndef _GUARD3_H
#define _GUARD3_H

#include "Enemy.h"
#include "Sword.h"

//status of Guard3
namespace _Guard3Status
{
	enum Guard3Status
	{
		RUNNING,
		STANDING,
		THROWING,
		HURT,
		EAT,
		DIE
	};
}

class Guard3 : public Enemy
{
private:
	//Số lượng máu của guard 1
	int blood;
	_Guard3Status::Guard3Status status;
	DWORD start_waiteat;

	vector<BaseObject*>listSword;
	bool isCreateSword;

public:
	//contructor of Guard3 class
	Guard3();

	//init object
	void LoadResources();

	//process input
	void ProcessInput();

	//collision
	void OnCollision(BaseObject* obj, float normalx, float normaly);
	//interserct
	void OnInterSerct(BaseObject* obj);

	//action of Guard3
	void Throw();
	void Run();
	void Stand();
	void Hurt();
	void Eat();
	void Die();

	//get status aladdin
	int getStatus();

	//handle sword
	void createSword();
	vector<BaseObject*>* GetList();
	void deleteSword(BaseObject* sword);

	//change and reset frame size
	void changeFrameSize(BaseObject*obj);
	void resetFrameSize(BaseObject*obj);


	//destructor of Guard3 class
	~Guard3();
};

#endif