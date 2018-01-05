#ifndef _BASEOBJECT_H
#define _BASEOBJECT_H

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include "GameSound.h"

#define DISAPPEAR_XMLFILEPATH "Xml/Disappear.xml"
#define SWORD_XMLFILEPATH "Xml/Sword.xml"
#define SPITTLE_XMLFILEPATH "Xml/Camel.xml"
#define STAR_XMLFILEPATH "xml/Star.xml"
#define BOSS_XMLFILEPATH "xml/Boss.xml"
#define ITEMACTIVED_XMLFILEPATH "Xml/ItemActived.xml"
#define ROD_XMLFILEPATH "Xml/Rod.xml"
#define FALLINGGROUND_XMLFILEPATH "Xml/FallingGround.xml"
#define ENEMYDIE_XMLFILEPATH "Xml/EnemyDie.xml"
#define BLOODBAR_XMLFILEPATH "Xml/BloodBar.xml"

using namespace std;

enum CollisionType
{
	CollGround,
	CollRope,
	CollCollarBeam,
	CollStair,
	CollCamel,
	CollApple,
	CollLine,
	CollAladdin,
	CollEnemy,
	CollItem,
	CollRod,
	CollFireCarpet,
	CollStar,
	CollUnknown
};

enum ObjectType
{
	OBJGround,
	OBJRope,
	OBJCollarBeam,
	OBJStair,
	OBJCamel,
	OBJApple,
	OBJJarThrower,
	OBJSwordsman,
	OBJRod,
	OBJItem,
	OBJSpittle,
	OBJSword,
	OBJJar,
	OBJAbuItem,
	OBJBlueHeart,
	OBJGenieFace,
	OBJGenieJar,
	OBJLamp,
	OBJRuby,
	OBJGuard1,
	OBJGuard2,
	OBJGuard3,
	OBJTheft,
	OBJFireCarpet,
	OBJFire,
	OBJLine,
	OBJFallingGround,
	OBJAladdin,
	OBJBoss,
	OBJStar,
	OBJAladdinFace,
	OBJAbu,
	OBJKnives,
	OBJBird,
	OBJGenie
};

class BaseObject
{
public:
	int id, _id;
	//vị trí ban đầu của các đối tượng
	float initx, inity;
	//active dùng cho các đối tượng có kiểu va chạm là Item
	bool isDie, isDead, isActive; 
	float w, h;
	float x, y;
	float limx_left, limx_right, limy_bottom, limy_top;
	//Tọa độ điểm neo
	float arx, ary;
	//Vận tốc theo các trục Ox, Oy của đối tượng
	float vx, vy;
	CollisionType collType;
	ObjectType objType;
	//Hướng có khả năng va chạm
	float normalx, normaly;
	//Hướng của đối tượng true nếu hướng phải, false nếu hướng trái
	bool direction;
	//Trạng thái ban đầu của đối tượng
	int begin_stat;

public:
	//contructor of BaseObject class
	BaseObject();
	BaseObject(float x, float y, float w, float h);

	//init object
	virtual void LoadResources();
	//process input
	virtual void ProcessInput();
	//sprite redering
	virtual void Render(int Delta);
	//set type object from object's id
	virtual void setObjectFromID();
	virtual void OnCollision(BaseObject*obj, float normalx, float normaly);
	virtual void OnInterSerct(BaseObject*obj);

	void setPosition(float arx, float ary);

	//top and bottom side, return y and y + height
	float top();
	float bottom();
	//left and right side, return x and x + width
	float left();
	float right();

	//get list object
	virtual vector<BaseObject*>* GetList();

	//change and reset frame size
	virtual void changeFrameSize(BaseObject*obj);
	virtual void resetFrameSize(BaseObject*obj);

	//when object die
	virtual void Die();

	//get status of object
	virtual int getStatus();
	virtual int getLastStatus();

	virtual void resetProper();

	//get style of object
	virtual int getTypeObj();

	//destructor of BaseObject class
	~BaseObject();
};

#endif