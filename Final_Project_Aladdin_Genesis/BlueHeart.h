#ifndef _BLUEHEART_H
#define _BLUEHEART_H

#include "Item.h"

class BlueHeart : public Item
{
public:
	//contructor of BlueHeart class
	BlueHeart();

	//init object
	void LoadResources();

	//action of BlueHeart
	void Active();
	void NonActive();

	//destructor of BlueHeart class
	~BlueHeart();
};

#endif
