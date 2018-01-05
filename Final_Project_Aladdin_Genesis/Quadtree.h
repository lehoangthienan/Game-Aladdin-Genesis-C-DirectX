#ifndef _QUADTREE_H
#define _QUADTREE_H

#include "Collision.h"
#include "Quadnode.h"
#include "Camera.h"

using namespace std;

class QuadTree
{
private:

	RECT rect;
	vector<BaseObject*> list_Obj;
	vector<QuadNode*> listNodeInView;
	vector<BaseObject*> listObjectInView;
	QuadNode *root_node;
	vector<BaseObject*> listObj;

public:
	//contructor of QuadTree class
	QuadTree();
	QuadTree(RECT rect);

	//lấy danh sách toàn bộ đối tượng từ map
	void getListObject(vector<BaseObject*> listObj);
	
	//lấy node gốc
	QuadNode* getRootNode();
	void FindNodeInView(QuadNode* node);
	void Delete(QuadNode* node);

	//destructor of QuadTree class
	~QuadTree();
};

#endif