#include "Map.h"

Map::Map()
{}

void Map::LoadResource(string ListObjFilePath, string QuadTreeFilePath)
{
	GetMapInfo(ListObjFilePath);
	LoadQuadtreeFromFile(QuadTreeFilePath);
	for each(BaseObject* obj in listObject)
	{
		obj->LoadResources();
	}

	isOpenStair1 = false;
	isOpenStair2 = false;
	old_isOpenStair1 = isOpenStair1;
	old_isOpenStair2 = isOpenStair2;
}

void Map::GetMapInfo(string path)
{
	BaseObject* obj = 0;
	fstream f;
	f.open(path);

	//lấy số lượng đối có trong map (đọc tự file AgrabahMarket.txt)
	int AmountOfObject = 0;
	f >> AmountOfObject;

	//Vòng lặp tạo danh sách các đối tượng trong map
	for (int count = 0; count < AmountOfObject; count++)
	{
		int ObjectID;
		f >> ObjectID;
		switch (ObjectID)
		{
		case OBJGround: case OBJStair: case OBJLine:
			obj = new Ground();
			break;
		case OBJRope:
			obj = new Rope();
			break;
		case OBJCollarBeam:
			obj = new CollarBeam();
			break;
		case OBJCamel:
			obj = new Camel();
			break;
		case OBJJarThrower:
			obj = new JarThrower();
			break;
		case OBJSwordsman:
			obj = new Swordsman();
			break;
		case OBJApple:
			obj = new Apple();
			break;
		case OBJRod:
			obj = new Rod();
			break;
		case OBJGenieFace:
			obj = new GenieFace();
			break;
		case OBJAbuItem:
			obj = new AbuItem();
			break;
		case OBJBlueHeart:
			obj = new BlueHeart();
			break;
		case OBJGenieJar:
			obj = new GenieJar();
			break;
		case OBJRuby:
			obj = new Ruby();
			break;
		case OBJLamp:
			obj = new Lamp();
			break;
		case OBJGuard1:
			obj = new Guard1();
			break;
		case OBJGuard2:
			obj = new Guard2();
			break;
		case OBJGuard3:
			obj = new Guard3();
			break;
		case OBJTheft:
			obj = new Theft();
			break;
		case OBJFireCarpet:
			obj = new FireCarpet();
			break;
		case OBJFallingGround:
			obj = new FallingGround();
			break;
		case OBJBoss:
			obj = new Boss();
			break;
		case OBJAbu:
			obj = new Abu();
			break;
		case OBJGenie:
			obj = new Genie();
			break;
		case OBJBird:
			obj = new Bird();
			break;
		case OBJKnives:
			obj = new Knives();
			break;
		}
		f >> obj->x;
		f >> obj->y;
		f >> obj->w;
		f >> obj->h;
		switch (ObjectID)
		{
		case OBJGuard1: case OBJGuard2: case OBJGuard3: case OBJTheft:
		{
							f >> obj->limx_left;
							f >> obj->limx_right;
							break;
		}
		case OBJGenie: case OBJAbu:
		{
						   f >> obj->begin_stat;
						   break;
		}
		}
		obj->initx = obj->x;
		obj->inity = obj->y;
		obj->id = ObjectID;
		obj->_id = count;
		obj->setObjectFromID();
		listObject.push_back(obj);
	}
	f.close();
}

void Map::LoadQuadtreeFromFile(string path)
{
	//Khởi tạo cây quadtree
	tree = new QuadTree();
	fstream file(path);

	//lấy danh sách object
	tree->getListObject(listObject);

	//khởi tạo node gốc
	tree->getRootNode()->LoadNode(&file, listObject);
	file.close();
}

