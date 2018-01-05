#include "Scene.h"

#define MAP1_FILEPATH "Data/Map/AgrabahMarket.txt"
#define QUADTREE1_FILEPATH "Data/Map/AgrabahMarketQuadTree.txt"
#define MAP2_FILEPATH "Data/Map/BossSpace.txt"
#define QUADTREE2_FILEPATH "Data/Map/BossSpaceQuadTree.txt"

Scene::Scene()
{}

void Scene::Scene_Init(LPDIRECT3DDEVICE9 d3ddev)
{
	isHide = true;
	count = 0;

	//set desc properties
	ZeroMemory(&desc, sizeof(D3DXFONT_DESC));
	desc.Height = 20;
	desc.Width = 10;
	desc.Weight = 200;
	desc.MipLevels = D3DX_DEFAULT;
	desc.Italic = false;
	desc.CharSet = 0;
	desc.OutputPrecision = 0;
	desc.Quality = 0;
	desc.PitchAndFamily = 0;
	strcpy_s(desc.FaceName, "Times New Roman");
	//Aladdin::GetInstance()->createFont(d3ddev, desc);
	D3DXCreateFontIndirect(d3ddev, &desc, &numberofapples);
	D3DXCreateFontIndirect(d3ddev, &desc, &numberofrubies);
	D3DXCreateFontIndirect(d3ddev, &desc, &numberoflifes);
	desc.Height = 40;
	desc.Width = 20;
	desc.Weight = 400;
	D3DXCreateFontIndirect(d3ddev, &desc, &score);

	background = new Sprite();

	//Khởi tạo map
	map = new Map();
	mapboss = new Map();

	map->LoadResource(MAP1_FILEPATH, QUADTREE1_FILEPATH);
	mapboss->LoadResource(MAP2_FILEPATH, QUADTREE2_FILEPATH);

	//khởi tạo các giá trị ban đầu của aladdin
	Aladdin::GetInstance()->LoadResources();

	//Khởi tạo camera
	//Camera::GetInstance()->Camera_Init(150, 700, 320, 200, Aladdin::GetInstance());

	//khởi tạo thanh máu cho aladdin
	aladdin_bloodbar = new BloodBar();
	aladdin_bloodbar->LoadResources();

	aladdin_apple = new Apple();
	aladdin_apple->collType = CollItem;
	aladdin_apple->LoadResources();
	aladdin_apple->getSprite()->setFrame(1, 1);

	aladdin_ruby = new Ruby();
	aladdin_ruby->LoadResources();
	aladdin_ruby->getSprite()->setFrame(9, 9);

	aladdin_life = new AladdinFace();
	aladdin_life->LoadResources();
}

void Scene::UpdateKey()
{
	if (!dx.Key_Down(DIK_RETURN))
		isKeyEnterUp = true;
	KeyNext = dx.Key_Down(DIK_RETURN);
}

void Scene::Scene_Run()
{
	UpdateKey();

	switch (sceneID)
	{
	case 0:
		Scene_Start0();
		break;
	case 1:
		Scene_Start1();
		break;
	case 2:
		Scene_Options0();
		break;
	case 3:
		Scene_Options1();
		break;
	case 4:
		Scene_Bug();
		break;
	case 5:
		Scene_Introduce();
		break;
	case 6:
		Scene_Story();
		break;
	case 7:
		Scene_BeginScene1();
		break;
	case 8:
		Scene_Scene1();
		break;
	case 9:
		Scene_Next();
		break;
	case 10:
		Scene_BeginSceneBoss();
		break;
	case 11:
		Scene_SceneBoss();
		break;
	case 12:
		Scene_Finish();
		break;
	case 13:
		Scene_TheEnd();
		break;
	case 14:
		Scene_Die();
		break;

	}
}

void Scene::Scene_Start0()
{
	switch (sceneID)
	{
	case 0:
	{
			  map->Run(sceneID);
			  Camera::GetInstance()->Camera_Run();
			  DWORD now = GetTickCount();
			  if ((now - last_time > 3000 && !isHide) || (KeyNext && isKeyEnterUp))
			  {
				  GameSound::getInstance()->play(BACKGROUND_MUSIC, true);
				  Scene_Start1();
			  }
			  break;
	}
	default:
	{
			   GameSound::getInstance()->play(SHOOT_MUSIC);

			   sceneID = 0;
			   isKeyEnterUp = false;
			   isHide = true;
			   count = 0;
			   last_time = GetTickCount();
			   begin = GetTickCount();
			   background->setImage(TextureManager::GetInstance()->GetScene1Texture());
			   map->Reset(sceneID);
			   Camera::GetInstance()->Camera_Init(0, 0, 320, 224, 0, 0, 0, 0, NULL);
			   break;
	}
	}
}

