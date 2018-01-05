#ifndef _JAR_H
#define _JAR_H

#include "JarThrower.h"

class JarThrower;

namespace _JarStatus
{
	enum JarStatus
	{
		FALLING,
		BURST,
		DIE
	};
}

class Jar :public Enemy
{
private:
	JarThrower *jarThrower;
	_JarStatus::JarStatus status;
public:
	//contructor of jar class
	Jar();

	//init object
	void LoadResources();

	//process input
	void ProcessInput();
	
	//collision
	void OnCollision(BaseObject* obj, float normalx, float normaly);
	//interserct
	void OnInterSerct(BaseObject* obj);

	//action of camel
	void Burst();
	void Fall();
	void Die();

	//get status apple
	int getStatus();

	//get jar thrower
	void GetJarThrower(JarThrower *obj);

	//destructor of jar class
	~Jar();
};

#endif