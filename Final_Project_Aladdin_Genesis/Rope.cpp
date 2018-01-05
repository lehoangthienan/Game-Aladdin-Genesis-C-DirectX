#include "Rope.h"

Rope::Rope()
{
	isDead = false;
}

void Rope::setObjectFromID()
{
	collType = CollRope;
}

//init object
void Rope::LoadResources(LPDIRECT3DDEVICE9 d3ddev){}

//sprite redering
void Rope::Render(int Delta){}

Rope::~Rope(){}
