#ifndef __GLOBAL_ARGS_H__
#define __GLOBAL_ARGS_H__

#include "cocos2d.h"
USING_NS_CC;

class GlobalArgs :public Node {
public:
	CREATE_FUNC(GlobalArgs);
	static GlobalArgs* getInstance();
	void setGamemode(int a);
	int getGamemode();
private:
	static GlobalArgs* g_global_args;
	int gamemode;
};

#endif