void Scene::Scene_Start1()
{
	switch (sceneID)
	{
	case 1:
	{
			  map->Run(sceneID);
			  DWORD now = GetTickCount();
			  Camera::GetInstance()->Camera_Run();
			  if (now - last_time > 2500 || (KeyNext && isKeyEnterUp))
				  Scene_Options0();
			  break;
	}
	default:
	{
			   sceneID = 1;
			   isKeyEnterUp = false;
			   last_time = GetTickCount();
			   background->setImage(TextureManager::GetInstance()->GetScene1Texture());
			   map->Reset(sceneID);
			   Camera::GetInstance()->Camera_Init(320, 0, 320, 224, 0, 0, 0, 0, NULL);
			   break;
	}
	}
}

void Scene::Scene_Options0()
{
	switch (sceneID)
	{
	case 2:
	{
			  BaseObject*obj = map->Run(sceneID);
			  Camera::GetInstance()->Camera_Run();
			  if (KeyNext && isKeyEnterUp)
			  {
				  if (obj != NULL && obj->ary == 126)
					  Scene_Bug();
				  else if (obj != NULL && obj->ary == 142)
					  Scene_Options1();
			  }
			  break;
	}
	default:
	{
			   sceneID = 2;
			   isKeyEnterUp = false;
			   background->setImage(TextureManager::GetInstance()->GetScene1Texture());
			   map->Reset(sceneID);
			   Camera::GetInstance()->Camera_Init(640, 0, 320, 223, 0, 0, 0, 0, NULL);
			   break;
	}
	}
}

void Scene::Scene_Options1()
{
	switch (sceneID)
	{
	case 3:
	{
			  BaseObject*obj = map->Run(sceneID);
			  Camera::GetInstance()->Camera_Run();
			  if (KeyNext && isKeyEnterUp)
			  {
				  if (obj != NULL && obj->ary == 190)
					  Scene_Options0();
			  }
			  break;
	}
	default:
	{
			   sceneID = 3;
			   isKeyEnterUp = false;
			   background->setImage(TextureManager::GetInstance()->GetScene1Texture());
			   map->Reset(sceneID);
			   Camera::GetInstance()->Camera_Init(640, 0, 320, 223, 0, 0, 0, 0, NULL);
			   break;
	}
	}
}

void Scene::Scene_Bug()
{
	switch (sceneID)
	{
	case 4:
	{
			  Camera::GetInstance()->Camera_Run();
			  DWORD now = GetTickCount();
			  if (KeyNext && isKeyEnterUp || count == 0 && isHide)
				  Scene_Introduce();
			  break;
	}
	default:
	{
			   sceneID = 4;
			   isKeyEnterUp = false;
			   isHide = false;
			   count = 0;
			   begin = GetTickCount();
			   background->setImage(TextureManager::GetInstance()->GetScene1Texture());
			   map->Reset(sceneID);
			   Camera::GetInstance()->Camera_Init(1289, 0, 320, 223, 0, 0, 0, 0, NULL);
			   break;
	}
	}
}

void Scene::Scene_Introduce()
{
	switch (sceneID)
	{
	case 5:
	{
			  Camera::GetInstance()->Camera_Run();
			  DWORD now = GetTickCount();
			  if (now - last_time > 5000 || (KeyNext && isKeyEnterUp))
			  {
				  if (isHide)
					  isHide = false;
				  else
					  Scene_Story();
			  }
			  break;
	}
	default:
	{
			   sceneID = 5;
			   isKeyEnterUp = false;
			   last_time = GetTickCount();
			   isHide = true;
			   background->setImage(TextureManager::GetInstance()->GetScene1Texture());
			   map->Reset(sceneID);
			   Camera::GetInstance()->Camera_Init(962, 198, 320, 224, 0, 0, 0, 0, NULL);
			   break;
	}
	}
}

