#ifndef __MAIN_GAME_MANAGER_H__
#define __MAIN_GAME_MANAGER_H__

#include "cocos2d.h"
#include "Creature.h"
USING_NS_CC;

class CreatureManager :public Node {
public:
	CREATE_FUNC(CreatureManager);
	void createMyCreature();
	Creature* getMyCreature();
	void addOtherCreature();
private:
	Creature* myCreature;
	std::vector<Creature*> otherCreatures;
};



#endif