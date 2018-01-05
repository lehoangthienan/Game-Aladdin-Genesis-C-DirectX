#ifndef _KNIVES_H
#define _KNIVES_H

#include "Sprite.h"
#include "Directx.h"

class Knives : public BaseObject
{
private:

	Directx dx;
	bool KeyUp, KeyDown;
	Sprite *knives_image;
	DWORD last_time;
	bool trans_left;
	bool isKeyUpUp, isKeyDownUp;

public:
	Knives();

	void LoadResources();
	void UpdateKey();
	void ProcessInput();
	void Render(int Delta);
	void resetProper();

	~Knives();
};

#endif

