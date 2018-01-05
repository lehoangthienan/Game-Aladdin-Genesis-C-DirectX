#include "CollarBeam.h"


CollarBeam::CollarBeam()
{
	isDead = false;
}

void CollarBeam::setObjectFromID()
{
	collType = CollCollarBeam;
}

//init object
void CollarBeam::LoadResources(){}

//sprite redering
void CollarBeam::Render(int Delta){}

CollarBeam::~CollarBeam()
{}
