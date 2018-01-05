#ifndef _BLOODBAR_H
#define _BLOODBAR_H

#include "Collision.h"
#include "Sprite.h"
#include "Aladdin.h"

class BloodBar : public BaseObject
{
private:
	int animation_rate;

	Sprite *bloodbar_image;
	DWORD last_time, startBlink;

	//Giống nhấp nháy (blink) của aladdin
	int isBlink;
	int old_blood;

public:
	//contructor of BloodBar class
	BloodBar();
	
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

	//destructor of BloodBar class
	~BloodBar();
};

#endif