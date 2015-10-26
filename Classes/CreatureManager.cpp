#include "CreatureManager.h"
#define CREATURE_SCALE 0.5

void CreatureManager::createMyCreature() {
	Size visiblesize = Director::getInstance()->getWinSize();
	myCreature = Creature::create("Body.png");
	myCreature->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	myCreature->setScale(CREATURE_SCALE);
	this->addChild(myCreature, 1);
}

void CreatureManager::addOtherCreature() {

}

Creature* CreatureManager::getMyCreature() {
	return myCreature;
}