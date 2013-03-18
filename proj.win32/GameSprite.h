#ifndef __GAME_SPRITE_H__
#define __GAME_SPRITE_H__

#include <cocos2d.h>

class GameSprite : public cocos2d::CCNode
{
protected:
	cocos2d::CCSprite *mysprite;
	int state;
public:
	GameSprite();
	~GameSprite();
	GameSprite(char *s);
	virtual void tick();
	virtual void setPosition(cocos2d::CCPoint myPoint);
	cocos2d::CCSprite *getSprite();
	void setState(int myState);
	int getState();
	virtual bool collision();
	virtual cocos2d::CCSize getMySize();
};

#endif

