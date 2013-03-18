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
	this->m_emitter = new CCParticleSystemQuad();
	this->m_emitter->setVisible(false);
	this->addChild(m_emitter, 10);
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
	this->isreduce = true;
}

void MapScene::update(CCTime dt) {

}

void MapScene::enemyrestart (CCTime dt) {

}

void MapScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {

}

void MapScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent) {

}

void MapScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {

}

void MapScene::resettouch(CCTime dt) {

}