BaseObject* Map::Run(int sceneID)
{
	BaseObject*result = NULL;

	//Tìm khong gian roi nhet doi tuong do vao camera
	tree->FindNodeInView(tree->getRootNode());

	if (sceneID == 8)
	{
		if (2715 <= Aladdin::GetInstance()->arx && Aladdin::GetInstance()->arx <= 2780 && 4715 <= Aladdin::GetInstance()->ary && Aladdin::GetInstance()->ary <= 4765)
		{
			if (old_isOpenStair1 == isOpenStair1)
			{
				isOpenStair1 = !isOpenStair1;
			}
		}
		else
			old_isOpenStair1 = isOpenStair1;

		if (2243 <= Aladdin::GetInstance()->arx && Aladdin::GetInstance()->arx <= 2270 && 4624 <= Aladdin::GetInstance()->ary && Aladdin::GetInstance()->ary <= 4674)
		{
			if (!(!isOpenStair1&&!isOpenStair2))
			{
				if (old_isOpenStair2 == isOpenStair2)
				{
					isOpenStair2 = !isOpenStair2;
					isOpenStair1 = !isOpenStair2;

				}
			}
		}
		else
			old_isOpenStair2 = isOpenStair2;
	}

	//Xử lý các đối tượng trong node trước khi phân loại chúng (xóa những đối tượng không nằm trong camera ra khỏi list,...)
	for (int i = 0; i < Camera::GetInstance()->GetListObj()->size();)//doi tuong nam trong camera, neu checkAABB sai thi se xoa ra khoi camera
	{
		BaseObject *obj = Camera::GetInstance()->GetListObj()->at(i);

		if (sceneID == 8)
		{
			if (24 <= obj->_id && obj->_id <= 34)
			{
				obj->isDie = !isOpenStair1;
			}

			if (34 <= obj->_id && obj->_id <= 42)
			{
				obj->isDie = !isOpenStair2;
			}

			if (obj->_id == 34 && isOpenStair1 != isOpenStair2)
				obj->isDie = false;

			if (obj->id == 26 && obj->isDie && Aladdin::GetInstance()->ary > 4600)
			{
				obj->x = obj->initx;
				obj->y = obj->inity;
				obj->resetProper();
			}
		}
		else if (sceneID == 11)
		{
			if (obj->objType == OBJBoss && obj->isDead)
				return obj;
			switch (obj->_id)
			{
			case 3: case 5: case 8: case 10:
			{
						obj->isDie = !listObject.at(6)->getTypeObj();
						break;
			}
			}
		}
		else if (sceneID == 2 || sceneID == 3)
		{
			if (obj->objType == OBJKnives)
			{
				result = obj;
			}
		}

		if (sceneID == 8 || sceneID == 11)
		{
			if ((!Collision::AABBCheck(Camera::GetInstance(), obj) || obj->isDead) && obj->objType != OBJBoss)
			{
				if (sceneID == 11 && obj->objType == OBJApple && obj->isActive && !Collision::AABBCheck(Camera::GetInstance(), obj))
					obj->resetProper();
				Camera::GetInstance()->GetListObj()->erase(Camera::GetInstance()->GetListObj()->begin() + i);
			}
			else
			{
				switch (obj->id)
				{
				case 4: case 6: case 21: case 23:
				{
							for (int j = 0; j < obj->GetList()->size();)
							{
								if (!Collision::AABBCheck(Camera::GetInstance(), obj->GetList()->at(j)))
								{
									BaseObject *obj1 = obj->GetList()->at(j);
									obj->GetList()->erase(obj->GetList()->begin() + j);
									delete obj1;
									obj1 = nullptr;
								}
								else
									j++;
							}
							break;
				}
				}
				i++;
			}
		}
		else
		{
			if (obj->isDead)
			{
				Camera::GetInstance()->GetListObj()->erase(Camera::GetInstance()->GetListObj()->begin() + i);
			}
			else
				i++;
		}
	}

	for (int i = 0; i < Aladdin::GetInstance()->GetList()->size();)
	{
		if (!Collision::AABBCheck(Camera::GetInstance(), Aladdin::GetInstance()->GetList()->at(i)))
		{
			BaseObject *obj = Aladdin::GetInstance()->GetList()->at(i);
			Aladdin::GetInstance()->GetList()->erase(Aladdin::GetInstance()->GetList()->begin() + i);
			delete obj;
			obj = nullptr;
		}
		else
			i++;
	}

	//Phân loại từng đối tượng trong camera
	Camera::GetInstance()->AddObjectToListCol();

	//Chạy process input của các đối tượng đang được xét (nằm trong camera)
	for each (BaseObject* obj in *Camera::GetInstance()->GetListEnemy())
	{
		obj->ProcessInput();
		switch (obj->id)
		{
		case 6: case 7: case 21: case 28:
		{
					for (int i = 0; i < obj->GetList()->size(); i++)
						obj->GetList()->at(i)->ProcessInput();
					break;
		}
		}
	}
	for each (BaseObject* obj in *Camera::GetInstance()->GetListGround())
		obj->ProcessInput();
	for each (BaseObject* obj in *Camera::GetInstance()->GetListItem())
		obj->ProcessInput();
	for each (BaseObject*obj in *Camera::GetInstance()->GetListOtherObject())
	{
		obj->ProcessInput();
		switch (obj->id)
		{
		case 4: case 23:
		{
					for (int i = 0; i < obj->GetList()->size(); i++)
						obj->GetList()->at(i)->ProcessInput();
					break;
		}
		}
	}

	if (sceneID == 8 || sceneID == 11)
	{
		//Chạy process input của các quả táo có trong danh sách táo được aladdin ném ra
		for (int i = 0; i < Aladdin::GetInstance()->GetList()->size(); i++)
			Aladdin::GetInstance()->GetList()->at(i)->ProcessInput();

		//reset các giá trị va chạm của aladdin
		Aladdin::GetInstance()->normalx = 0;
		Aladdin::GetInstance()->normaly = 0;
		Aladdin::GetInstance()->isCollStair = false;

		//Xét va chạm giữa các đối tượng có tương tác với nhau
		//Xét va chạm giữa aladdin với enemy
		for each (BaseObject* obj in *Camera::GetInstance()->GetListEnemy())
		{
			Collision::CheckCollision(Aladdin::GetInstance(), obj);
			for (int i = 0; i < Aladdin::GetInstance()->GetList()->size(); i++)
			{
				Collision::CheckCollision(Aladdin::GetInstance()->GetList()->at(i), obj);
			}
			switch (obj->id)
			{
			case 6: case 7: case 21:
			{
						for (int i = 0; i < Aladdin::GetInstance()->GetList()->size(); i++)
						{
							for (int j = 0; j < obj->GetList()->size(); j++)
								Collision::CheckCollision(Aladdin::GetInstance()->GetList()->at(i), obj->GetList()->at(j));
						}
						for (int i = 0; i < obj->GetList()->size(); i++)
							Collision::CheckCollision(Aladdin::GetInstance(), obj->GetList()->at(i));
						break;
			}
			case 28:
			{
					   for (int i = 0; i < obj->GetList()->size(); i++)
						   Collision::CheckCollision(Aladdin::GetInstance(), obj->GetList()->at(i));
					   break;
			}
			}
		}

		//Xét va chạm giữa Aladdin và các item
		for each (BaseObject* obj in *Camera::GetInstance()->GetListItem())
		{
			Collision::CheckCollision(Aladdin::GetInstance(), obj);
			if (Collision::AABBCheck(Aladdin::GetInstance(), obj) && obj->objType == OBJLamp)
			{
				for each(BaseObject *obj1 in *Camera::GetInstance()->GetListEnemy())
				{
					switch (obj1->id)
					{
					case 4: case 6: case 7: case 21: case 23: case 28:
					{
								for (int j = 0; j < obj1->GetList()->size(); j++)
									obj1->Die();
								break;
					}
					}
					obj1->Die();
				}
			}
		}

		for each (BaseObject* obj in *Camera::GetInstance()->GetListGround())
		{
			Collision::CheckCollision(Aladdin::GetInstance(), obj);
			for each (BaseObject* obj1 in *Camera::GetInstance()->GetListEnemy())
			{
				Collision::CheckCollision(obj1, obj);
				switch (obj1->id)
				{
				case 6: case 7: case 21: case 28:
					for (int i = 0; i < obj1->GetList()->size(); i++)
						Collision::CheckCollision(obj1->GetList()->at(i), obj);
					break;
				}
			}
			for (int i = 0; i < Aladdin::GetInstance()->GetList()->size(); i++)
				Collision::CheckCollision(Aladdin::GetInstance()->GetList()->at(i), obj);
		}

		for each(BaseObject*obj in *Camera::GetInstance()->GetListOtherObject())
		{
			Collision::CheckCollision(Aladdin::GetInstance(), obj);
			for each(BaseObject* obj1 in *Camera::GetInstance()->GetListEnemy())
			{
				switch (obj->id)
				{
				case 4:
				{
						  for (int i = 0; i < obj->GetList()->size(); i++)
							  Collision::CheckCollision(obj1, obj->GetList()->at(i));
						  break;
				}
				case 23:
					Collision::CheckCollision(obj1, obj);
					break;
				}
			}
			switch (obj->id)
			{
			case 23:
			{
					   for (int i = 0; i < obj->GetList()->size(); i++)
						   Collision::CheckCollision(Aladdin::GetInstance(), obj->GetList()->at(i));
					   break;
			}
			}
		}
	}
	return result;
}

