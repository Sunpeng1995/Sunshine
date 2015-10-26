#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "cocos2d.h"
#include "Entity.h"
USING_NS_CC;

class Creature :public Entity {
public:
	static Creature* create(std::string filename);
	virtual bool init(std::string filename);
	void addEye();
	void setAngle(float a);
	float getAngle();

private:
	Sprite* eye;

	/*the direction that entity faces*/
	float angle = 0.0;
};


#endif