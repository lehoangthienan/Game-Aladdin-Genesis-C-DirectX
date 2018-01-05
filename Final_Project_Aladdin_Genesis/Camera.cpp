#include "Camera.h"

Camera*Camera::instance = 0;

//lấy instance (con trỏ) camera
Camera*Camera::GetInstance()
{
	if (instance == 0)
	{
		instance = new Camera();
	}
	return instance;
}

//Khởi tạo camera
void Camera::Camera_Init(float x, float y, float w, float h, float limx_left, float limx_right, float limy_top, float limy_bottom, BaseObject *player)
{
	this->w = w;
	this->h = h;
	vx = 0;
	vy = 0;
	this->limx_left = limx_left;
	this->limx_right = limx_right;
	this->limy_top = limy_top;
	this->limy_bottom = limy_bottom;

	if (player == NULL)
	{
		this->x = x;
		this->y = y;
		arx = x + w / 2;
		ary = y + h / 2;
	}
	else
	{
		this->arx = (player->left() + player->right()) / 2;
		this->ary = (player->top() + player->bottom()) / 2;
		this->x = this->arx - w / 2;
		this->y = this->ary - h / 2;
	}
	this->player = player;

	D3DXMatrixOrthoLH(&orthographicMatrix, w, h, 0.0f, 1.0f);
}


//Lấy các loại danh sách (danh sách các đối tượng, danh sách các enemy, ground, item)
vector<BaseObject*>* Camera::GetListObj()
{
	return &ListObj;
}

vector<BaseObject*>* Camera::GetListEnemy()
{
	return &ListEnemy;
}

vector<BaseObject*>* Camera::GetListGround()
{
	return &ListGround;
}

vector<BaseObject*>* Camera::GetListItem()
{
	return &ListItem;
}

vector<BaseObject*>* Camera::GetListOtherObject()
{
	return&ListOtherObject;
}

//Phân loại các đối tượng trong danh sách các đối tượng (ListObj) theo loại va chạm (collType) 
void Camera::AddObjectToListCol()
{
	ListEnemy.clear();
	ListGround.clear();
	ListItem.clear();
	ListOtherObject.clear();

	bool allowAdd;
	for each(BaseObject* o in ListObj)
	{
		switch (o->collType)
		{
		case CollEnemy:
		{
						  allowAdd = true;
						  for each(BaseObject* o2 in ListEnemy)
						  {
							  if (o == o2)
							  {
								  allowAdd = false;
								  break;
							  }
						  }
						  if (allowAdd)
							  ListEnemy.push_back(o);
						  break;
		}
		case CollGround: case CollLine: case CollStair:
		{
							 allowAdd = true;
							 for each(BaseObject* o2 in ListGround)
							 {
								 if (o == o2)
								 {
									 allowAdd = false;
									 break;
								 }
							 }
							 if (allowAdd)
								 ListGround.push_back(o);
							 break;
		}
		case CollItem:
		{
						 allowAdd = true;
						 for each(BaseObject* o2 in ListItem)
						 {
							 if (o == o2)
							 {
								 allowAdd = false;
								 break;
							 }
						 }
						 if (allowAdd)
							 ListItem.push_back(o);
						 break;
		}
		case CollFireCarpet: case CollCamel: case CollRod: case CollRope: case CollCollarBeam: case CollUnknown:
		{
								 allowAdd = true;
								 for each(BaseObject* o2 in ListOtherObject)
								 {
									 if (o == o2)
									 {
										 allowAdd = false;
										 break;
									 }
								 }
								 if (allowAdd)
									 ListOtherObject.push_back(o);
								 break;
		}
		}
	}
}

//Cập nhật vị trí camera
void Camera::UpdatePosition()
{
	this->arx += vx*GameTime;
	this->ary += vy*GameTime;

	x = arx - w / 2;
	y = ary - h / 2;
}

