#ifndef _FIRECARPET_H
#define _FIRECARPET_H

#include "Collision.h"
#include "Fire.h"

class Fire;

class FireCarpet : public BaseObject
{
private:

	DWORD last_time, start_delay;
	vector<BaseObject*>listFire;

public:
	//contructor of FireCarpet class
	FireCarpet();

	//init object
	void LoadResources();

	//process input
	void ProcessInput();

	//collision
	void OnCollision(BaseObject* obj, float normalx, float normaly);
	//interserct
	void OnInterSerct(BaseObject* obj);

	//get status aladdin
	int getStatus();

	//handle sword
	void createFire(BaseObject*obj);
	vector<BaseObject*>* GetList();
	void deleteFire(BaseObject* sword);

	//change and reset frame size
	void changeFrameSize(BaseObject*obj);
	void resetFrameSize(BaseObject*obj);

	//destructor of FireCarpet class
	~FireCarpet();
};

#endif