#ifndef _STAR_H
#define _STAR_H

#include "Boss.h"
#include "Aladdin.h"

class Boss;

namespace _StarStatus
{
	enum StarStatus
	{
		FLING,
		DESTROY
	};
}

class Star : public BaseObject
{
	Boss *boss;
	_StarStatus::StarStatus status;
	int animation_rate;

	Sprite *star_image;
	DWORD last_time;
	string  xmlFilePath;

public:
	Star();
	void setObjectFromID();
	//init object
	void LoadResources();

	//process input
	virtual void ProcessInput();
	//sprite redering
	void Render(int Delta);
	//collision
	void OnCollision(BaseObject* obj, float normalx, float normaly);
	//interserct
	void OnInterSerct(BaseObject* obj);

	//action of camel
	void Destroy();
	void Fly();

	//get status apple
	int getStatus();

	//get Sword thrower
	void GetBoss(Boss *obj);

	~Star();
};

#endif