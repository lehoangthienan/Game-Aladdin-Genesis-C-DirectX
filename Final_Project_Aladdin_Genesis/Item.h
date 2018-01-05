#ifndef _ITEM_H
#define _ITEM_H

#include "Collision.h"
#include "Sprite.h"

namespace _ItemStatus
{
	enum ItemStatus
	{
		NONACTIVED,
		ACTIVED
	};
}

using namespace _ItemStatus;

class Item : public BaseObject
{
protected:
	ItemStatus status;
	int animation_rate;
	DWORD last_time, start_wait;
	Sprite*image;
	string xmlFilePath;

public:
	//contructor of item class
	Item();

	//set type collision from object's id
	void setObjectFromID();
	//init object
	virtual void LoadResources();

	//process input
	void ProcessInput();
	//sprite redering
	void Render(int Delta);
	//collision
	void OnCollision(BaseObject* obj, float normalx, float normaly);
	//interserct
	void OnInterSerct(BaseObject* obj);

	//action when item actived
	virtual void Active();
	virtual void NonActive();

	//get status item
	int getStatus();

	//destructor of item class
	~Item();
};

#endif