#include "GameEnemy.h"

using namespace cocos2d;

GameEnemy::GameEnemy(char *s) {
	this->mysprite = CCSprite::create(s);
	this->mysprite->setPosition(ccp(122,450));
	this->bezier1.controlPoint_1 = CCPointMake(-50, 300);
	this->bezier1.controlPoint_2 = CCPointMake(494, 150);
	this->bezier1.endPosition = CCPointMake(122, -20);
	this->bezier2.controlPoint_1 = CCPointMake(294, 300);
	this->bezier2.controlPoint_2 = CCPointMake(-50, 150);
	this->bezier2.endPosition = CCPointMake(122, -20);
	this->chooseFlyType();
	this->state = 0;
	this->bulletTick = 0;
}

void GameEnemy::setDead() {
	this->mysprite->stopAllActions();
	this->mysprite->setVisible(false);
	this->state = -1;
	this->bulletTick = 0;
}

void GameEnemy::chooseFlyType() {
	type = CCRANDOM_0_1() * 5;
	switch (type) {
	case 0:
		mysprite->initWithFile("e2.png");
		this->bezierTo1 = CCBezierTo::create(5, this->bezier1);
		this->mysprite->runAction(this->bezierTo1);
		break;
	case 1:
		mysprite->initWithFile("e2.png");
		bezierTo1 = CCBezierTo::create(5, bezier1);
		mysprite->runAction(bezierTo1);
		break;
	case 2:
		mysprite->initWithFile("e4.png");
		actionTo1 = CCMoveTo::create(2, CCPointMake(30, 300));
		actionTo2 = CCMoveTo::create(2, CCPointMake(214, 150));
		actionTo3 = CCMoveTo::create(1, CCPointMake(122, -20));
		mysprite->runAction(CCSequence::create(actionTo1, actionTo2, actionTo3, NULL));
		break;
	case 3:
		mysprite->initWithFile("e5.png");
		actionTo1 = CCMoveTo::create(2, CCPointMake(30, 300));
		actionTo2 = CCMoveTo::create(2, CCPointMake(30, 150));
		actionTo3 = CCMoveTo::create(1, CCPointMake(122, -20));
		mysprite->runAction(CCSequence::create(actionTo1, actionTo2, actionTo3, NULL));
		break;
	case 4:
		mysprite->initWithFile("e6.png");
		actionTo1 = CCMoveTo::create(5, CCPointMake(122, -20));
		mysprite->runAction(actionTo1);
		break;
	}
}

void GameEnemy::restart() {
	mysprite->setPosition(ccp(122, 450));
	mysprite->setVisible(true);
	chooseFlyType();
	state = 0;
	bulletTick = 0;
}

void GameEnemy::tick() {
	switch (state) {
	case -1:
		break;
	case 0:
		CCPoint myPoint = mysprite->getPosition();
		if (myPoint.y <= -20) {
			mysprite->stopAllActions();
			restart();
		} else {
			if (bulletTick >= 60) {
				bulletTick = 0;
			} else {
				bulletTick ++;
			}
		}
		break;
	}
}

void GameEnemy::setPosition(CCPoint mypoint) {
	mysprite->setPosition(mypoint);
}

int GameEnemy::getBulletTick() {
	return bulletTick;
}

bool GameEnemy::isCollision(GameSprite *testsprite) {
	CCSize ownSize = mysprite->getContentSize();
	CCSize othersize = testsprite->getMySize();
	CCPoint ownp = mysprite->getPosition();
	CCPoint otherp = testsprite->getSprite()->getPosition();
	if (abs(ownp.x - otherp.x) <= ownSize.width / 2 + othersize.width / 2
		&& abs(ownp.y - otherp.y) <= ownSize.height / 2 + othersize.height / 2) {
			return true;
	}
	return false;
}

bool GameEnemy::collision(GamePlayer *testsprite) {
	CCSize ownSize = mysprite->getContentSize();
	CCSize othersize = testsprite->getMySize();
	CCPoint ownp = mysprite->getPosition();
	CCPoint otherp = testsprite->getSprite()->getPosition();
	if (abs(ownp.x - otherp.x) <= ownSize.width / 2
		+ othersize.width / 2 
		&&  abs(ownp.y - otherp.y) <= ownSize.height / 2 + othersize.height / 2) {
			if (ownp.y + ownSize.height / 2 <= otherp.y - othersize.height / 2) {
				otherp.y = ownp.y + ownSize.height / 2 + othersize.height / 2;
				testsprite->setPosition(ccp(otherp.x, otherp.y));
				return true;
			}

			if (ownp.y + ownSize.height / 2 >= otherp.y + othersize.height / 2 
				&& ownp.y - ownSize.height / 2 <= otherp.y + othersize.height / 2) {
					otherp.y = ownp.y - ownSize.height / 2 - othersize.height / 2;
					testsprite->setPosition(ccp(otherp.x, otherp.y));
					return true;
			}

			if (ownp.x + ownSize.width / 2 >= otherp.x - othersize.width / 2
				&&  ownp.x - ownSize.width / 2 <= otherp.x - othersize.width / 2) {
					otherp.x = ownp.x + ownSize.width / 2 + othersize.width / 2;
					testsprite->setPosition(ccp(otherp.x, otherp.y));
					return true;
			}

			if (ownp.x + ownSize.width / 2 >= otherp.x + othersize.width / 2 
				&& ownp.x - ownSize.width / 2 <= otherp.x + othersize.width / 2) {
					otherp.x = ownp.x - ownSize.width / 2 - othersize.width / 2;
					testsprite->setPosition(ccp(otherp.x, otherp.y));
					return true;
			}

	}
	return false;
}


bool GameEnemy::collisionWidthBullet(GameBullet *testsprite) {
	CCSize ownsize = mysprite->getContentSize();
	CCSize othersize = testsprite->getMySize();
	CCPoint ownp = mysprite->getPosition();
	CCPoint otherp = testsprite->getSprite()->getPosition();
	if (abs(ownp.x - otherp.x) <= ownsize.width / 2 + othersize.width / 2
		&& abs(ownp.y - otherp.y) <= ownsize.height / 2 + othersize.height / 2) {
			return true;
	}
	return false;
}

CCSize GameEnemy::getMySize() {
	return mysprite->getContentSize();
}