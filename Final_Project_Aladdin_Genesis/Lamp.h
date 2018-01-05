#ifndef _LAMP_H
#define _LAMP_H

#include "Item.h"

class Lamp : public Item
{
public:
	//contructor of Lamp class
	Lamp();

	//init object
	void LoadResources();

	//action of Lamp
	void Active();
	void NonActive();

	//destructor of Lamp class
	~Lamp();
};

#endif
