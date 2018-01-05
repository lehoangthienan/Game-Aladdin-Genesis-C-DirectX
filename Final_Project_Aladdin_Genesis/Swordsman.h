#ifndef _SWORDSMAN_H
#define _SWORDSMAN_H

#include "Enemy.h"
#include "Sword.h"

//status of Swordsman
namespace _SwordsmanStatus
{
	enum SwordsmanStatus
	{
		STANDING,
		THROWING,
		DIE
	};
}

class Sword;

class Swordsman : public Enemy
{
private:
	_SwordsmanStatus::SwordsmanStatus status;
	vector<BaseObject*>listSword;
	bool isCreateSword, typeThrow;

public:
	//contructor of Swordsman class
	Swordsman();

	//init object
	void LoadResources();

	//process input
	void ProcessInput();

	//collision
	void OnCollision(BaseObject* obj, float normalx, float normaly);
	//interserct
	void OnInterSerct(BaseObject* obj);

	//action of Swordsman
	void Stand();
	void Throw();
	void Die();

	//get status Swordsman
	int getStatus();

	//handle sword
	void createSword();
	vector<BaseObject*>* GetList();
	void deleteSword(BaseObject* sword);

	//change and reset frame size
	void changeFrameSize(BaseObject*obj);
	void resetFrameSize(BaseObject*obj);

	//destructor of Swordsman class
	~Swordsman();
};

#endif
