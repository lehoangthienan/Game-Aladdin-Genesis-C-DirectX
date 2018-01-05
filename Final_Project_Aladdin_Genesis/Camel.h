#ifndef _CAMEL_H
#define _CAMEL_H

#include "Collision.h"
#include "Spittle.h"
#include "Sprite.h"

//status of camel
namespace _CamelStatus
{
	enum CamelStatus
	{
		LIE,
		SPIT
	};
}

using namespace _CamelStatus;

class Spittle;

class Camel : public BaseObject
{
private:

	CamelStatus status;
	int animation_rate;

	Sprite *camel_image;
	DWORD last_time;

	vector<BaseObject*>listSpittle;
	bool isCreateSpittle;

public:
	//contructor of camel class
	Camel();

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
	void Lie();
	void Spit();

	//get status camel
	int getStatus();
	//get camel direction
	bool getDirection();

	//handle spittle
	void createSpittle();
	vector<BaseObject*>* GetList();
	void deleteSpittle(BaseObject* spittle);

	//destructor of camel class
	~Camel();
};

#endif