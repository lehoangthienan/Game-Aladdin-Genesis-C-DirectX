#ifndef _READXML_H
#define _READXML_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "rapidxml-1.13\rapidxml.hpp"

class readXML
{

public:
	/*static void readxmldoc(std::string xmlFilePath);*/
	static void getAttrSprite(std::string xmlFilePath,int SpriteID, int &x, int &y, int &width, int &height, int &x_anchor, int &y_anchor);
};

#endif