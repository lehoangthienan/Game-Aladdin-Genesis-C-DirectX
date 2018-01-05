#ifndef _MAP_H
#define _MAP_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Quadtree.h"
#include "Ground.h"
#include "Rope.h"
#include "CollarBeam.h"
#include "Camel.h"
#include "Aladdin.h"
#include "Apple.h"
#include "JarThrower.h"
#include "Swordsman.h"
#include "Rod.h"
#include "GenieFace.h"
#include "AbuItem.h"
#include "BlueHeart.h"
#include "GenieJar.h"
#include "Ruby.h"
#include "Lamp.h"
#include "Guard1.h"
#include "Guard2.h"
#include "Guard3.h"
#include "Theft.h"
#include "FireCarpet.h"
#include "FallingGround.h"
#include "Boss.h"
#include "Knives.h"
#include "Genie.h"
#include "Abu.h"
#include "Bird.h"
#include "BloodBar.h"
#include "AladdinFace.h"

using namespace std;

class Map
{
private:
	
	vector<BaseObject*> listObject;
	QuadTree*tree;
	bool isOpenStair1, isOpenStair2, old_isOpenStair1, old_isOpenStair2;

public:
	Map();
	void LoadResource(string ListObjFilePath, string QuadTreeFilePath);
	void GetMapInfo(string path);
	void LoadQuadtreeFromFile(string path);
	BaseObject* Run(int sceneID);
	void Render(int Delta);
	void Release();
	void Reset(int sceneID);
	~Map();
};

#endif