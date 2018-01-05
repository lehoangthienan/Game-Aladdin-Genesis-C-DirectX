#include "Game.h"

Game::Game()
{
	result = 0;
}

//initializes the game
int Game::Game_Init(HWND hwnd)
{
	//set random number seed
	srand(time(NULL));

	initKeyBoard = false;

	//initialize keyboard
	initKeyBoard = Init_Keyboard(hwnd);
	if (!initKeyBoard)
	{
		MessageBox(hwnd, "Error initializing the keyboard", "Error", MB_OK);
		return 0;
	}
	GameSound::initialize(hwnd);

	//Khởi tạo các texture
	TextureManager::GetInstance()->CreateTexture(d3ddev);
	TextureManager::GetInstance()->CreateSurface(d3ddev);

	//Khởi tạo scene
	scene = new Scene();
	scene->Scene_Init(d3ddev);
	scene->sceneID = -1;
	scene->Scene_Start0();

	//return okay
	return 1;
}

//the main game loop
void Game::Game_Run(HWND hwnd)
{
	//make sure the Direct3D device is valid
	if (d3ddev == NULL)
		return;

	//init keyboard
	if (!initKeyBoard)
	{
		initKeyBoard = Init_Keyboard(hwnd);
	}

	//update keyboard
	Poll_Keyboard();

	scene->Scene_Run();

	//Phần render các đối tượng trong game
	//start rendering
	if (true)
	{
		//begin rendering
		d3ddev->BeginScene();

		d3ddev->ColorFill(backbuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
		//d3ddev->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);

		Camera::GetInstance()->SetTransform(d3ddev);

		//render background trong cùng
		scene->RenderBack(d3ddev, backbuffer);

		//render scene
		scene->Scene_Render();

		//render background ngoài cùng
		scene->RenderBack1();

		//render thông tin nếu scene là scene1 và scene boss
		scene->RenderSceneInfoPlayer();

		//stop rendering
		d3ddev->EndScene();
	}

	//diaplay the back buffer on the screen
	d3ddev->Present(NULL, NULL, NULL, NULL);

	//check for escape key (to exit program)
	if (KEY_DOWN(VK_ESCAPE))
		PostMessage(hwnd, WM_DESTROY, 0, 0);
}

//frees memory and cleans up before the game ends
void Game::Game_End(HWND hwnd)
{
	//release the Direct3D device
	if (d3ddev != NULL)
		d3ddev->Release();
	//release the Direct3D object
	if (d3d != NULL)
		d3d->Release();
}

Game::~Game()
{
	Kill_Keyboard();
}
