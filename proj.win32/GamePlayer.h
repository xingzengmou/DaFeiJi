#ifndef __GAMEPLAYER_H__
#define __GAMEPLAYER_H__

#include <cocos2d.h>
#include "GameSprite.h"

class GamePlayer : public GameSprite
{
private:
	cocos2d::CCMotionStreak *myStreak;
	int state;
public:
	GamePlayer(char *s);
	virtual void tick();
	virtual void setPosition(cocos2d::CCPoint myPoint);
	bool isCollision(GameSprite *testSprite);
	cocos2d::CCMotionStreak *getStreak();
	virtual bool collision();
	virtual cocos2d::CCSize getMySize();
};

#endif