void Scene::Scene_Story()
{
	switch (sceneID)
	{
	case 6:
	{
			  Camera::GetInstance()->Camera_Run();
			  DWORD now = GetTickCount();
			  if ((KeyNext && isKeyEnterUp) || count == 3)
				  Scene_BeginScene1();
			  break;
	}
	default:
	{
			   sceneID = 6;
			   isKeyEnterUp = false;
			   count = 0;
			   last_time = GetTickCount();
			   background->setImage(TextureManager::GetInstance()->GetScene1Texture());
			   map->Reset(sceneID);
			   Camera::GetInstance()->Camera_Init(1609, 0, 320, 223, 0, 0, 0, 0, NULL);
			   break;
	}
	}
}

void Scene::Scene_BeginScene1()
{
	switch (sceneID)
	{
	case 7:
	{
			  Camera::GetInstance()->Camera_Run();
			  DWORD now = GetTickCount();
			  if ((now - last_time > 3000) || (KeyNext && isKeyEnterUp))
				  Scene_Scene1();
			  break;
	}
	default:
	{
			   sceneID = 7;
			   isKeyEnterUp = false;
			   count = 0;
			   last_time = GetTickCount();
			   begin = GetTickCount();
			   background->setImage(TextureManager::GetInstance()->GetScene1Texture());
			   map->Reset(sceneID);
			   Camera::GetInstance()->Camera_Init(1929, 0, 320, 224, 0, 0, 0, 0, NULL);
			   break;
	}
	}
}

void Scene::Scene_Scene1()
{
	switch (sceneID)
	{
	case 8:
	{
			  GameSound::getInstance()->stop(BACKGROUND_MUSIC);

			  if (Aladdin::GetInstance()->isDie)
			  {
				  GameSound::getInstance()->stop(GAME1_MUSIC);
				  GameSound::getInstance()->play(DIE_MUSIC);
				  Scene_Die();
				  return;
			  }
			  Aladdin::GetInstance()->ProcessInput();
			  map->Run(sceneID);
			  Camera::GetInstance()->Camera_Run();
			  aladdin_bloodbar->setPosition(Camera::GetInstance()->x + 40, Camera::GetInstance()->y + 30);
			  aladdin_bloodbar->ProcessInput();
			  aladdin_apple->setPosition(Camera::GetInstance()->right() - 30, Camera::GetInstance()->bottom() - 30);
			  aladdin_ruby->setPosition(Camera::GetInstance()->right() - 60, Camera::GetInstance()->bottom() - 30);
			  aladdin_life->setPosition(Camera::GetInstance()->left() + 30, Camera::GetInstance()->bottom() - 30);
			  if (Aladdin::GetInstance()->left() > 4700 && Aladdin::GetInstance()->bottom() < 4309)
				  Scene_Next();
			  break;
	}
	default:
	{
			   GameSound::getInstance()->play(GAME1_MUSIC, true);

			   last_sceneID = sceneID;
			   sceneID = 8;
			   if (last_sceneID != 14)
			   {
				   Aladdin::GetInstance()->setPosition(200, 4600);
			   }
			   background->setImage(TextureManager::GetInstance()->GetScene1Texture());
			   Camera::GetInstance()->Camera_Init(0, 0, 320, 224, 4, 4769, 4095, 4782, Aladdin::GetInstance());
			   break;
	}
	}
}

void Scene::Scene_Next()
{
	switch (sceneID)
	{
	case 9:
	{
			  Aladdin::GetInstance()->ProcessInput();
			  map->Run(sceneID);
			  Camera::GetInstance()->Camera_Run();
			  DWORD now = GetTickCount();
			  if (now - last_time > 3000 || (KeyNext && isKeyEnterUp))
			  {
				  if (last_sceneID == 8)
					  Scene_BeginSceneBoss();
				  else
					  Scene_Finish();
			  }
			  break;
	}
	default:
	{
			   GameSound::getInstance()->stop(GAME1_MUSIC);
			   GameSound::getInstance()->stop(GAME2_MUSIC);

			   GameSound::getInstance()->play(NEXT_MUSIC);

			   last_sceneID = sceneID;
			   sceneID = 9;
			   last_time = GetTickCount();
			   background->setImage(TextureManager::GetInstance()->GetScene1Texture());
			   map->Reset(sceneID);
			   Camera::GetInstance()->Camera_Init(2249, 0, 320, 223, 0, 0, 0, 0, NULL);
			   Aladdin::GetInstance()->setPosition(2567, 200);
			   Aladdin::GetInstance()->direction = true;
			   Aladdin::GetInstance()->RunNext();
			   break;
	}
	}
}

