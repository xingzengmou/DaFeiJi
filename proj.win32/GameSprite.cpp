#include "GameSprite.h"

using namespace cocos2d;

GameSprite::GameSprite() {}

GameSprite::~GameSprite() {}

GameSprite::GameSprite(char *s) {
	this->mysprite = CCSprite::createWithSpriteFrameName(s);
}

void GameSprite::tick() {

}

void GameSprite::setPosition(CCPoint point) {
	this->mysprite->setPosition(point);
}

CCSprite *GameSprite::getSprite() {
	return this->mysprite;
}

void GameSprite::setState(int myState) {
	this->state = myState;
}

int GameSprite::getState() {
	return this->state;
}

bool GameSprite::collision() {
	return false;
}

CCSize GameSprite::getMySize() {
	return this->mysprite->getContentSize();
}
