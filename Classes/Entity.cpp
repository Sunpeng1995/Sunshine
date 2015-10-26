#include "Entity.h"

Entity* Entity::create(std::string filename) {
	Entity* pRet = new(std::nothrow) Entity();
	if (pRet && pRet->init()) {
		pRet->autorelease();
		pRet->bindSpirte(filename);
		return pRet;
	}
	else {
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

void Entity::bindSpirte(std::string filename) {
	m_sprite = Sprite::create(filename);
	this->addChild(m_sprite);
}

Sprite* Entity::getSprite() {
	return m_sprite;
}

bool Entity::init() {
	
	this->scheduleUpdate();
	return true;
}

void Entity::update(float delta) {
	for (auto call : callVec) {
		call();
	}
}

void Entity::addUpdateCallBackFunc(std::function<void()> call) {
	callVec.push_back(call);
}

