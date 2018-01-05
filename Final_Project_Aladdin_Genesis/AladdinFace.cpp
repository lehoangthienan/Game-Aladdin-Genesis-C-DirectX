#include "AladdinFace.h"
#define ALADDINFACE_XMLFILEPATH "Xml/AladdinFace.xml"

//contructor of AladdinFace class
AladdinFace::AladdinFace()
{
	objType = OBJAladdinFace;
}

//init object
void AladdinFace::LoadResources()
{
	arx = x + 11;
	ary = y + 12;

	Item::LoadResources();
	animation_rate = 1;
	xmlFilePath = ALADDINFACE_XMLFILEPATH;

	image = new Sprite(TextureManager::GetInstance()->GetItemsTexture(), 0, 0);
}

//destructor of AladdinFace class
AladdinFace::~AladdinFace()
{}
