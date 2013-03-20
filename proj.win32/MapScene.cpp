#include "MapScene.h"

using namespace cocos2d;

enum {
	kTagTilemap = 1,
};

CCScene* MapScene::scene() {
	CCScene *scene = NULL;
	do {
		scene = CCScene::create();
		CC_BREAK_IF(!scene);
		MapScene *layer = MapScene::create();
		CC_BREAK_IF(!layer);
		scene->addChild(layer);
	} while (0);
	return scene;
}

bool MapScene::init() {
	player = new GamePlayer("player.png");
	enemy = new GameEnemy("e6.png");

	maplayer1 = CCSprite::create("back_img1.png");
	maplayer2 = CCSprite::create("back_img1.png");
	life1 = CCSprite::create("life.png");
	life2 = CCSprite::create("life.png");
	life3 = CCSprite::create("life.png");
	life1->setPosition(ccp(20,20));
	life2->setPosition(ccp(30,20));
	life3->setPosition(ccp(40,20));
	this->addChild(life1,1,300);
	this->addChild(life2,1,301);
	this->addChild(life3,1,302);
	this->playerlife = 3;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	maplayer1->setAnchorPoint(ccp(0,0));
	maplayer2->setAnchorPoint(ccp(0,0));
	maplayer1->setPosition(ccp(0,0));
	maplayer2->setPosition(ccp(0,512));
	this->addChild(maplayer1,0,1);
	this->addChild(maplayer2,0,2);
	player->setPosition(ccp(122,30));

	this->addChild((player->getSprite()), 2, 0);
	this->addChild((enemy->getSprite()), 2, 100);
	this->addChild((player->getStreak()), 1);
	//this->m_emitter = CCParticleSystemQuad::create();
	//m_emitter->initWithFile("ExplodingRing.plist");
	//this->m_emitter->setVisible(false);
	//this->addChild(m_emitter, 10);
	this->setTouchEnabled(true);
	this->scheduleUpdate();
	this->stepindex = -1;

	bullets = CCArray::createWithCapacity(10);
	for (int i = 0; i < bullets->capacity(); i ++) {
		GameBullet *myBullet = new GameBullet("bullet.png");
		CCPoint herop = (player->getSprite())->getPosition();
		CCSize herosize = player->getSprite()->getContentSize();
		myBullet->setPosition(ccp(herop.x,herop.y + herosize.height));
		myBullet->setType(0);
		myBullet->getSprite()->setVisible(false);
		this->addChild(myBullet->getSprite(), 200 + i);
		bullets->addObject(myBullet);
	}

	bullets->retain();

	this->enemybullets = CCArray::createWithCapacity(20);
	for (int i = 0; i < this->enemybullets->capacity(); i ++) {
		GameBullet *myBullet = new GameBullet("bullet3456.png");
		myBullet->getSprite()->setVisible(false);
		myBullet->setType(1);
		this->addChild(myBullet->getSprite(), 400 + i);
		this->enemybullets->addObject(myBullet);
	}
	this->enemybullets->retain();

	this->isreduce = false;
	return true;
}

void MapScene::reduceLife() {
	player->getSprite()->stopAllActions();

	switch (playerlife) {
	case 3:
		life1->setVisible(false);
		playerlife --;
		break;
	case 2:
		life2->setVisible(false);
		playerlife --;
		break;
	case 1:
		life3->setVisible(false);
		playerlife --;
		break;
	}

	CCActionInterval *action = CCBlink::create(5, 10);
	player->getSprite()->runAction(action);
	this->schedule(schedule_selector(MapScene::resetreduce), 5.0f);

	isreduce = true;
}

void MapScene::resetreduce(float dt) {
	this->isreduce = false;
}

