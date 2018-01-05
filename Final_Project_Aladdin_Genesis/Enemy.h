#ifndef _ENEMY_H
#define _ENEMY_H

#include "Collision.h"
#include "Aladdin.h"
#include "Sprite.h"

class Enemy: public BaseObject
{
protected:
	int animation_rate;
	DWORD last_time;
	Sprite*image;
	string xmlFilePath;

public:
	//contructor of enemy class
	Enemy();

	//set type collision from object's id
	void setObjectFromID();
	//init object
	virtual void LoadResources();

	//process input
	virtual void ProcessInput();
	//sprite redering
	void Render(int Delta);
	//collision
	virtual void OnCollision(BaseObject* obj, float normalx, float normaly);
	//interserct
	virtual void OnInterSerct(BaseObject* obj);

	//get list object
	virtual vector<BaseObject*>* GetList();

	//change and reset frame size
	virtual void changeFrameSize(BaseObject*obj);
	virtual void resetFrameSize(BaseObject*obj);

	//action when enemy die
	virtual void Die();

	//get status of enemy
	virtual int getStatus();

	//destructor of enemy class
	~Enemy();
};

#endif