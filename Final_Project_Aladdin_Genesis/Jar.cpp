#include "Jar.h"
#define JAR_XMLFILEPATH "Xml/Jar.xml"

//contructor of Jar class
Jar::Jar()
{
	objType = OBJJar;
}

//init object
void Jar::LoadResources()
{
	arx = x + 14;
	ary = y + 10;

	status = _JarStatus::FALLING;
	animation_rate = 10;
	xmlFilePath = JAR_XMLFILEPATH;

	Enemy::LoadResources();
	image = new Sprite(TextureManager::GetInstance()->GetCivilianEnemiesTexture(), 0, 5);
}

//process input
void Jar::ProcessInput()
{
	if (isDie)
	{
		Die();
		return;
	}
	
	switch (status)
	{
	case _JarStatus::BURST:
		Burst();
		return;
	default:
		Fall();
		break;
	}

	//simulate fall down (gravity)
	vy += 0.1f;
}

//collision
void Jar::OnCollision(BaseObject* obj, float normalx, float normaly)
{
	switch (obj->collType)
	{
	case CollGround: case CollStair:
		Collision::PreventMove(this, obj, normalx, normaly);
		break;
	}

}

//interserct
void Jar::OnInterSerct(BaseObject* obj)
{
	if (obj->collType == CollGround || obj->collType == CollStair||obj->collType == CollLine)
	{
		GameSound::getInstance()->play(POT_MUSIC);
			Burst();
	}
	if (obj->collType == CollApple || obj->objType == OBJSpittle)
	{
		Die();
		status = _JarStatus::DIE;
	}
	if (obj->collType == CollAladdin && Aladdin::GetInstance()->getStatus() == _AladdinStatus::CUTTING)
	{
		Die();
		status = _JarStatus::DIE;
	}
}

//action of Jar
void Jar::Fall()
{
	switch (status)
	{
	case _JarStatus::FALLING:
		break;
	default:
	{
			   status = _JarStatus::FALLING;
			   image->setFrame(0, 5);
			   animation_rate = 15;
			   break;
	}
	}
}

void Jar::Burst()
{
	switch (status)
	{
	case _JarStatus::BURST:
	{
				  if (image->isActionFinish())
				  {
					  isDead = true;
					  jarThrower->deleteJar(this);
				  }
				  break;
	}
	default:
	{
			   status = _JarStatus::BURST;
			   image->setFrame(6, 13);
			   animation_rate = 10;
			   vx = 0;
			   vy = 0;
			   isDie = true;
			   ary += h / 2;
			   break;
	}
	}
}

void Jar::Die()
{
	Enemy::Die();
	if (isDead)
		jarThrower->deleteJar(this);
}

//get status aladdin
int Jar::getStatus()
{
	return status;
}

//get jar thrower
void Jar::GetJarThrower(JarThrower*obj)
{
	jarThrower = obj;
}

//destructor of Jar class
Jar::~Jar()
{}
