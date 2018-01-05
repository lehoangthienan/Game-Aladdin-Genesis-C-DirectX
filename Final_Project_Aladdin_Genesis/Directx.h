#ifndef _DIRECTX_H
#define _DIRECTX_H

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

class Directx
{
protected:
	//variable declarations
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddev;
	LPDIRECT3DSURFACE9 backbuffer;

	//DirectInput objects, devices, and states
	LPDIRECTINPUT8 dinput;
	LPDIRECTINPUTDEVICE8 dikeyboard;

public:
	//constructor of Directx class
	Directx();

	//function prototypes of dxGraphics
	int Init_Direct3D(HWND, int, int, int);
	LPDIRECT3DSURFACE9 LoadSurface(char*, D3DCOLOR);
	LPDIRECT3DTEXTURE9 LoadTexture(char*, D3DCOLOR);

	//function prototypes of dxInput
	int Init_DirectInput(HWND);
	int Init_Keyboard(HWND);

	void Poll_Keyboard();
	int Key_Down(int);
	void Kill_Keyboard();

	//destructor of Directx class
	~Directx();
};

#endif