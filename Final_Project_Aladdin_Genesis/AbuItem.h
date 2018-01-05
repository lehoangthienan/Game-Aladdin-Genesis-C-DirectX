#ifndef _ABUITEM_H
#define _ABUITEM_H

#include "Item.h"

class AbuItem : public Item
{
public:
	//contructor of Abu class
	AbuItem();

	//init object
	void LoadResources();

	//action of Abu
	void Active();
	void NonActive();

	//destructor of Abu class
	~AbuItem();
};

#endif