void Scene::Scene_BeginSceneBoss()
{
	switch (sceneID)
	{
	case 10:
	{
			   Camera::GetInstance()->Camera_Run();
			   DWORD now = GetTickCount();
			   if (now - last_time > 3000 || (KeyNext && isKeyEnterUp))
				   Scene_SceneBoss();
			   break;
	}
	default:
	{
			   sceneID = 10;
			   isKeyEnterUp = false;
			   last_time = GetTickCount();
			   background->setImage(TextureManager::GetInstance()->GetScene1Texture());
			   map->Reset(sceneID);
			   Camera::GetInstance()->Camera_Init(1929, 0, 320, 224, 0, 0, 0, 0, NULL);
			   break;
	}
	}
}

void Scene::Scene_SceneBoss()
{
	if (sceneID == 11)
	{
		if (Aladdin::GetInstance()->isDie)
		{
			Scene_Die();
			return;
		}
		Aladdin::GetInstance()->ProcessInput();
		if (mapboss->Run(sceneID))
		{
			Scene_Next();
			return;
		}
		Camera::GetInstance()->Camera_Run();
		aladdin_bloodbar->setPosition(Camera::GetInstance()->x + 40, Camera::GetInstance()->y + 30);
		aladdin_bloodbar->ProcessInput();
		aladdin_apple->setPosition(Camera::GetInstance()->right() - 30, Camera::GetInstance()->bottom() - 30);
		aladdin_ruby->setPosition(Camera::GetInstance()->right() - 60, Camera::GetInstance()->bottom() - 30);
		aladdin_life->setPosition(Camera::GetInstance()->left() + 30, Camera::GetInstance()->bottom() - 30);
	}
	else
	{
		GameSound::getInstance()->play(GAME2_MUSIC, true);

		last_sceneID = sceneID;
		sceneID = 11;
		if (last_sceneID != 14)
		{
			Camera::GetInstance()->resetList();
			Aladdin::GetInstance()->setPosition(200, 740);
			Aladdin::GetInstance()->initx = 200;
			Aladdin::GetInstance()->inity = 740;
			Aladdin::GetInstance()->Stand();
		}
		background->setImage(TextureManager::GetInstance()->GetSceneBossTexture());
		Camera::GetInstance()->Camera_Init(0, 0, 320, 224, 0, 960, 557, 960, Aladdin::GetInstance());
	}
}

void Scene::Scene_Finish()
{
	switch (sceneID)
	{
	case 12:
	{
			   Aladdin::GetInstance()->ProcessInput();
			   Camera::GetInstance()->Camera_Run();
			   DWORD now = GetTickCount();
			   if (now - last_time > 3000 || (KeyNext && isKeyEnterUp))
				   Scene_TheEnd();
			   break;
	}
	default:
	{
			   GameSound::getInstance()->play(THEEND_MUSIC);
			   sceneID = 12;
			   isKeyEnterUp = false;
			   last_time = GetTickCount();
			   back = TextureManager::GetInstance()->GetFinishTexture();
			   Camera::GetInstance()->Camera_Init(0, 0, 320, 224, 0, 0, 0, 0, NULL);
			   Aladdin::GetInstance()->setPosition(50, 160);
			   Aladdin::GetInstance()->Fly();
			   break;
	}
	}
}

void Scene::Scene_TheEnd()
{
	switch (sceneID)
	{
	case 13:
	{
			   Camera::GetInstance()->Camera_Run();
			   Aladdin::GetInstance()->ProcessInput();
			   if (KeyNext && isKeyEnterUp)
			   {
				   Aladdin::GetInstance()->resetProper();
				   Scene_Options0();
			   }
			   break;
	}
	default:
	{
			   sceneID = 13;
			   isKeyEnterUp = false;
			   back = TextureManager::GetInstance()->GetTheEndTexture();
			   Camera::GetInstance()->Camera_Init(0, 0, 320, 224, 0, 0, 0, 0, NULL);
			   Aladdin::GetInstance()->setPosition(250, 120);
			   Aladdin::GetInstance()->Hug();
			   break;
	}
	}
}

