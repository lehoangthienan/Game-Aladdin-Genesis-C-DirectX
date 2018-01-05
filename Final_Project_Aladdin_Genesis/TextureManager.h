#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

#include <iostream>
#include "Directx.h"
#include "trace.h"

using namespace std;

class TextureManager
{
private:
	static TextureManager* instance;

	LPD3DXSPRITE sprite_handler;

	LPDIRECT3DTEXTURE9 aladdin_image;
	LPDIRECT3DTEXTURE9 camel_image;
	LPDIRECT3DTEXTURE9 civilianenemies_image;
	LPDIRECT3DTEXTURE9 enemydie_image;
	LPDIRECT3DTEXTURE9 enemyexplosion_image;
	LPDIRECT3DTEXTURE9 guards_image;
	LPDIRECT3DTEXTURE9 itemactived_image;
	LPDIRECT3DTEXTURE9 items_image;
	LPDIRECT3DTEXTURE9 jafar_image;
	LPDIRECT3DTEXTURE9 rod_image;
	LPDIRECT3DTEXTURE9 fallingground_image;
	LPDIRECT3DTEXTURE9 bloodbar_image;
	LPDIRECT3DTEXTURE9 genie_image;
	LPDIRECT3DTEXTURE9 knives_image;
	LPDIRECT3DTEXTURE9 abu_image;
	LPDIRECT3DTEXTURE9 bird_image;
	
	LPDIRECT3DTEXTURE9 scene1_image;
	LPDIRECT3DTEXTURE9 sceneboss_image;

	LPDIRECT3DSURFACE9 finish_image;
	LPDIRECT3DSURFACE9 theend_image;
	

public:
	//contructor of Texture manager class
	TextureManager();

	static TextureManager* GetInstance();

	//create texture
	void CreateTexture(LPDIRECT3DDEVICE9 d3ddev);
	void CreateSurface(LPDIRECT3DDEVICE9 d3ddev);

	LPD3DXSPRITE GetSprite_Handler();

	//Lấy Texture tương ứng với mỗi đối tượng
	LPDIRECT3DTEXTURE9 GetAladdinTexture();
	LPDIRECT3DTEXTURE9 GetCamelTexture();
	LPDIRECT3DTEXTURE9 GetCivilianEnemiesTexture();
	LPDIRECT3DTEXTURE9 GetEnemyDieTexture();
	LPDIRECT3DTEXTURE9 GetEnemyExplosionTexture();
	LPDIRECT3DTEXTURE9 GetGuardsTexture();
	LPDIRECT3DTEXTURE9 GetItemActivedTexture();
	LPDIRECT3DTEXTURE9 GetItemsTexture();
	LPDIRECT3DTEXTURE9 GetJafarTexture();
	LPDIRECT3DTEXTURE9 GetRodTexture();
	LPDIRECT3DTEXTURE9 GetFallingGroundTexture();
	LPDIRECT3DTEXTURE9 GetBloodBarTexture();
	LPDIRECT3DTEXTURE9 GetAbuTexture();
	LPDIRECT3DTEXTURE9 GetGenieTexture();
	LPDIRECT3DTEXTURE9 GetKnivesTexture();
	LPDIRECT3DTEXTURE9 GetBirdTexture();

	LPDIRECT3DTEXTURE9 GetScene1Texture();
	LPDIRECT3DTEXTURE9 GetSceneBossTexture();
	
	LPDIRECT3DSURFACE9 GetFinishTexture();
	LPDIRECT3DSURFACE9 GetTheEndTexture();
	

	//LoadTexture
	LPDIRECT3DTEXTURE9 LoadTexture(LPDIRECT3DDEVICE9 d3ddev, LPCSTR filePath, D3DCOLOR transcolor);
	LPDIRECT3DSURFACE9 LoadSurface(LPDIRECT3DDEVICE9 d3ddev, LPCSTR filePath, D3DCOLOR transcolor);

	//destructor of Texture manager class
	~TextureManager();
};

#endif