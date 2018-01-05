#ifndef _ABU_H
#define _ABU_H

#include "Sprite.h"

namespace _AbuStatus
{
	enum AbuStatus
	{
		FAN,
		RUN
	};
}
using namespace _AbuStatus;

class Abu : public BaseObject
{
private:

	AbuStatus status;
	Sprite *abu_image;
	DWORD last_time;
	int animation_rate;

public:
	Abu();

	void LoadResources();
	void ProcessInput();

	void Render(int Delta);

	void Fan();
	void Run();
	void resetProper();

	~Abu();
};

#endif
