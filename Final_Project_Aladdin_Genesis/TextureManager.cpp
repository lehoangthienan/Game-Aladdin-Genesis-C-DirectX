#include "TextureManager.h"
#define ALADDIN_IMAGE "Image/Genesis 32X SCD - Aladdin - Aladdin.png"
#define CAMEL_IMAGE "Image/Genesis 32X SCD - Aladdin - Camel.png"
#define CIVILIANENEMIES_IMAGE "Image/Genesis 32X SCD - Aladdin - Civilian Enemies.png"
#define ENEMYDIE_IMAGE "Image/Genesis 32X SCD - Aladdin - Enemy Die.png"
#define ENEMYEXPLOSION_IMAGE "Image/Genesis 32X SCD - Aladdin - Enemy Explosions.png"
#define GUARDS_IMAGE "Image/Genesis 32X SCD - Aladdin - Guards.png"
#define ITEMACTIVED_IMAGE "Image/Genesis 32X SCD - Aladdin - Item Actived.png"
#define ITEMS_IMAGE "Image/Genesis 32X SCD - Aladdin - Items.png"
#define JAFAR_IMAGE "Image/Genesis 32X SCD - Aladdin - Jafar.png"
#define ROD_IMAGE "Image/Genesis 32X SCD - Aladdin - Rod.png"
#define FALLINGGROUND_IMAGE "Image/Genesis 32X SCD - Aladdin - Falling Ground.png"
#define BLOODBAR_IMAGE	"Image/Genesis 32X SCD - Aladdin - Blood Bar.png"
#define ABU_IMAGE "Image/Genesis 32X SCD - Aladdin - Abu.png"
#define BIRD_IMAGE "Image/Genesis 32X SCD - Aladdin - Iago Enemy.png"
#define GENIE_IMAGE "Image/Genesis 32X SCD - Aladdin - Genie.png"
#define KNIVES_IMAGE "Image/Knives.png"

#define START0_IMAGE "Image/Start0.png"
#define START1_IMAGE "Image/Start1.png"
#define OPTIONS_IMAGE "Image/Options.png"
#define BEGINSCENE1_IMAGE "Image/Begin Scene1.png"
#define SCENE1_IMAGE "Image/Genesis 32X SCD - Aladdin - Agrabah Market.png"
#define SCENEBOSS_IMAGE "Image/Genesis 32X SCD - Aladdin - Boss Space.png"
#define NEXT_IMAGE "Image/Next.png"
#define FINISH_IMAGE "Image/Finish.png"
#define THEEND_IMAGE "Image/TheEnd.png"

TextureManager* TextureManager::instance = 0;

//contructor of Texture manager class
TextureManager::TextureManager()
{
	aladdin_image = 0;
	camel_image = 0;
	civilianenemies_image = 0;
	enemydie_image = 0;
	enemyexplosion_image = 0;
	guards_image = 0;
	itemactived_image = 0;
	items_image = 0;
	jafar_image = 0;
	rod_image = 0;
	bloodbar_image = 0;
	abu_image = 0;
	genie_image = 0;
	bird_image = 0;
	knives_image = 0;

	scene1_image = 0;
	sceneboss_image = 0;
	finish_image = 0;
	theend_image = 0;
}

//get texture manager current instance (get texture manager pointer)
TextureManager* TextureManager::GetInstance()
{
	if (instance == 0)
	{
		instance = new TextureManager();
	}
	return instance;
}


