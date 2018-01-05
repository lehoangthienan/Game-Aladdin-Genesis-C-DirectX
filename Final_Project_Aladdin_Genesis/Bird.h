#ifndef _BIRD_H
#define _BIRD_H

#include "Sprite.h"

class Bird : public BaseObject
{
private:
	Sprite *bird_image;

public:
	Bird();
	void LoadResources();
	void ProcessInput();
	void Render(int Delta);
	void resetProper();
	~Bird();
};

#endif