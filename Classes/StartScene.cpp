#include "StartScene.h"

Scene* StartScene::createScene() {
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);

	return scene;
}

bool StartScene::init() {
	Size visiblesize = Director::getInstance()->getVisibleSize();
	Sprite* bg = Sprite::create("startbg.png");
	bg->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	bg->setScale(2.0);
	this->addChild(bg);

	initMenu();

	return true;
}

void StartScene::initMenu() {
	Size visiblesize = Director::getInstance()->getVisibleSize();
	auto menu1 = MenuItemImage::create("menu_start1.png", "menu_start2.png", CC_CALLBACK_1(StartScene::startCallBack, this));
	menu1->setPosition(visiblesize.width / 2, visiblesize.height * 3 / 4);

	auto menu2 = MenuItemImage::create("menu_exit1.png", "menu_exit2.png", CC_CALLBACK_1(StartScene::exitCallBack, this));
	menu2->setPosition(visiblesize.width / 2, visiblesize.height / 4);

	auto menu = Menu::create(menu1, menu2, NULL);
	menu->setPosition(Vec2::ZERO);
	menu->setName("main_menu");
	this->addChild(menu, 1);

	auto gamemode_create = MenuItemImage::create("gamemode_create1.png", "gamemode_create2.png", CC_CALLBACK_1(StartScene::createCallBack, this));
	gamemode_create->setPosition(visiblesize.width * 0.5, visiblesize.height * 3 / 4);
	gamemode_create->setTag(0);

	auto gamemode_join = MenuItemImage::create("gamemode_join1.png", "gamemode_join2.png", CC_CALLBACK_1(StartScene::joinCallBack, this));
	gamemode_join->setPosition(visiblesize.width * 0.5, visiblesize.height / 4);
	gamemode_join->setTag(1);

	auto gamemode_menu = Menu::create(gamemode_create, gamemode_join, NULL);
	gamemode_menu->setPosition(Vec2::ZERO);
	gamemode_menu->setVisible(false);
	gamemode_menu->setName("gamemode_menu");
	this->addChild(gamemode_menu, 1);
}

void StartScene::exitCallBack(Ref* pSender) {
	Director::getInstance()->end();
}

void StartScene::startCallBack(Ref* pSender) {
	getChildByName("main_menu")->setVisible(false);
	getChildByName("gamemode_menu")->setVisible(true);
}

void StartScene::createCallBack(Ref* pSender) {
	GlobalArgs::getInstance()->setGamemode(0);
	Director::getInstance()->replaceScene(GameScene::createScene());
}

void StartScene::joinCallBack(Ref* pSender) {
	GlobalArgs::getInstance()->setGamemode(1);
	Director::getInstance()->replaceScene(GameScene::createScene());
}