//Tạo các Texture
void TextureManager::CreateTexture(LPDIRECT3DDEVICE9 d3ddev)
{
	srand((unsigned)time(NULL));
	HRESULT res = D3DXCreateSprite(d3ddev, &sprite_handler);

	if (aladdin_image == NULL)
		aladdin_image = LoadTexture(d3ddev, ALADDIN_IMAGE, D3DCOLOR_XRGB(255, 0, 255));
	if (camel_image == NULL)
		camel_image = LoadTexture(d3ddev, CAMEL_IMAGE, D3DCOLOR_XRGB(248, 0, 248));
	if (civilianenemies_image == NULL)
		civilianenemies_image = LoadTexture(d3ddev, CIVILIANENEMIES_IMAGE, D3DCOLOR_XRGB(120, 193, 152));
	if (enemydie_image == NULL)
		enemydie_image = LoadTexture(d3ddev, ENEMYDIE_IMAGE, D3DCOLOR_XRGB(186, 254, 202));
	if (enemyexplosion_image == NULL)
		enemyexplosion_image = LoadTexture(d3ddev, ENEMYEXPLOSION_IMAGE, D3DCOLOR_XRGB(186, 254, 202));
	if (guards_image == NULL)
		guards_image = LoadTexture(d3ddev, GUARDS_IMAGE, D3DCOLOR_XRGB(120, 193, 152));
	if (itemactived_image == NULL)
		itemactived_image = LoadTexture(d3ddev, ITEMACTIVED_IMAGE, D3DCOLOR_XRGB(255, 4, 253));
	if (items_image == NULL)
		items_image = LoadTexture(d3ddev, ITEMS_IMAGE, D3DCOLOR_XRGB(248, 0, 248));
	if (jafar_image == NULL)
		jafar_image = LoadTexture(d3ddev, JAFAR_IMAGE, D3DCOLOR_XRGB(186, 254, 202));
	if (rod_image == NULL)
		rod_image = LoadTexture(d3ddev, ROD_IMAGE, D3DCOLOR_XRGB(255, 0, 255));
	if (fallingground_image == NULL)
		fallingground_image = LoadTexture(d3ddev, FALLINGGROUND_IMAGE, D3DCOLOR_XRGB(255, 0, 255));
	if (bloodbar_image == NULL)
		bloodbar_image = LoadTexture(d3ddev, BLOODBAR_IMAGE, D3DCOLOR_XRGB(255, 0, 255));
	if (abu_image == NULL)
		abu_image = LoadTexture(d3ddev, ABU_IMAGE, D3DCOLOR_XRGB(255, 0, 255));
	if (bird_image == NULL)
		bird_image = LoadTexture(d3ddev, BIRD_IMAGE, D3DCOLOR_XRGB(84, 109, 142));
	if (genie_image == NULL)
		genie_image = LoadTexture(d3ddev, GENIE_IMAGE, D3DCOLOR_XRGB(255, 0, 255));
	if (knives_image == NULL)
		knives_image = LoadTexture(d3ddev, KNIVES_IMAGE, D3DCOLOR_XRGB(255, 0, 255));

	if (scene1_image == NULL)
		scene1_image = LoadTexture(d3ddev, SCENE1_IMAGE, D3DCOLOR_XRGB(63, 72, 204));
	if (sceneboss_image == NULL)
		sceneboss_image = LoadTexture(d3ddev, SCENEBOSS_IMAGE, D3DCOLOR_XRGB(255, 0, 255));
}

void TextureManager::CreateSurface(LPDIRECT3DDEVICE9 d3ddev)
{	
	if (finish_image == NULL)
		finish_image = LoadSurface(d3ddev, FINISH_IMAGE, D3DCOLOR_XRGB(255, 0, 255));
	if (theend_image == NULL)
		theend_image = LoadSurface(d3ddev, THEEND_IMAGE, D3DCOLOR_XRGB(255, 0, 255));
}

LPD3DXSPRITE TextureManager::GetSprite_Handler()
{
	return sprite_handler;
}

//Lấy Texture tương ứng với mỗi đối tượng
LPDIRECT3DTEXTURE9 TextureManager::GetAladdinTexture()
{
	return aladdin_image;
}

LPDIRECT3DTEXTURE9 TextureManager::GetCamelTexture()
{
	return camel_image;
}

LPDIRECT3DTEXTURE9 TextureManager::GetCivilianEnemiesTexture()
{
	return civilianenemies_image;
}

LPDIRECT3DTEXTURE9 TextureManager::GetEnemyDieTexture()
{
	return enemydie_image;
}

LPDIRECT3DTEXTURE9 TextureManager::GetEnemyExplosionTexture()
{
	return enemyexplosion_image;
}

LPDIRECT3DTEXTURE9 TextureManager::GetGuardsTexture()
{
	return guards_image;
}

LPDIRECT3DTEXTURE9 TextureManager::GetItemActivedTexture()
{
	return itemactived_image;
}

LPDIRECT3DTEXTURE9 TextureManager::GetItemsTexture()
{
	return items_image;
}

LPDIRECT3DTEXTURE9 TextureManager::GetJafarTexture()
{
	return jafar_image;
}

LPDIRECT3DTEXTURE9 TextureManager::GetRodTexture()
{
	return rod_image;
}

