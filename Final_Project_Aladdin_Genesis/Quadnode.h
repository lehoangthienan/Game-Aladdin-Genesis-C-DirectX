#ifndef _QUADNODE_H
#define _QUADNODE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <vector>
#include "BaseObject.h"

class QuadNode
{
private:
	int nodeID;
	float x, y, w, h;
	int num_node;
	int num_obj;

	vector<BaseObject*> listObjectInNode;
	BaseObject *rect;

public:
	//Các node con tương ứng của node hiện tại (top-left, top-right, bottom-left, bottom-right)
	QuadNode *tl, *tr, *bl, *br;

	//contructor of Quadnode class
	QuadNode();

	void LoadNode(fstream *f, vector<BaseObject*> listObj);

	void CreateSubNode();

	//lấy vùng bao quanh của node hiện thời
	BaseObject* getRect();

	//lấy giá trị node con
	QuadNode* getChildNode(int);

	//lấy giá trị của một số thuộc tính của lớp quadnode (nodeid, số lượng node, số lượng đối tượng)
	int getNodeID();
	int getNumObj();
	int getNumNode();

	vector<BaseObject*> getListObjInNode();

	//destructor of Quadnode class
	~QuadNode();
};

#endif