#ifndef _JARTHROWER_H
#define _JARTHROWER_H

#include "Enemy.h"
#include "Jar.h"

namespace _JarThrowerStatus
{
	enum JarThrowerStatus
	{
		THROWING,
		NOTMOVING,
		DIE
	};
}

class Jar;

class JarThrower : public Enemy
{
private:
	_JarThrowerStatus::JarThrowerStatus status;
	vector<BaseObject*>listJar;
	bool isCreateJar;

public:
	//contructor of jar thrower class
	JarThrower();

	//init object
	void LoadResources();

	//process input
	void ProcessInput();

	//collision
	void OnCollision(BaseObject* obj, float normalx, float normaly);
	//interserct
	void OnInterSerct(BaseObject* obj);

	//action of camel
	void Throw();
	void Move();
	void Die();

	//get status JarThrower
	int getStatus();

	//handle jar
	void createJar();
	vector<BaseObject*>* GetList();
	void deleteJar(BaseObject* jar);

	//change and reset frame size
	void changeFrameSize(BaseObject*obj);
	void resetFrameSize(BaseObject*obj);

	//destructor of jar thrower class
	~JarThrower();
};

#endif