void MapScene::update(float dt) {
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint maplayer1p = maplayer1->getPosition();
	CCPoint maplayer2p = maplayer2->getPosition();
	maplayer1->setPosition(ccp(maplayer1p.x, maplayer1p.y - 5));
	maplayer2->setPosition(ccp(maplayer2p.x, maplayer2p.y - 5));
	if (maplayer2p.y < 0) {
		float temp = maplayer2p.y + 512;
		maplayer1->setPosition(ccp(maplayer1p.x, temp));
	}

	if (maplayer1p.y < 0) {
		float temp = maplayer1p.y + 512;
		maplayer2->setPosition(ccp(maplayer2p.x, temp));
	}

	if (!isreduce) {
		for (int i = 0; i < enemybullets->capacity(); i ++) {
			GameBullet *mybullet = (GameBullet*)(enemybullets->objectAtIndex(i));
			if (mybullet->getSprite()->isVisible() &&
				player->isCollision(mybullet)) {
					mybullet->getSprite()->setVisible(false);
					reduceLife();
			}
		}
	}

	if (enemy->getState() != -1) {
		enemy->tick();
		if (enemy->getBulletTick() == 59) {
			CCPoint herop = enemy->getSprite()->getPosition();
			CCSize herosize = enemy->getSprite()->getContentSize();
			for (int i = 0; i < enemybullets->capacity(); i ++) {
				GameBullet *mybullet = (GameBullet*)enemybullets->objectAtIndex(i);
				if (!mybullet->getSprite()->isVisible()) {
					mybullet->setPosition(ccp(herop.x, herop.y - herosize.height));
					mybullet->getSprite()->setVisible(true);
					break;
				}
			}
		}

		if (!isreduce && enemy->isCollision(player)) {
			stepindex = 0;
			enemy->setDead();
			m_emitter = CCParticleSystemQuad::create("ExplodingRing.plist");
			//m_emitter->initWithFile("ExplodingRing.plist");
			m_emitter->setPosition(enemy->getSprite()->getPosition());
			m_emitter->setVisible(true);
			this->addChild(m_emitter, 10);
			reduceLife();
			m_emitter->release();
			schedule(schedule_selector(MapScene::enemyrestart), 2.0f);
		} else {
			for (int i = 0; i < bullets->capacity(); i ++) {
				GameBullet *mybullet = (GameBullet *)bullets->objectAtIndex(i);
				if (mybullet->getSprite()->isVisible()
					&& enemy->collisionWidthBullet(mybullet)) {
						enemy->setDead();
						mybullet->getSprite()->setVisible(false);
						m_emitter->initWithFile("ExplodingRing.plist");
						m_emitter->setVisible(true);
						m_emitter->setPosition(enemy->getSprite()->getPosition());
						schedule(schedule_selector(MapScene::enemyrestart), 2.0f);
				}
			}
		}
	}

	for (int i = 0; i < bullets->capacity(); i ++) {
		GameBullet *mybullet = (GameBullet*)bullets->objectAtIndex(i);
		if (mybullet->getSprite()->isVisible()) {
			mybullet->tick();
			if (mybullet->getSprite()->getPosition().y > size.height) {
				mybullet->getSprite()->setVisible(false);
			}
		}
	}

	for (int i = 0; i < enemybullets->capacity(); i ++ ) {
		GameBullet *mybullet = (GameBullet*) enemybullets->objectAtIndex(i);
		if (mybullet->getSprite()->isVisible()) {
			mybullet->tick();
			if (mybullet->getSprite()->getPosition().y < 0) {
				mybullet->getSprite()->setVisible(false);
			}
		}
	}

}

void MapScene::enemyrestart (float dt) {
	enemy->restart();
	unschedule(schedule_selector(MapScene::enemyrestart));
}

void MapScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
	CCSetIterator it = pTouches->begin();
	CCTouch *touch = (CCTouch*)(*it);

	CCPoint m_tBeginPos = touch->getLocationInView();
	m_tBeginPos = CCDirector::sharedDirector()->convertToGL(m_tBeginPos);
	CCPoint herop = player->getSprite()->getPosition();
	CCSize herosize = player->getSprite()->getContentSize();
	if (m_tBeginPos.x > herop.x - herosize.width / 2
		&& m_tBeginPos.x < herop.x + herosize.width / 2
		&& m_tBeginPos.y > herop.y - herosize.height / 2
		&& m_tBeginPos.y < herop.y + herosize.height / 2) {
			stepindex = -5;
			xdelta = m_tBeginPos.x - herop.x;
			ydelta = m_tBeginPos.y - herop.y;
			schedule(schedule_selector(MapScene::resettouch), 1.0f);
	}
}

void MapScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent) {
	CCSetIterator it = pTouches->begin();
	CCTouch *touch = (CCTouch*)(*it);
	CCPoint touchLocation = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
	if (stepindex == -5) {
		CCPoint herop = player->getSprite()->getPosition();
		CCPoint lastone = ccp(herop.x + xdelta, herop.y + ydelta);
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		if (touchLocation.x >= 0
			&& touchLocation.x <= winSize.width
			&& touchLocation.y >= 0
			&& touchLocation.y <= winSize.height) {
				if (lastone.x != touchLocation.x
					|| lastone.y != touchLocation.y) {
						player->setPosition(ccp(touchLocation.x - xdelta,touchLocation.y - ydelta));
				}
		}
	}
}

void MapScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {
	if (stepindex == -5) {
		unschedule(schedule_selector(MapScene::resettouch));
		stepindex = -1;
	}
}

void MapScene::resettouch(float dt) {
	CCPoint herop = player->getSprite()->getPosition();
	CCSize herosize = player->getSprite()->getContentSize();
	for (int i = 0; i < bullets->capacity(); i++) {
		GameBullet *mybullet = (GameBullet*)bullets->objectAtIndex(i);
		if (!mybullet->getSprite()->isVisible()) {
			mybullet->setPosition(ccp(herop.x, herop.y + herosize.height));
			mybullet->getSprite()->setVisible(true);
			break;
		}
	}
}