void Scene::Scene_Die()
{
	switch (sceneID)
	{
	case 14:
	{
			   map->Run(sceneID);
			   Aladdin::GetInstance()->ProcessInput();
			   Camera::GetInstance()->Camera_Run();
			   if (!Aladdin::GetInstance()->isDie)
			   {
				   if (last_sceneID == 8)
				   {
					   Scene_Scene1();
					   return;
				   }
				   if (last_sceneID == 11)
				   {
					   Scene_SceneBoss();
					   return;
				   }
			   }
			   if (Aladdin::GetInstance()->isDead)
			   {
				   Aladdin::GetInstance()->resetProper();
				   Scene_Options0();
			   }
			   break;
	}
	default:
	{
			   last_sceneID = sceneID;
			   sceneID = 14;
			   Aladdin::GetInstance()->setPosition(2729, 150);
			   background->setImage(TextureManager::GetInstance()->GetScene1Texture());
			   map->Reset(sceneID);
			   Camera::GetInstance()->Camera_Init(2569, 0, 320, 223, 0, 0, 0, 0, NULL);
			   break;
	}
	}
}

void Scene::Scene_Render()
{
	switch (sceneID)
	{
	case 8: case 0: case 1: case 2: case 3: case 9: case 14:
	{
				//Vẽ các đối tượng trong map
				map->Render(GameTime);
				//Vẽ aladdin
				Aladdin::GetInstance()->Render(GameTime);
				break;
	}
	case 11:
	{
			   //Vẽ các đối tượng trong map
			   mapboss->Render(GameTime);
			   //Vẽ aladdin
			   Aladdin::GetInstance()->Render(GameTime);
			   break;
	}
	case 12: case 13:
	{
				 //Vẽ aladdin
				 Aladdin::GetInstance()->Render(GameTime);
				 break;
	}
	}
}

void Scene::RenderBack(LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DSURFACE9 backbuffer)
{
	switch (sceneID)
	{
	case 0:
	{
			  background->Render(0, 0, 0, 0, 4784, 4784);
			  if (!isHide)
				  background->Render(108, 140, 138, 262, 70, 14);
			  background->Render(94, 88, 10, 253 + count * 40, 107, 30);
			  DWORD end = GetTickCount();
			  if (end - begin > 60)
			  {
				  count++;
				  begin = end;
			  }
			  if (count == 7)
			  {
				  isHide = false;
				  count = 0;
			  }		  	  
			  break;
	}
	case 3:
	{
			  background->Render(640, 0, 640, 223, 320, 223);
			  //background->Render(0, 0, 0, 0, 4784, 4784);
			  break;
	}
	case 4:
	{
			  background->Render(1289, 0, 1289, count * 223, 320, 223);
			  if (count == 11)
			  {
				  isHide = true;
				  count = 3;
			  }
			  else
			  {
				  DWORD end = GetTickCount();
				  if (end - begin > 100)
				  {
					  if (!isHide)
						  count++;
					  else
						  count--;
					  begin = end;
				  }
			  }	  
			  //background->Render(0, 0, 0, 0, 4784, 4784);
			  break;
	}
	case 6:
	{
			  background->Render(1609, 0, 1609, count * 223, 320, 223);
			  DWORD now = GetTickCount();
			  if (now - last_time > 1500)
			  {
				  count++;
				  last_time = now;
			  }
			  
			  //background->Render(0, 0, 0, 0, 4784, 4784);
			  break;
	}
	case 7:
	{
			  background->Render(1929, 0, 1929, count * 223, 320, 223);
			  DWORD end = GetTickCount();
			  if (end - begin > 100)
			  {
				  count++;
				  begin = end;
			  }
			  if (count == 4)
				  count = 0;

			  //background->Render(0, 0, 0, 0, 4784, 4784);
			  break;
	}
	case 8:
	{
			  for (int i = 0; i < 4; i++)
			  {
				  if (cloud_dx[i] + 0.7 / (i + 1) + Camera::GetInstance()->w < 512)
					  cloud_dx[i] += 0.7 / (i + 1);
				  else
					  cloud_dx[i] = 1;
			  }

			  float const_x = Camera::GetInstance()->x;
			  float const_y = Camera::GetInstance()->top();
			  float const_w = Camera::GetInstance()->w;

			  background->Render(const_x, const_y - 1, cloud_dx[0], 4789, const_w, 16);
			  background->Render(const_x, const_y + 15, cloud_dx[1], 4811, const_w, 24);
			  background->Render(const_x, const_y + 38, cloud_dx[2], 4840, const_w, 32);
			  background->Render(const_x, const_y + 69, cloud_dx[3], 4877, const_w, 24);

			  background->Render(const_x, const_y + 92, 1, 4906, const_w, 16);
			  background->Render(const_x, const_y + 107, 1, 4927, const_w, 8);
			  background->Render(const_x, const_y + 114, 1, 4940, const_w, 16);
			  background->Render(const_x, const_y + 129, 1, 4961, const_w, 24);
			  background->Render(const_x, const_y + 152, 1, 4990, const_w, 64);

			  background->Render(0, 0, 0, 0, 4784, 4784);
			  break;
	}
	case 11:
	{
			   background->Render(0, 0, 0, 0, 960, 960);
			   break;
	}
	case 12: case 13:
	{
				 d3ddev->StretchRect(back, NULL, backbuffer, NULL, D3DTEXF_NONE);
				 break;
	}
	default:
	{
			   background->Render(0, 0, 0, 0, 4784, 4784);
			   break;
	}
	}
}

