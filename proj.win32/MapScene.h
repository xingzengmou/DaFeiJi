#ifndef __MAPSCENE_H__
#define __MAPSCENE_H__

#include <cocos2d.h>
#include "GamePlayer.h"
#include "GameEnemy.h"

class MapScene : public cocos2d::CCLayer
{
private:
	cocos2d::CCParticleSystem *m_emitter;
	cocos2d::CCArray *bullets;
	cocos2d::CCArray *enemybullets;
	int stepindex;
	int smallstepindex;
	int xdelta;
	int ydelta;
	int startx;
	int starty;
	byte playerlife;
	double xstep;
	double ystep;
	cocos2d::CCSprite *maplayer1;
	cocos2d::CCSprite *maplayer2;
	cocos2d::CCSprite *life1;
	cocos2d::CCSprite *life2;
	cocos2d::CCSprite *life3;
	bool isreduce;
	GamePlayer *player;
	GameEnemy *enemy;

public:
	int vmove;
	int hmove;
	cocos2d::CCSprite *m_tamara;
	virtual bool init();
	void reduceLife();
	void resetreduce(float dt);
	void enemyrestart(float dt);
	void resettouch(float dt);
	void update(float dt);
	static cocos2d::CCScene *scene();
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	CREATE_FUNC(MapScene);
};

#endif