void Map::Render(int Delta)
{
	//render từng đối tượng lên màn hình
	for each (BaseObject* obj in *Camera::GetInstance()->GetListEnemy())
	{
		if (!obj->isDead)
			obj->Render(Delta);
		switch (obj->id)
		{
		case 6: case 7: case 21: case 28:
		{
					for (int i = 0; i < obj->GetList()->size(); i++)
						obj->GetList()->at(i)->Render(Delta);
					break;
		}
		}
	}
	for each (BaseObject* obj in *Camera::GetInstance()->GetListGround())
	{
		if (!obj->isDead)
			obj->Render(Delta);
	}
	for each (BaseObject* obj in *Camera::GetInstance()->GetListItem())
	{
		if (!obj->isDead)
			obj->Render(Delta);
	}
	for each (BaseObject*obj in *Camera::GetInstance()->GetListOtherObject())
	{
		if (!obj->isDead)
			obj->Render(Delta);
		switch (obj->id)
		{
		case 4: case 23:
		{
					for (int i = 0; i < obj->GetList()->size(); i++)
						obj->GetList()->at(i)->Render(Delta);
					break;
		}
		}
	}

	//Vẽ táo từ aladdin
	for (int i = 0; i < Aladdin::GetInstance()->GetList()->size(); i++)
		Aladdin::GetInstance()->GetList()->at(i)->Render(Delta);

}

