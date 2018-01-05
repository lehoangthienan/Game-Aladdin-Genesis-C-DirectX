#include "QuadTree.h"

//contructor of quadtree class
QuadTree::QuadTree()
{
	root_node = new QuadNode();
}

QuadTree::QuadTree(RECT rect)
{
	this->rect = rect;
}

//lấy danh sách toàn bộ đối tượng từ map
void QuadTree::getListObject(vector<BaseObject*> listObj)
{
	this->listObj = listObj;
}

void QuadTree::FindNodeInView(QuadNode* node)
{
	if (node == NULL)
		return;

	//kiểm tra node có nằm trong khoảng của camera hay không
	if (node->getRect() && !Collision::AABBCheck(Camera::GetInstance(), node->getRect()))
		return;

	if (node->getNumNode() == 4)
	{
		FindNodeInView(node->tl);
		FindNodeInView(node->tr);
		FindNodeInView(node->bl);
		FindNodeInView(node->br);
		return;
	}
	if (node->getListObjInNode().size() == 0)
		return;

	//đưa toàn bộ đối tượng có trong node lá hiện thời vào ListNode của camera
	Camera::GetInstance()->ImportObject(node->getListObjInNode());

}

QuadNode* QuadTree::getRootNode()
{
	return root_node;
}

void QuadTree::Delete(QuadNode* node)
{
	if (node->tl != NULL)
		Delete(node->tl);
	if (node->tr != NULL)
		Delete(node->tr);
	if (node->bl != NULL)
		Delete(node->tl);
	if (node->br != NULL)
		Delete(node->tl);
	if (node->tl == NULL&&node->tr == NULL&&node->bl == NULL&&node->br == NULL)
	{
		delete node;
		node = nullptr;
	}
}

QuadTree::~QuadTree()
{}
