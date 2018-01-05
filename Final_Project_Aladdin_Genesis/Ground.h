#ifndef _GROUND_H
#define _GROUND_H

#include "BaseObject.h"
#include "Directx.h"
#include "Sprite.h"

class Ground :public BaseObject
{
public:

	Ground();
	void setObjectFromID();
	//init object
	void LoadResources();
	//sprite redering
	void Render(int Delta);

	//change and reset frame size
	void changeFrameSize(BaseObject*obj);
	void resetFrameSize(BaseObject*obj);

	~Ground();
};

#endif