LPDIRECT3DTEXTURE9 TextureManager::GetFallingGroundTexture()
{
	return fallingground_image;
}

LPDIRECT3DTEXTURE9 TextureManager::GetBloodBarTexture()
{
	return bloodbar_image;
}

LPDIRECT3DTEXTURE9 TextureManager::GetAbuTexture()
{
	return abu_image;
}

LPDIRECT3DTEXTURE9 TextureManager::GetGenieTexture()
{
	return genie_image;
}

LPDIRECT3DTEXTURE9 TextureManager::GetKnivesTexture()
{
	return knives_image;
}

LPDIRECT3DTEXTURE9 TextureManager::GetBirdTexture()
{
	return bird_image;
}


//Các texture và surface background
LPDIRECT3DTEXTURE9 TextureManager::GetScene1Texture()
{
	return scene1_image;
}

LPDIRECT3DTEXTURE9 TextureManager::GetSceneBossTexture()
{
	return sceneboss_image;
}

LPDIRECT3DSURFACE9 TextureManager::GetFinishTexture()
{
	return finish_image;
}

LPDIRECT3DSURFACE9 TextureManager::GetTheEndTexture()
{
	return theend_image;
}

LPDIRECT3DTEXTURE9 TextureManager::LoadTexture(LPDIRECT3DDEVICE9 d3ddev, LPCSTR filePath, D3DCOLOR transcolor)
{
	LPDIRECT3DTEXTURE9 image;
	D3DXIMAGE_INFO info;
	HRESULT result;

	//get Texture image from file
	result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		trace(L"[ERROR] Failed to get information from image file '%s'", filePath);
		return NULL;
	}

	//create texture (image) from file image
	result = D3DXCreateTextureFromFileEx(
		d3ddev,
		filePath,
		info.Width,
		info.Height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transcolor,
		&info,
		NULL,
		&image);

	//check create texture
	if (result != D3D_OK)
	{
		trace(L"[ERROR] Failed to create texture from file '%s'", filePath);
		return NULL;
	}
	return image;
}

LPDIRECT3DSURFACE9 TextureManager::LoadSurface(LPDIRECT3DDEVICE9 d3ddev, LPCSTR filePath, D3DCOLOR transcolor)
{
	LPDIRECT3DSURFACE9 image = NULL;
	D3DXIMAGE_INFO info;
	HRESULT result;
	//get width and height from bitmap file
	result = D3DXGetImageInfoFromFile(filePath, &info);
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
		filePath, //source filename
		NULL, //source rectangle
		D3DX_DEFAULT, //controls how image is filtered
		transcolor, //for transparency (0 for none)
		NULL); //source image info (usually NULL)
	//make sure file was loaded okay
	if (result != D3D_OK)
		return NULL;
	return image;
}

//destructor of Texture manager class
TextureManager::~TextureManager()
{
	if (instance != NULL){ delete instance; instance = nullptr; }
	if (sprite_handler != NULL){ delete sprite_handler; sprite_handler = nullptr; }
	if (aladdin_image != NULL)
		aladdin_image->Release();
	if (camel_image != NULL)
		camel_image->Release();
	if (civilianenemies_image != NULL)
		civilianenemies_image->Release();
	if (enemydie_image != NULL)
		enemydie_image->Release();
	if (enemyexplosion_image == NULL)
		enemyexplosion_image->Release();
	if (guards_image != NULL)
		guards_image->Release();
	if (itemactived_image != NULL)
		itemactived_image->Release();
	if (items_image != NULL)
		items_image->Release();
	if (jafar_image != NULL)
		jafar_image->Release();
	if (rod_image != NULL)
		rod_image->Release();
	if (fallingground_image != NULL)
		fallingground_image->Release();
	if (bloodbar_image != NULL)
		bloodbar_image->Release();
	if (abu_image!=NULL)
		abu_image->Release();
	if (genie_image != NULL)
		genie_image->Release();
	if (bird_image != NULL)
		bird_image->Release();
	if (knives_image != NULL)
		knives_image->Release();

	if (scene1_image != NULL)
		scene1_image->Release();
	if (sceneboss_image != NULL)
		sceneboss_image->Release();
	if (finish_image != NULL)
		finish_image->Release();
	if (theend_image != NULL)
		theend_image->Release();
}
