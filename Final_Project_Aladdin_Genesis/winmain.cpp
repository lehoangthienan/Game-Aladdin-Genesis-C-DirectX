#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include "Game.h"

Game game;

//window event callback function
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		//call the "front-end" shutdown function
		game.Game_End(hWnd);
		//tell Windows to kill this program
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//helper function to set up the window properties
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	//create the window class structure
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	//fill the struct with info
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = APPTITLE;
	wc.hIconSm = NULL;

	//set up the window with the class info
	return RegisterClassEx(&wc);
}

//entry point for a Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	HWND hWnd;

	//register the class
	MyRegisterClass(hInstance);

	//set up the screen in windowed or fullscreen mode?
	DWORD style;
	if (FULLSCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPED;

	//create a new window
	hWnd = CreateWindow(APPTITLE,
		APPTITLE,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//was there an error creating the window?
	if (!hWnd)
		return FALSE;

	//display the window
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	if (!game.Init_Direct3D(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN))
		return 0;

	//initialize input directx
	if (!game.Init_DirectInput(hWnd))
	{
		MessageBox(hWnd, "Error intializing DirectInput", "Error", MB_OK);
		return 0;
	}
	
	//initialize the game
	if (!game.Game_Init(hWnd))
	{
		MessageBox(hWnd, "Error initializing the game", "Error", MB_OK);
		return 0;
	}

	//main message loop
	int done = 0;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//look for quit message
			if (msg.message == WM_QUIT)
				done = 1;
			//decode and pass messages on to WndProc
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			//process game loop (else prevents running after window is closed)
			game.Game_Run(hWnd);
	}
	return msg.wParam;
}