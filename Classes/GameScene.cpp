#include "GameScene.h"

GameScene::~GameScene() {
}

Scene* GameScene::createScene() {
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	
	return scene;
}

bool GameScene::init() {
	initStage();
	initManager();
	return true;
}

void GameScene::initStage() {
	Size visiblesize = Director::getInstance()->getVisibleSize();

	background = Sprite::create();
	background->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	this->addChild(background, 0);

	stage = Sprite::create("Stage.png");
	stage->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	stage->setScale(MIN(visiblesize.width / stage->getContentSize().width, visiblesize.height / stage->getContentSize().height));
	this->addChild(stage, 1);
	
}

void GameScene::initManager() {
	c_manager = CreatureManager::create();
	c_manager->createMyCreature();
	c_manager->getMyCreature()->scheduleUpdate();
	c_manager->addStage(stage);
	this->addChild(c_manager, 1);
}
