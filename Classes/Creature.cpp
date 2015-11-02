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

	this->scheduleUpdate();
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

void Creature::move() {
	float factor = Director::getInstance()->getVisibleSize().height / 500.0 * 5;
	auto point = getPosition();
	float dx = cos(angle / 180 * 3.1415926);
	float dy = sin(angle / 180 * 3.1415926);
	this->setPosition(point.x + dx * factor, point.y + dy * factor);
}

void Creature::update(float delta) {
	if (state == STOP) {
		setAngle(getAngle() >= 357.0 ? 0.0 : getAngle() + 3.0);
		setRotation(0 - getAngle());
	}
	else if (state == MOVE) {
		move();
	}
	else if (state = STATIC){
	}
}

void Creature::setState(CreatureState st) {
	state = st;
}

CreatureState Creature::getState() {
	return state;
}
