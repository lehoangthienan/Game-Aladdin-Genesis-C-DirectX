#ifndef _GenieJar_H
#define _GenieJar_H

#include "Item.h"

class GenieJar : public Item
{
public:
	//contructor of GenieJar class
	GenieJar();

	//init object
	void LoadResources();

	//action of GenieJar
	void Active();
	void NonActive();

	//destructor of GenieJar class
	~GenieJar();
};

#endif
