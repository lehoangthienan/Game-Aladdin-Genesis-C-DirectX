#include "Quadnode.h"

//contructor of Quadnode class
QuadNode::QuadNode()
{
	rect = NULL;
}

//Khởi tạo node lá
void QuadNode::CreateSubNode()
{
	this->tl = new QuadNode();
	this->tr = new QuadNode();
	this->bl = new QuadNode();
	this->br = new QuadNode();
}

//Xử lý node (lấy giá trị từ file, thêm đối tượng vào danh sách nếu nó là node lá)
void QuadNode::LoadNode(fstream *f, vector<BaseObject*> listObj)
{
	if (rect == NULL)
		rect = new BaseObject();

	//lấy thuộc tính của node từ file txt
	(*f) >> rect->x;
	(*f) >> rect->y;
	(*f) >> rect->w;
	(*f) >> rect->h;
	(*f) >> num_node;
	(*f) >> num_obj;

	//nếu node không có đối tượng thì return
	if (num_node == 0 && num_obj == 0)
	{
		return;
	}

	//nếu node có node con thì khởi tạo là load dữ liệu của node con đó lên  
	if (num_node == 4)
	{
		CreateSubNode();
		tl->LoadNode(f, listObj);
		tr->LoadNode(f, listObj);
		bl->LoadNode(f, listObj);
		br->LoadNode(f, listObj);
	}
	//nếu node là node lá thì load các đối tượng trong node lên list
	else
	{
		for (int i = 0; i < num_obj; i++)
		{
			//lấy id của từng đối có trong node
			int obj_id; 
			(*f) >> obj_id;
			listObjectInNode.push_back(listObj.at(obj_id));
		}
	}
}

//lấy vùng bao quanh của node hiện thời
BaseObject* QuadNode::getRect()
{
	return rect;
}

//lấy danh sách các đối tượng trong node
vector<BaseObject *> QuadNode::getListObjInNode()
{
	return listObjectInNode;
}

//lấy giá trị của một số thuộc tính của lớp quadnode (nodeid, số lượng node, số lượng đối tượng)
int QuadNode::getNodeID()
{
	return nodeID;
}

int QuadNode::getNumNode()
{
	return num_node;
}

int QuadNode::getNumObj()
{
	return num_obj;
}

//destructor of quadnode class
QuadNode::~QuadNode()
{
	if (rect != NULL)
	{
		delete rect;
		rect = nullptr;
	}
}