void Scene::RenderBack1()
{
	switch (sceneID)
	{
	case 5:
	{

			  DWORD now = GetTickCount();
			  if (now - last_time > 2000 || !isHide)
			  {
				  background->Render(962, 199, 960, 0, 320, 196);
				  isHide = false;
			  }
			  break;
	}
	case 8:
	{
			  background->Render(0, 4091, 0, 4784, 4773, 694);
			  break;
	}
	}
}

void Scene::RenderSceneInfoPlayer()
{
	switch (sceneID)
	{
	case 8: case 11:
	{
				aladdin_bloodbar->Render(GameTime);
				aladdin_life->Render(GameTime);

				if (Aladdin::GetInstance()->numberofapples > 0)
				{
					aladdin_apple->Render(GameTime);
					drawFont(numberofapples, 585, 390, 35, 25, Aladdin::GetInstance()->numberofapples);
				}
				if (Aladdin::GetInstance()->numberofrubies > 0)
				{
					aladdin_ruby->Render(GameTime);
					drawFont(numberofrubies, 529, 390, 35, 25, Aladdin::GetInstance()->numberofrubies);
				}
				drawFont(numberoflifes, 75, 398, 35, 25, Aladdin::GetInstance()->numberoflifes);
				drawFont(score, 500, 20, 100, 50, Aladdin::GetInstance()->score);
				break;
	}
	}
}

//draw font
void Scene::drawFont(ID3DXFont*font, float x, float y, float width, float height, int value)
{
	//set position of font 
	RECT rect;
	rect.top = (int)y;
	rect.left = (int)x;
	rect.bottom = (int)y + height;
	rect.right = (int)x + width;

	char intStr[20];
	_itoa_s(value, intStr, 10);
	//strcpy_s(intStr, status.c_str());
	if (font != score)
		font->DrawText(NULL, intStr, -1, &rect, DT_TOP | DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	else
		font->DrawText(NULL, intStr, -1, &rect, DT_TOP | DT_RIGHT, D3DCOLOR_XRGB(255, 255, 255));
}

Scene::~Scene()
{
	if (background != NULL){ delete background; background = nullptr; }
	if (map != NULL){ delete map; map = nullptr; }
	if (mapboss != NULL){ delete mapboss; mapboss = nullptr; }
	if (aladdin_bloodbar != NULL){ delete aladdin_bloodbar; aladdin_bloodbar = nullptr; }
	if (aladdin_apple != NULL){ delete aladdin_apple; aladdin_apple = nullptr; }
	if (aladdin_ruby != NULL){ delete aladdin_ruby; aladdin_ruby = nullptr; }
	if (aladdin_life != NULL){ delete aladdin_life; aladdin_life = nullptr; }
	if (numberofapples != NULL){ numberofapples->Release(); }
	if (numberofrubies != NULL){ numberofrubies->Release(); }
	if (numberoflifes != NULL){ numberoflifes->Release(); }
	if (score != NULL){ score->Release(); }
}
