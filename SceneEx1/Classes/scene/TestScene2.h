#pragma once

#include "cocos2d.h"

class TestScene2 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(TestScene2);

	void doClose(Ref* pSender);
};