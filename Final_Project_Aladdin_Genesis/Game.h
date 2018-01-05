#ifndef _GAME_H
#define _GAME_H

#include <time.h>
#include "TextureManager.h"
#include "Scene.h"
#include "GameSound.h"

//application title
#define APPTITLE "Anim_Sprite"

//screen setup
#define FULLSCREEN 0
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 448
#define GameTime 4

//macros to read the keyboard asynchronously
#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000)? 1:0)
#define KEY_UP(vk_code)((GetAsyncKeyState(vk_code) & 0x8000)? 1:0)

class Map;

class Game:public Directx
{
private:
	HRESULT result;
	Scene* scene;
	bool initKeyBoard;

public:
	//constructor of game class
	Game();

	//function prototypes
	int Game_Init(HWND);
	void Game_Run(HWND);
	void Game_End(HWND);

	~Game();
};

#endif