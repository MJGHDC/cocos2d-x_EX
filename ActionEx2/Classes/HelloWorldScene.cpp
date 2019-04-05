/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto wlayer = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(wlayer);

	mpMan = Sprite::create("Images/grossini.png");
	mpMan->setPosition(Vec2(50, 100));
	this->addChild(mpMan);

	auto pMenuItem = MenuItemFont::create(" action ", CC_CALLBACK_1(HelloWorld::doAction, this));
	pMenuItem->setColor(Color3B::BLACK);

	auto pMenu = Menu::create(pMenuItem, nullptr);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);

	return true;
}

void HelloWorld::doAction(Ref* pSender)
{
	mpMan->removeFromParentAndCleanup(true);

	mpMan = Sprite::create("Images/grossini.png");
	mpMan->setPosition(Vec2(50, 100));
	this->addChild(mpMan);

	auto menuItem = static_cast<MenuItem*>(pSender);
	//doActionSequence();
	//doActionSpawn();
	//doActionRepeat();
	//doActionRepeatForever();
	doActionDelayTime();
}

void HelloWorld::doActionSequence()
{
	auto action = Sequence::create(
		MoveBy::create(2, Vec2(400, 0)),
		RotateBy::create(2, 720),
		nullptr
	);

	mpMan->runAction(action);
}

void HelloWorld::doActionSpawn()
{
	auto action = Spawn::create(
		JumpBy::create(4, Vec2(400, 0), 50, 4),
		RotateBy::create(2, 720),
		nullptr
	);

	mpMan->runAction(action);
}

void HelloWorld::doActionRepeat()
{
	auto moveByForward = MoveBy::create(0.25, Vec2(400, 0));
	auto moveByBack = moveByForward->reverse();

	auto action = Sequence::create(moveByForward, moveByBack, nullptr);

	auto rap = Repeat::create(action, 3);

	mpMan->runAction(rap);
}

void HelloWorld::doActionRepeatForever()
{
	auto moveByForward = MoveBy::create(0.25, Vec2(400, 0));
	auto moveByBack = moveByForward->reverse();

	auto action = Sequence::create(moveByForward, moveByBack, nullptr);

	auto rap = RepeatForever::create(action);

	mpMan->runAction(rap);
}

void HelloWorld::doActionDelayTime()
{
	auto rotate1 = RotateTo::create(1, 150);
	auto rotate2 = RotateTo::create(1, 0);
	auto moveBy = MoveBy::create(2, Vec2(400, 0));

	auto action = Sequence::create(rotate1, DelayTime::create(2.0), rotate2, DelayTime::create(1.0), moveBy, nullptr);

	mpMan->runAction(action);
}

