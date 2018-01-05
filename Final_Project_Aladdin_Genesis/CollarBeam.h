#ifndef _COLLARBEAM_H
#define _COLLARBEAM_H

#include "BaseObject.h"
#include "Sprite.h"

class CollarBeam:public BaseObject
{
public:
	CollarBeam();

	void setObjectFromID();
	//init object
	void LoadResources();
	//sprite redering
	void Render(int Delta);

	~CollarBeam();
};

#endif
