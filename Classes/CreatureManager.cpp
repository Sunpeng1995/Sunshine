#include "CreatureManager.h"
#define CREATURE_SCALE 0.5

CreatureManager::~CreatureManager() {
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
}

bool CreatureManager::init() {
	addTouchListener();
	addOtherCreature();
	std::thread thr = std::thread(&CreatureManager::initNetwork, this);
	thr.detach();
	//boost::thread thrd(boost::bind(&CreatureManager::initNetwork, this));
	//thrd.join();

	this->scheduleUpdate();
	return true;
}

void CreatureManager::update(float delta) {
	float dis = stage->getPosition().getDistance(my_creature->getPosition());
	float sc = stage->getScale();
	if (dis >= stage->getContentSize().width * sc * 0.5 && my_creature->getState() != STATIC) {
// 		my_creature->setState(STATIC);//fuck it!!!
	}
	sentData();
	recevData();
}

void CreatureManager::createMyCreature() {
	Size visiblesize = Director::getInstance()->getWinSize();
	my_creature = Creature::create("Body.png");
	my_creature->setPosition(visiblesize.width / 4, visiblesize.height / 2);
	my_creature->setScale(CREATURE_SCALE);
	this->addChild(my_creature, 1);
}

void CreatureManager::addOtherCreature() {
	Size visiblesize = Director::getInstance()->getWinSize();
	auto creature = Creature::create("Body.png");
	creature->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	creature->setScale(CREATURE_SCALE);
	other_creatures.push_back(creature);
	this->addChild(creature,2);
}

Creature* CreatureManager::getMyCreature() {
	return my_creature;
}

void CreatureManager::addTouchListener() {
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event) {
		getMyCreature()->setState(MOVE);
		return true;
	};
	listener->onTouchMoved = [=](Touch* touch, Event* event) {

	};
	listener->onTouchEnded = [=](Touch* touch, Event* event) {
		getMyCreature()->setState(STOP);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void CreatureManager::addStage(Sprite* st) {
	this->stage = st;
}

void CreatureManager::initNetwork() {
	this->network = new Network(GlobalArgs::getInstance()->getGamemode());
	log("aaa");
	network->getIOS()->run();
	log("aaa");
}

std::string CreatureManager::formatData(std::vector<float> list) {
	char format_char[1024];
	sprintf(format_char, "%.3f#%.3f#%.1f", list[0], list[1], list[2]);
	std::string format_str = format_char;
	return format_str;
}

std::vector<float> CreatureManager::unformatData(std::string str) {
	std::vector<std::string> tokens;
	std::vector<float> result;
	boost::split(tokens, str, boost::is_any_of("#"));
	for (int i = 0; i < 3; i++) {
		result.push_back(atof(tokens[i].c_str()));
	}
	return result;
}

void CreatureManager::sentData() {
	std::vector<float> net_data;
	net_data.push_back(my_creature->getPositionX());
	net_data.push_back(my_creature->getPositionY());
	net_data.push_back(my_creature->getAngle());
	network->set_sent_data(formatData(net_data));
}

void CreatureManager::recevData() {
	std::vector<float> net_data;
	if (network->get_rec_data() != "") {
		net_data = unformatData(network->get_rec_data());
		for (int i = 0; i < other_creatures.size(); i++) {
			other_creatures[i]->setPositionX(net_data[0]);
			other_creatures[i]->setPositionY(net_data[1]);
			other_creatures[i]->setAngle(-net_data[2]);
			other_creatures[i]->setRotation(-net_data[2]);
		}
	}
}