#ifndef _CAMERA_H
#define _CAMERA_H

#include "Collision.h"

class Camera : public BaseObject
{
private:
	static Camera* instance;
	BaseObject *player;
	vector<BaseObject*> ListObj;
	vector<BaseObject*> ListEnemy;
	vector<BaseObject*> ListGround;
	vector<BaseObject*> ListItem;
	vector<BaseObject*> ListOtherObject;

	D3DXMATRIX orthographicMatrix;
	D3DXMATRIX viewMatrix;

public:

	static Camera* GetInstance();
	void Camera_Init(float x, float y, float w, float h, float limx_left, float limx_right, float limy_top, float limy_bottom, BaseObject *player);
	vector<BaseObject*>* GetListObj();
	vector<BaseObject*>* GetListEnemy();
	vector<BaseObject*>* GetListGround();
	vector<BaseObject*>* GetListItem();
	vector<BaseObject*>* GetListOtherObject();

	void ImportObject(vector<BaseObject*> listObj);
	void AddObjectToListCol();
	void UpdatePosition();
	void Camera_Run();
	void OnCollision(BaseObject* obj, int nx, int ny);
	void SetTransform(LPDIRECT3DDEVICE9 d3ddev) const;
	void resetList();
	RECT ToRect();
};

#endif