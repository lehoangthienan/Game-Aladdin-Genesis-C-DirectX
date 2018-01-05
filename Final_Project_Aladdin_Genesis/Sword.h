#ifndef _SWORD_H
#define _SWORD_H

#include "Swordsman.h"
#include "Guard3.h"

class Swordsman;
class Guard3;

namespace _SwordStatus
{
	enum SwordStatus
	{
		FLING,
		DESTROY,
		DIE
	};
}

class Sword : public Enemy
{
private:
	Swordsman *swordsMan;
	Guard3 * guard3;
	_SwordStatus::SwordStatus status;
	

public:
	//contructor of Sword class
	Sword();

	//init object
	void LoadResources();

	//process input
	virtual void ProcessInput();
	
	//collision
	void OnCollision(BaseObject* obj, float normalx, float normaly);
	//interserct
	void OnInterSerct(BaseObject* obj);

	//action of camel
	void Destroy();
	void Fly();
	void Die();

	//get status apple
	int getStatus();

	//get Sword thrower
	void GetSwordsman(Swordsman *obj);

	//get Guard3 
	void GetGuard3(Guard3 *obj);

	//destructor of Sword class
	~Sword();
};

#endif