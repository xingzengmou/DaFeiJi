#ifndef __GAME_ENEMY_H__
#define __GAME_ENEMY_H__

#include <cocos2d.h>
#include "GameSprite.h"
#include "GamePlayer.h"
#include "GameBullet.h"

class GameEnemy : public GameSprite
{
private:
	cocos2d::CCMotionStreak *myStreak;
	cocos2d::CCActionInterval *bezierTo1;
	cocos2d::CCActionInterval *actionTo1;
	cocos2d::CCActionInterval *actionTo2;
	cocos2d::CCActionInterval *actionTo3;
	cocos2d::ccBezierConfig bezier1;
	cocos2d::ccBezierConfig bezier2;
	short bulletTick;
	short type;

public:
	GameEnemy(char *s);
	void setDead();
	void restart();
	virtual void tick();
	virtual void setPosition(cocos2d::CCPoint myPoint);
	bool isCollision(GameSprite *testSprite);
	cocos2d::CCMotionStreak *getStreak();
	void chooseFlyType();
	int getBulletTick();
	virtual bool collision(GamePlayer *testSprite);
	virtual cocos2d::CCSize getMySize();
	bool collisionWidthBullet(GameBullet *testSprite);

};

#endif

