#ifndef _SPITTLE_H
#define _SPITTLE_H

#include "Camel.h"
#include "Sprite.h"

class Camel;

namespace _SpittleStatus
{
	enum SpittleStatus
	{
		FLING,
		DESTROY
	};
}

using namespace _SpittleStatus;

class Spittle : public BaseObject
{
private:
	Camel *camel;
	SpittleStatus status;
	int animation_rate;

	Sprite *spittle_image;
	DWORD last_time;

public:
	//contructor of Spittle class
	Spittle();

	//set type collision from object's id
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
	void Fly();
	void Destroy();

	//get status apple
	int getStatus();

	//get Spittle thrower
	void GetCamel(Camel *obj);

	//destructor of Spittle class
	~Spittle();
};

#endif