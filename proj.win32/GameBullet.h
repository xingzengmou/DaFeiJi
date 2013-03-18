#ifndef __GAME_BULLET_H__
#define __GAME_BULLET_H__

#include <cocos2d.h>
#include "GamePlayer.h"

class GameBullet : public GameSprite
{
private:
	cocos2d::CCMotionStreak *myStreak;
	int type;

public:
	GameBullet(char* s);
	virtual void tick();
	virtual void setPosition(cocos2d::CCPoint myPoint);
	cocos2d::CCMotionStreak *getStreak();
	void setType(int myType);
	int getType();
	virtual bool collision(GamePlayer *testSprite);
	virtual cocos2d::CCSize getMySize();
};

#endif

