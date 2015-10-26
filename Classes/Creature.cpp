#include "Creature.h"

Creature* Creature::create(std::string filename) {
	auto pRet = new(std::nothrow) Creature();
	if (pRet && pRet->init(filename)) {
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
		return NULL;
	}
}

bool Creature::init(std::string filename)
{
	bindSpirte(filename);
	addEye();
	addUpdateCallBackFunc([=](){
		setAngle(getAngle() > 360.0 ? 0.0 : getAngle() + 1.0);
		setRotation(getAngle());
	});
	return true;
}

void Creature::addEye()
{
	Size bodysize = getSprite()->getContentSize();
	eye = Sprite::create("eye.png");
	eye->setPosition(bodysize.width * 0.8, bodysize.height * 0.5);
	getSprite()->addChild(eye, 1);
}

void Creature::setAngle(float a) {
	this->angle = a;
}

float Creature::getAngle() {
	return angle;
}

