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
	this->addChild(menu, 1);

}

void StartScene::exitCallBack(Ref* pSender) {
	Director::getInstance()->end();
}

void StartScene::startCallBack(Ref* pSender) {
	Director::getInstance()->replaceScene(GameScene::createScene());
}