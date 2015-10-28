#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Creature.h"
#include "CreatureManager.h"
USING_NS_CC;

class GameScene :public Layer {
public:
	~GameScene();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
private:
	void initStage();
	void initManager();
private:
	CreatureManager* c_manager;
	Sprite* background;
	Sprite* stage;
};

#endif