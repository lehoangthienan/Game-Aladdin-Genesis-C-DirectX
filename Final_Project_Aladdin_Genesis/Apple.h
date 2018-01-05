#ifndef _APPLE_H
#define _APPLE_H

#include "Collision.h"
#include "Aladdin.h"
#include "Sprite.h"

namespace _AppleStatus
{
	enum AppleStatus
	{
		NOTMOVING,
		FLING,
		BURST,
		ACTIVED,
		SPLIT_HALF,
	};
}

using namespace _AppleStatus;

class Apple : public BaseObject
{
private:

	AppleStatus status;
	int animation_rate;

	Sprite *apple_image;
	DWORD last_time;
	string xmlFilePath;
	bool typeSplit_Half; // true: split_half1, false: split_half2

public:
	Apple();

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
	void Burst();
	void Move();
	void Active();
	void Split_Half();

	//get status apple
	int getStatus();

	//get sprite
	Sprite* getSprite();

	//reset
	void resetProper();

	~Apple();
};

#endif