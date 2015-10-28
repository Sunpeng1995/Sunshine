#include "CreatureManager.h"
#define CREATURE_SCALE 0.5

CreatureManager::~CreatureManager() {
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
}

bool CreatureManager::init() {
	addTouchListener();
	addOtherCreature();
	this->scheduleUpdate();
	return true;
}

void CreatureManager::update(float delta) {
	float dis = stage->getPosition().getDistance(my_creature->getPosition());
	float sc = stage->getScale();
	if (dis >= stage->getContentSize().width * sc * 0.5 && my_creature->getState() != STATIC) {
		my_creature->setState(STATIC);//fuck it!!!
	}
}

void CreatureManager::createMyCreature() {
	Size visiblesize = Director::getInstance()->getWinSize();
	my_creature = Creature::create("Body.png");
	my_creature->setPosition(visiblesize.width / 4, visiblesize.height / 2);
	my_creature->setScale(CREATURE_SCALE);
	this->addChild(my_creature, 1);
}

void CreatureManager::addOtherCreature() {
	Size visiblesize = Director::getInstance()->getWinSize();
	auto creature = Creature::create("Body.png");
	creature->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	creature->setScale(CREATURE_SCALE);
	other_creatures.push_back(creature);
	this->addChild(creature,2);
}

Creature* CreatureManager::getMyCreature() {
	return my_creature;
}

void CreatureManager::addTouchListener() {
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event) {
		getMyCreature()->setState(MOVE);
		return true;
	};
	listener->onTouchMoved = [=](Touch* touch, Event* event) {

	};
	listener->onTouchEnded = [=](Touch* touch, Event* event) {
		getMyCreature()->setState(STOP);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void CreatureManager::addStage(Sprite* st) {
	this->stage = st;
}