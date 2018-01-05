#ifndef _GENIE_H
#define _GENIE_H

#include "Sprite.h"

namespace _GenieStatus
{
	enum GenieStatus
	{
		SHOOT,
		FLY
	};
}

class Genie : public BaseObject
{
private:
	_GenieStatus::GenieStatus status;

	Sprite *genie_image;
	DWORD last_time;
	int animation_rate;

public:
	Genie();
	void LoadResources();
	void Render(int Delta);
	void Shoot();
	void Fly();
	void UpdateKey();
	void ProcessInput();
	void resetProper();
	~Genie();
};

#endif