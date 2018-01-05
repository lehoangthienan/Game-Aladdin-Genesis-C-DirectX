#ifndef _ROD_H
#define _ROD_H

#include "Collision.h"
#include "Sprite.h"

//status of Rod
namespace _RodStatus
{
	enum RodStatus
	{
		NOTMOVING,
		MOVING
	};
}

using namespace _RodStatus;

class Rod : public BaseObject
{
private:

	RodStatus status;
	int animation_rate;

	Sprite *rod_image;
	DWORD last_time;

public:
	//contructor of Rod class
	Rod();

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

	//action of Rod
	void NotMove();
	void Move();

	//get status Rod
	int getStatus();

	//destructor of Rod class
	~Rod();
};

#endif