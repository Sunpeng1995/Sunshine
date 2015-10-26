#ifndef __MANAGER_BASE_H__
#define __MANAGER_BASE_H__

#include "cocos2d.h"
USING_NS_CC;

class ManagerBase :public Node {
public:
	virtual bool init();
	virtual void update(float delta) {};
	static ManagerBase* getInstance();
private:
	static ManagerBase* g_manager;
};

#endif