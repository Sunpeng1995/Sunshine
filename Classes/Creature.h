#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "cocos2d.h"
#include "Entity.h"
USING_NS_CC;

enum CreatureState { STATIC, STOP, MOVE };

class Creature :public Entity {
public:
	static Creature* create(std::string filename);
	virtual bool init(std::string filename);
	virtual void update(float delta);
	void addEye();
	void setAngle(float a);
	float getAngle();
	void setState(CreatureState st);
	CreatureState getState();
private:
	Sprite* eye;
	CreatureState state = STATIC;
	void move();
	/*the direction that entity faces*/
	float angle = 0.0;
};


#endif