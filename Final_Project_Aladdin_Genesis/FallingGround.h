#ifndef _FALLINGGROUND_H
#define _FALLINGGROUND_H

#include "Collision.h"
#include "Sprite.h"

//status of FallingGround
namespace _FallingGroundStatus
{
	enum FallingGroundStatus
	{
		NOTMOVING,
		FALLING,
		DESTROY
	};
}

using namespace _FallingGroundStatus;


class FallingGround : public BaseObject
{
private:

	FallingGroundStatus status;
	int animation_rate;

	Sprite *fallingground_image;
	DWORD last_time, start_waitfall;

public:
	//contructor of FallingGround class
	FallingGround();

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

	//action of FallingGround
	void Move();
	void Fall();
	void Destroy();

	//get status FallingGround
	int getStatus();

	void resetProper();

	//destructor of FallingGround class
	~FallingGround();
};

#endif