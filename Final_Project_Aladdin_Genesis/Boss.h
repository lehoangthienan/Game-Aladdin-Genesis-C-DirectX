#ifndef _BOSS_H
#define _BOSS_H

#include "Enemy.h"
#include "Fire.h"
#include "Star.h"

namespace _BossStatus
{
	enum BossStatus
	{
		STANDING,
		ATTACK,
		DIE
	};
}

class Fire;
class Star;

class Boss : public Enemy
{
private:

	_BossStatus::BossStatus status;

	vector<BaseObject*>list;
	bool isCreate;

	DWORD startCut;
	float blood;
	bool isHurt;
	int typeBoss;

public:
	Boss();
	void LoadResources();

	//process input
	virtual void ProcessInput();

	void OnCollision(BaseObject* obj, float normalx, float normaly);
	//interserct
	void OnInterSerct(BaseObject* obj);

	//action of camel
	void Stand();
	void Attack();
	void Die();

	//get status aladdin
	int getStatus();

	void createFire();
	vector<BaseObject*>* GetList();
	void deleteFire(BaseObject* sword);
	void createStar();
	void deleteStar(BaseObject* star);

	void changeFrameSize(BaseObject*obj);
	void resetFrameSize(BaseObject*obj);

	int getTypeObj();
	~Boss();
};

#endif
