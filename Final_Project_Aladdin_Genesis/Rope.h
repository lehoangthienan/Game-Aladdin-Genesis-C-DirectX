#ifndef _ROPE_H
#define _ROPE_H

#include "BaseObject.h"
#include "Directx.h"
#include "Sprite.h"

class Rope :public BaseObject
{
public:
	Rope();

	void setObjectFromID();
	//init object
	void LoadResources(LPDIRECT3DDEVICE9 d3ddev);
	//sprite redering
	void Render(int Delta);

	~Rope();
};

#endif