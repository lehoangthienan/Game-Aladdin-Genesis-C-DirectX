#include "Directx.h"

//contructor of Directx class
Directx::Directx()
{
	//variable declarations
	d3d = NULL;
	d3ddev = NULL;
	backbuffer = NULL;
}


int Directx::Init_Direct3D(HWND hwnd, int width, int height, int fullscreen)
{
	//initalize Direct3D
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL)
	{
		MessageBox(hwnd, "Error initializing Direct3D", "Error", MB_OK);
		return 0;
	}

	//set Direct3D presentation parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = (!fullscreen);
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.hDeviceWindow = hwnd;

	//create Direct3D device
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	if (d3ddev == NULL)
	{
		MessageBox(hwnd, "Error creating Direct3D device", "Error", MB_OK);
		return 0;
	}

	//clear the backbuffer to black
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//create pointeer to the back buffer
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
	return 1;
}

LPDIRECT3DSURFACE9 Directx::LoadSurface(char *filename, D3DCOLOR transcolor)
{
	LPDIRECT3DSURFACE9 image = NULL;
	D3DXIMAGE_INFO info;
	HRESULT result;
	//get width and height from bitmap file
	result = D3DXGetImageInfoFromFile(filename, &info);
	if (result != D3D_OK)
		return NULL;
	//create surface
	result = d3ddev->CreateOffscreenPlainSurface(
		info.Width, //width of the surface
		info.Height, //height of the surface
		D3DFMT_X8R8G8B8, //surface format
		D3DPOOL_DEFAULT, //memory pool to use
		&image, //pointer to the surface
		NULL); //reserved (always NULL)
	if (result != D3D_OK)
		return NULL;
	//load surface from file into newly created surface
	result = D3DXLoadSurfaceFromFile(
		image, //destination surface
		NULL, //destination palette
		NULL, //destination rectangle
		filename, //source filename
		NULL, //source rectangle
		D3DX_DEFAULT, //controls how image is filtered
		transcolor, //for transparency (0 for none)
		NULL); //source image info (usually NULL)
	//make sure file was loaded okay
	if (result != D3D_OK)
		return NULL;
	return image;
}

LPDIRECT3DTEXTURE9 Directx::LoadTexture(char* filename, D3DCOLOR transcolor)
{
	LPDIRECT3DTEXTURE9 texture = NULL;
	D3DXIMAGE_INFO info;
	HRESULT result;

	//get width and height from bitmap file
	result = D3DXGetImageInfoFromFile(filename, &info);
	if (result != D3D_OK)
		return NULL;

	//create texture
	result = D3DXCreateTextureFromFileEx(
		d3ddev,
		filename,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		&info,
		NULL,
		&texture);

	//make sure file was loaded okay
	if (result != D3D_OK)
		return NULL;
	return texture;
}

#define BUTTON_DOWN(obj, button) (obj.rgbButtons[button] & 0x80)

//keyboard input
char keys[256];
int Directx::Init_DirectInput(HWND hwnd)
{
	//initialize DirectInput object
	HRESULT result = DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&dinput,
		NULL);
	if (result != DI_OK)
		return 0;

	//initialize the keyboard
	result = dinput->CreateDevice(GUID_SysKeyboard, &dikeyboard, NULL);
	if (result != DI_OK)
		return 0;

	//clean return
	return 1;
}

int Directx::Init_Keyboard(HWND hwnd)
{
	//set the data format for mouse input
	HRESULT result = dikeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (result != DI_OK)
		return 0;
	//set the cooperative level
	result = dikeyboard->SetCooperativeLevel(hwnd,
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (result != DI_OK)
		return 0;
	//acquire the mouse
	result = dikeyboard->Acquire();
	if (result != DI_OK)
		return 0;
	//give the go-ahead
	return 1;
}

void Directx::Poll_Keyboard()
{
	dikeyboard->GetDeviceState(sizeof(keys), (LPVOID)&keys);
}

int Directx::Key_Down(int key)
{
	return (keys[key] & 0x80);
}

void Directx::Kill_Keyboard()
{
	if (dikeyboard != NULL)
	{
		dikeyboard->Unacquire();
		dikeyboard->Release();
		dikeyboard = NULL;
	}
}

Directx::~Directx()
{
	if (d3d != NULL)
		d3d->Release();
	if (d3ddev != NULL)
		d3ddev->Release();
	/*if (backbuffer != NULL)
		backbuffer->Release();*/
}
