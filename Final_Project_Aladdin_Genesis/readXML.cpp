#include "readXML.h"
using namespace std;
using namespace rapidxml;

void readXML::getAttrSprite(string xmlFilePath, int SpriteID, int &x, int &y, int &width, int &height, int &x_anchor, int &y_anchor)
{
	//character type default to char
	xml_document<> doc;

	//Load file xml
	ifstream file(xmlFilePath);
	stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	string content(buffer.str());
	doc.parse<0>(&content[0]);

	//create node equivalent to xml's tag
	xml_node<> *pRoot = doc.first_node();
	xml_node<> *pSpritesNode = pRoot->first_node("Sprites");
	xml_node<> *pSpriteNode = 0;

	xml_node<>*pAnimations = pRoot->first_node("Animations");
	xml_node<>*pAnimation = pAnimations->first_node("Animation");
	xml_node<>* pFrames = pAnimation->first_node("Frames");
	xml_node<>* pFrame = pFrames->first_node("Frame");

	//search Sprite from Id sprite
	for (xml_node<> *pNode = pSpritesNode->first_node("Sprite"); pNode; pNode = pNode->next_sibling())
	{
		if (pNode->last_attribute("Id")->value() == to_string(SpriteID))
		{
			pSpriteNode = pNode;
			break;
		}
		pFrame = pFrame->next_sibling();
	}

	xml_node<>*pCoordinatesNode = pSpriteNode->first_node("Coordinates");
	x = atoi(pCoordinatesNode->first_node("X")->value());
	y = atoi(pCoordinatesNode->first_node("Y")->value());
	width = atoi(pCoordinatesNode->first_node("Width")->value());
	height = atoi(pCoordinatesNode->first_node("Height")->value());
	x_anchor = atoi(pFrame->first_attribute("OffSetX")->value());
	y_anchor = atoi(pFrame->first_attribute("OffSetY")->value());

	doc.clear();
}