void Map::Release()
{
	//for each (BaseObject * obj in listObject)
	//{
	//	delete obj;
	//	obj = nullptr;
	//}
	//listObject.clear();
	//tree->Delete(tree->getRootNode());
	//if (tree != NULL)
	//	delete tree;
}

void Map::Reset(int sceneID)
{
	switch (sceneID)
	{
	case 0:
	{
			  listObject.at(238)->resetProper();
			  listObject.at(239)->resetProper();
			  listObject.at(240)->isDead = true;
			  listObject.at(241)->isDead = true;
			  listObject.at(242)->isDead = true;
			  listObject.at(243)->isDead = true;
			  break;
	}
	case 1:
	{
			  listObject.at(238)->isDead = true;
			  listObject.at(239)->isDead = true;
			  listObject.at(240)->resetProper();
			  listObject.at(241)->isDead = true;
			  listObject.at(242)->isDead = true;
			  listObject.at(243)->isDead = true;
			  break;
	}
	case 2:
	{
			  listObject.at(238)->isDead = true;
			  listObject.at(239)->isDead = true;
			  listObject.at(240)->isDead = true;
			  listObject.at(241)->resetProper();
			  listObject.at(241)->limy_top = 125;
			  listObject.at(241)->limy_bottom = 143;
			  listObject.at(242)->isDead = true;
			  listObject.at(243)->isDead = true;
			  break;
	}
	case 3:
	{
			  listObject.at(238)->isDead = true;
			  listObject.at(239)->isDead = true;
			  listObject.at(240)->isDead = true;
			  listObject.at(241)->resetProper();
			  listObject.at(241)->ary -= 16;
			  listObject.at(241)->arx -= 32;
			  listObject.at(241)->limy_top = 95;
			  listObject.at(241)->limy_bottom = 191;
			  listObject.at(242)->isDead = true;
			  listObject.at(243)->isDead = true;
			  break;
	}
	case 9:
	{
			  listObject.at(238)->isDead = true;
			  listObject.at(239)->isDead = true;
			  listObject.at(240)->isDead = true;
			  listObject.at(241)->isDead = true;
			  listObject.at(242)->resetProper();
			  listObject.at(243)->isDead = true;
			  break;
	}
	case 14:
	{
			   listObject.at(238)->isDead = true;
			   listObject.at(239)->isDead = true;
			   listObject.at(240)->isDead = true;
			   listObject.at(241)->isDead = true;
			   listObject.at(242)->isDead = true;
			   listObject.at(243)->resetProper();
			   break;
	}
	}
}

Map::~Map()
{
	for each (BaseObject * obj in listObject)
	{
		delete obj;
		obj = nullptr;
	}
	listObject.clear();
}
