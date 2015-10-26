#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"
USING_NS_CC;

class Entity :public Node {
public:
	CREATE_FUNC(Entity);
	static Entity* create(std::string filename);
	void bindSpirte(std::string filename);
	Sprite* getSprite();

	virtual bool init();
	virtual void update(float delta);
	void addUpdateCallBackFunc(std::function<void()> call);
private:
	Sprite* m_sprite;
	
	std::vector<std::function<void()>> callVec;
};

#endif