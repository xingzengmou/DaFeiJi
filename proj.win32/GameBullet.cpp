#include "GameBullet.h"

using namespace cocos2d;

GameBullet::GameBullet(char *s) {
	this->mysprite = CCSprite::create(s);
	this->state = 0;
}

void GameBullet::tick() {
	switch (this->type) {
	case 0:
		switch (state) {
		case -1:
			break;
		case 0:
			CCPoint ownp = this->mysprite->getPosition();
			this->mysprite->setPosition(ccp(ownp.x, ownp.y + 2));
			break;
		}
		break;
	case 1:
		switch (state) {
		case -1:
			break;
		case 0:
			CCPoint ownp = this->mysprite->getPosition();
			this->mysprite->setPosition(ccp(ownp.x, ownp.y - 2));
		}
		break;
	}
}

void GameBullet::setType(int type) {
	this->type = type;
}

int GameBullet::getType() {
	return this->type;
}

void GameBullet::setPosition(CCPoint myPoint) {
	this->mysprite->setPosition(myPoint);
}

CCMotionStreak *GameBullet::getStreak() {
	return this->myStreak;
}

bool GameBullet::collision(GamePlayer *testSprite) {
	return false;
}

CCSize GameBullet::getMySize() {
	return this->mysprite->getContentSize();
}