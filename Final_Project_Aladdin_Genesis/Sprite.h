#ifndef _SPRITE_H
#define _SPRITE_H

#include <cmath>
#include "readXML.h"
#include "TextureManager.h"
#include "Camera.h"

class Sprite
{
protected:
	LPDIRECT3DTEXTURE9 image;

	int index;				//current sprite index
	int firstframe;			//first sprite
	int lastframe;			//last sprite
	bool isActionDone;

public:
	//contructor of sprite class
	Sprite();
	Sprite(LPDIRECT3DTEXTURE9 image, int firstframe, int lastframe);
	Sprite(LPD3DXSPRITE sprite_handler, LPDIRECT3DTEXTURE9 image, int firstframe, int lastframe);

	//draw sprite
	void Render(float position_x, float position_y, float x, float y, float w, float h);
	void Render(std::string xmlFilePath, float &x, float &y, float &w, float &h, float& arx, float& ary, bool direction, int isBlink);
	
	//increase index
	void Next();
	
	//reset index when it equal lastframe
	void Reset();

	//set first frame and last frame
	void setFrame(int firstframe, int lastframe);
	int getFirstFrame();
	int getLastFrame();
	
	//get and set current sprite index
	int getIndex();
	void setIndex(int currentIndex);

	//set texture
	void setImage(LPDIRECT3DTEXTURE9 image);

	//set sprite_handler
	void setSpriteHandler(LPD3DXSPRITE sprite_handler);

	//is animation finish?
	bool isActionFinish();

	//destructor of sprite class
	~Sprite();
};

#endif