#pragma once

#include "cocos2d.h"

class TestScene3 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(TestScene3);

	void doChangeScene(Ref* pSender);

	void onEnter();
	void onEnterTransitionDidFinish();
	void onExitTransitionDidStart();
	void onExit();

	~TestScene3();
};