//Thêm đối tượng vào danh sách đối tượng của camera
void Camera::ImportObject(vector<BaseObject*> listObj)
{

	bool allowAdd;
	for each(BaseObject* o1 in listObj)
	{
		allowAdd = true;
		for each(BaseObject* o2 in ListObj)
		{
			if (o1 == o2)
			{
				allowAdd = false;
				break;
			}
		}
		if (allowAdd)
			ListObj.push_back(o1);
	}

}

void Camera::Camera_Run()
{
	if (player != NULL)
	{
		vx = 0;
		if (!(limx_left > x && player->vx <= 0 || player->vx >= 0 && this->right() > limx_right))
		{
			if (player->getLastStatus() != 12 && player->getLastStatus() != 13 && player->getLastStatus() != 14 && player->getLastStatus() != 15)
			{
				if (player->getStatus() != 14 && player->getStatus() != 15)
				{
					if (player->direction)
					{
						if (!(limx_left > x && player->arx + 60 - arx < 0))
							vx = (player->arx + 60 - arx) / 100;
					}
					else
					{
						if (!(this->right() > limx_right && player->arx - 60 - arx > 0))
							vx = (player->arx - 60 - arx) / 100;
					}
				}
				else
				{
					if (!player->direction)
					{
						if (!(limx_left > x && player->arx + 60 - arx < 0))
							vx = (player->arx + 60 - arx) / 100;
					}
					else
					{
						if (!(this->right() > limx_right && player->arx - 60 - arx > 0))
							vx = (player->arx - 60 - arx) / 100;
					}
				}
			}
			else
			{
				if (!(this->right() > limx_right && player->arx - arx > 0) && !(limx_left > x && player->arx - arx < 0))
					vx = (player->arx - arx) / 100;
			}
		}


		if (player->getLastStatus() != 12 && player->getLastStatus() != 13 && player->getLastStatus() != 14 && player->getLastStatus() != 15)
		{
			if (player->vy < 0 && y + vy > limy_top)
			{
				if ((player->top() + player->bottom()) / 2 < this->ary - 100)
					vy -= 0.025f;
				else
					vy = 0;
			}
			else if (player->vy > 0 && limy_bottom > y + h)
			{
				if ((player->top() + player->bottom()) / 2 > this->ary + 20)
					vy = player->vy;
				else
					vy = 0;
			}
			else
				vy = 0;
			
			if (player->vy == 0 || vy == 0)
			{
				
				if (y <= limy_top)
					vy += (limy_top - y) / 100;
				else if (limy_bottom < y + h)
					vy += (limy_bottom - y - h) / 100;
				else if ((player->top() + player->bottom()) / 2 > ary + 10 || (player->top() + player->bottom()) / 2 < ary - 10)
					vy = ((player->top() + player->bottom()) / 2 - ary) / 50;
				else
					vy = 0;
			}
		}
		else
			vy = (player->ary - ary) / 50;

		if (player->getStatus() == 16)
			vx = 0;

		//update position of camera
		UpdatePosition();

	}

	//create matrix
	this->viewMatrix = D3DXMATRIX(
		1.0f, 0, 0, 0,
		0, -1.0f, 0, 0,
		0, 0, 1.0f, 0,
		-arx, ary, 0, 1.0f
		);
}

//set transform with matrixes
void Camera::SetTransform(LPDIRECT3DDEVICE9 d3ddev) const
{
	d3ddev->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
	d3ddev->SetTransform(D3DTS_VIEW, &viewMatrix);
}

//loại va chạm trong camera
void Camera::OnCollision(BaseObject* obj, int nx, int ny)
{
	Collision::PreventMove(this, obj, nx, ny);
}

void Camera::resetList()
{
	GetListObj()->clear();
	GetListEnemy()->clear();
	GetListGround()->clear();
	GetListItem()->clear();
	GetListOtherObject()->clear();
}

//lấy thuộc tính của khung camera trả về bằng kiểu RECT (rectangle) 
RECT Camera::ToRect()
{
	RECT r;
	r.top = y;
	r.bottom = r.top + h;
	r.left = x;
	r.right = r.left + w;

	return r;
}