#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "GlobalArgs.h"
USING_NS_CC;

class StartScene :public Layer {
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(StartScene);
private:
	void initMenu();
	void exitCallBack(Ref* pSender);
	void startCallBack(Ref* pSender);
	void createCallBack(Ref* pSender);
	void joinCallBack(Ref* pSender);
};

#endif