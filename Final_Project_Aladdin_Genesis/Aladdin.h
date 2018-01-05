#ifndef _ALADDIN_H
#define _ALADDIN_H

#include <time.h>
#include <iostream>
#include "Apple.h"
#include "Directx.h"
#include "Sprite.h"

//status of aladdin
namespace _AladdinStatus
{
	enum AladdinStatus
	{
		STANDING,
		WAITING_1,
		WAITING_2,
		WAITING_3,
		RUNNING,
		RUN_LONG_ENOUGH,
		BRAKING,
		CUTTING,
		JUMPING,
		THROWING,
		LOOK_UP,
		SITTING,
		CLIMB,
		CLIMBING,
		SWING,
		SWINGING,
		PUSHING,
		STUNTING,
		HURT,
		DIE,
		RESETPOSITION,
		RUNNEXT,
		FLY,
		HUG
	};
}

using namespace _AladdinStatus;

class Aladdin : public BaseObject
{
public:
	int blood;
	int score;
	int numberofrubies;
	int numberoflifes;
	int numberofapples;
	bool isCollStair, isCutted;

private:
	static Aladdin* instance;
	float last_vy;

	AladdinStatus status, last_status;
	int animation_rate;				// this is to control the animate rate of aladdin
	int currentIndex;

	DWORD last_time, standing_time;					

	Directx dx;
	Sprite *aladdin_image;
	ID3DXFont *font;
	bool keyUp[3];
	bool KeyUp, KeyDown, KeyZ, KeyX, KeyC, KeyLeft, KeyRight;
	int count;

	vector<BaseObject*> listApple;
	bool isCreateApple;
	//Kiểm tra nhấp nháy (khi bị thương)
	//Nếu isBlink = 0 : không ở trong trạng thái nhấp nháy, nếu isBlink = 1 : nhấp nháy (kích hoạt trạng thái nhấp nháy, không vẽ sprite)
	//Nếu isBlink = 2 : ko nhấp nháy (vẫn ở trong trạng thái nhấp nháy, vẽ sprite)
	int isBlink;
	//Lưu thời gian lúc bắt đầu nhấp nháy
	DWORD startBlink;

public:
	//contructor of aladdin class
	Aladdin();

	static Aladdin* GetInstance();

	//load aladdin animation
	void LoadResources();
	//update key
	void UpdateKey();
	//process input
	void ProcessInput();
	//sprite redering
	void Render(int Delta);
	//collision
	void OnCollision(BaseObject* obj, float normalx, float normaly);
	//interserct
	void OnInterSerct(BaseObject* obj);

	//action of aladdin
	void Wait();
	void Stand();
	void Run();
	void Jump();
	void Throw();
	void Cut();
	void LookUp();
	void Brake();
	void Sit();
	void Climb();
	void Climbing();
	void Swing();
	void Swinging();
	void Push();
	void Stunt();
	void Hurt();
	void Die();
	void ResetPosition();
	void RunNext();
	void Fly();
	void Hug();

	//create font
	void createFont(LPDIRECT3DDEVICE9 d3ddev, D3DXFONT_DESC desc);
	//draw font
	void drawFont(int x, int y, int width, int height);

	//get status aladdin
	int getStatus();
	int getLastStatus();

	//handle apple
	void createApple();
	void createApple(BaseObject*obj);
	vector<BaseObject*>* GetList();
	void deleteApple(BaseObject* apple);

	//reset properties
	void resetProper();

	//destructor of aladdin class
	~Aladdin();
};

#endif