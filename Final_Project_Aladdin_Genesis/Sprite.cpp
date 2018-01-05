#include "Sprite.h"

//contructor of sprite class
Sprite::Sprite()
{
	this->image = NULL;
	this->firstframe = 0;
	this->lastframe = 0;
	index = firstframe;
}

Sprite::Sprite(LPDIRECT3DTEXTURE9 image, int firstframe, int lastframe)
{
	this->image = image;
	this->firstframe = firstframe;
	this->lastframe = lastframe;
	index = firstframe;
}

void Sprite::Render(float position_x, float position_y, float x, float y, float w, float h)
{
	//start randering
	TextureManager::GetInstance()->GetSprite_Handler()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	//set the sprite's rect for drawing
	RECT srcRect;

	//set rectangle of sprite
	srcRect.left = x;
	srcRect.top = y;
	srcRect.right = srcRect.left + w;
	srcRect.bottom = srcRect.top + h;

	D3DXVECTOR3 v3_position(position_x, position_y, 0);
	TextureManager::GetInstance()->GetSprite_Handler()->Draw(image, &srcRect, NULL, &v3_position, D3DCOLOR_XRGB(255, 255, 255));

	//stop randering
	TextureManager::GetInstance()->GetSprite_Handler()->End();
}

void Sprite::Render(std::string xmlFilePath, float &x, float &y, float &w, float &h, float& arx, float& ary, bool direction, int isBlink)
{		
	//start randering
	TextureManager::GetInstance()->GetSprite_Handler()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	//set the sprite's rect for drawing
	RECT srcRect;
	int spritesheet_x, spritesheet_y, anchor_x, anchor_y, spritesheet_width, spritesheet_height;

	//get old matrix before draw sprite 
	D3DXMATRIX oldMt;
	TextureManager::GetInstance()->GetSprite_Handler()->GetTransform(&oldMt);

	//get position of sprite in spritesheet in xml_file
	readXML::getAttrSprite(xmlFilePath, index, spritesheet_x, spritesheet_y, spritesheet_width, spritesheet_height, anchor_x, anchor_y);

	//update width, height
	w = (float)spritesheet_width;
	h = (float)spritesheet_height;

	//update x, y depend on arx, ary
	x = (float)(arx - anchor_x);
	y = (float)(ary - anchor_y);

	//create vector to update sprite's position
	D3DXVECTOR3 v3_position(x, y, 0);

	if (direction == false)
	{
		//set correct position of x and y
		x = (float)(arx - w + anchor_x);
		y = (float)(ary - anchor_y);

		D3DXMATRIX newMt;
		D3DXVECTOR2 center;
		center = D3DXVECTOR2(arx, ary);

		D3DXVECTOR2 rotate = D3DXVECTOR2(-1.0f, 1.0f);
		D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
		D3DXMATRIX finalMt = newMt * oldMt;
		TextureManager::GetInstance()->GetSprite_Handler()->SetTransform(&finalMt);

	}

	if (isBlink != 1)
	{
		//set rectangle of sprite
		srcRect.left = spritesheet_x;
		srcRect.top = spritesheet_y;
		srcRect.right = srcRect.left + spritesheet_width;
		srcRect.bottom = srcRect.top + spritesheet_height;

		//draw the sprite
		TextureManager::GetInstance()->GetSprite_Handler()->Draw(image, &srcRect, NULL, &v3_position, D3DCOLOR_XRGB(255, 255, 255));
	}

	//set old matrix after draw sprite
	TextureManager::GetInstance()->GetSprite_Handler()->SetTransform(&oldMt);

	//stop randering
	TextureManager::GetInstance()->GetSprite_Handler()->End();
}


//increase index
void Sprite::Next()
{
	//index = (index % firstframe + 1) % (lastframe - firstframe + 1) + firstframe;
	if (index == lastframe)
	{
		Reset();
		isActionDone = true;
	}
	else
	{
		if (firstframe <= lastframe)
			index++;
		else
			index--;
	}
}

//reset index when it equal lastframe
void Sprite::Reset()
{
	index = firstframe;
}

//set first frame and last frame
void Sprite::setFrame(int firstframe, int lastframe)
{
	this->firstframe = firstframe;
	this->lastframe = lastframe;
	Reset();
	isActionDone = false;
}

//get firstframe
int Sprite::getFirstFrame()
{
	return firstframe;
}

//get lastframe
int Sprite::getLastFrame()
{
	return lastframe;
}

//get index
int Sprite::getIndex()
{
	return index;
}

//set index
void Sprite::setIndex(int currentIndex)
{
	index = currentIndex;
}

//set texture
void Sprite::setImage(LPDIRECT3DTEXTURE9 image)
{
	this->image = image;
}

bool Sprite::isActionFinish()
{
	return isActionDone;
}

//destructor of sprite class
Sprite::~Sprite()
{}
