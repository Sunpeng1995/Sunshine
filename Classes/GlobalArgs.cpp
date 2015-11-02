#include "GlobalArgs.h"

GlobalArgs* GlobalArgs::g_global_args = nullptr;

GlobalArgs* GlobalArgs::getInstance() {
	if (g_global_args == nullptr) {
		g_global_args = new GlobalArgs();
		g_global_args->autorelease();
		g_global_args->retain();
	}
	return g_global_args;
}

void GlobalArgs::setGamemode(int a) {
	gamemode = a;
}

int GlobalArgs::getGamemode() {
	return gamemode;
}