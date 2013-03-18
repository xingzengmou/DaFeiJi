#include "GamePlayer.h"

using namespace cocos2d;

GamePlayer::GamePlayer(char *s) {
	this->mysprite = CCSprite::createWithSpriteFrameName(s);
	this->myStreak = CCMotionStreak::create(2,2,2,ccc3(255,0,0), s);
}

void GamePlayer::tick() {

}

void GamePlayer::setPosition(CCPoint myPoint) {
	this->mysprite->setPosition(myPoint);
	this->myStreak->setPosition(myPoint);
}

CCMotionStreak *GamePlayer::getStreak() {
	return this->myStreak;
}

bool GamePlayer::isCollision(GameSprite *testSprite) {
	CCSize ownSize = this->mysprite->getContentSize();
	CCSize otherSize = testSprite->getMySize();
	CCPoint ownp = this->mysprite->getPosition();
	CCPoint otherp = testSprite->getSprite()->getPosition();
	if (abs(ownp.x - otherp.x) <= ownSize.width/2 
		+ otherSize.width/2 && abs(ownp.y-otherp.y) <= ownSize.height/2 + 
		otherSize.height/2) {
			return true;
	}
	return false;
}

bool GamePlayer::collision() {
	return false;
}

CCSize GamePlayer::getMySize() {
	return this->mysprite->getContentSize();
}