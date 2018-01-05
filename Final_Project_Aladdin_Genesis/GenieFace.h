#ifndef _GENIEFACE_H
#define _GENIEFACE_H

#include "Item.h"

class GenieFace : public Item
{
public:
	//contructor of GenieFace class
	GenieFace();

	//init object
	void LoadResources();

	//action of GenieFace
	void Active();
	void NonActive();

	//destructor of GenieFace class
	~GenieFace();
};

#endif
