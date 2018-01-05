#ifndef _RUBY_H
#define _RUBY_H

#include "Item.h"

class Ruby : public Item
{
public:
	//contructor of Ruby class
	Ruby();

	//init object
	void LoadResources();

	//action of Ruby
	void Active();
	void NonActive();

	//get sprite
	Sprite* getSprite();

	//destructor of Ruby class
	~Ruby();
};

#endif

