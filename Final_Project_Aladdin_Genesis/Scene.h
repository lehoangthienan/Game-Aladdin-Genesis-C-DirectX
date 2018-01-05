#ifndef _SCENE_H
#define _SCENE_H

#include "Directx.h"
#include "TextureManager.h"
#include "Map.h"
#include "GameSound.h"

class Scene
{
private:

	Directx dx;
	Map*map, *mapboss;
	Sprite*background;
	LPDIRECT3DSURFACE9 back;

	float cloud_dx[4];
	int count;
	bool KeyNext;
	DWORD last_time, begin;

	BloodBar *aladdin_bloodbar;
	Apple *aladdin_apple;
	Ruby *aladdin_ruby;
	AladdinFace *aladdin_life;
	D3DXFONT_DESC desc;
	ID3DXFont *numberofapples, *numberofrubies, *numberoflifes, *score;
	bool isKeyEnterUp, isHide;

public:

	int sceneID, last_sceneID;

	Scene();
	void Scene_Init(LPDIRECT3DDEVICE9 d3ddev);
	void Scene_Run();

	void Scene_Start0();
	void Scene_Start1();
	void Scene_Options0();
	void Scene_Options1();
	void Scene_Bug();
	void Scene_Introduce();
	void Scene_Story();
	void Scene_BeginScene1();
	void Scene_Scene1();
	void Scene_Next();
	void Scene_BeginSceneBoss();
	void Scene_SceneBoss();
	void Scene_Finish();
	void Scene_TheEnd();
	void Scene_Die();

	void Scene_Render();
	void RenderBack(LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DSURFACE9 backbuffer);
	void RenderBack1();
	void RenderSceneInfoPlayer();
	void UpdateKey();

	//draw font
	void drawFont(ID3DXFont*font, float x, float y, float width, float height, int value);

	~Scene();
};


#endif