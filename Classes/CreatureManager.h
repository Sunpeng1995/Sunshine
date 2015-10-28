#ifndef __MAIN_GAME_MANAGER_H__
#define __MAIN_GAME_MANAGER_H__

#include "cocos2d.h"
#include "Creature.h"
USING_NS_CC;

class CreatureManager :public Node {
public:
	~CreatureManager();
	CREATE_FUNC(CreatureManager);
	virtual bool init();
	virtual void update(float delta);
	void createMyCreature();
	Creature* getMyCreature();
	void addOtherCreature();
	void addTouchListener();
	void addStage(Sprite* st);
private:
	EventListenerTouchOneByOne* listener;
	Creature* my_creature;
	Sprite* stage;
	std::vector<Creature*> other_creatures;
};



#endif