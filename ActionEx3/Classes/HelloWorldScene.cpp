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

	createSprite();

	auto pMenuItem = MenuItemFont::create(" action ", CC_CALLBACK_1(HelloWorld::doAction, this));
	pMenuItem->setColor(Color3B::BLACK);

	auto pMenu = Menu::create(pMenuItem, nullptr);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);

	return true;
}

void HelloWorld::createSprite()
{
	mpBall = Sprite::create("Images/r1.png");
	mpBall->setPosition(Vec2(50, 100));
	mpBall->setScale(0.7f);
	this->addChild(mpBall);

	mpMan = Sprite::create("Images/grossini.png");
	mpMan->setPosition(Vec2(50, 150));
	mpMan->setScale(0.5f);
	this->addChild(mpMan);

	mpWoman1 = Sprite::create("Images/grossinis_sister1.png");
	mpWoman1->setPosition(Vec2(50, 220));
	mpWoman1->setScale(0.5f);
	this->addChild(mpWoman1);

	mpWoman2 = Sprite::create("Images/grossinis_sister2.png");
	mpWoman2->setPosition(Vec2(50, 280));
	mpWoman2->setScale(0.5f);
	this->addChild(mpWoman2);
}

void HelloWorld::doAction(Ref* pSender)
{
	mpBall->removeFromParentAndCleanup(true);
	mpMan->removeFromParentAndCleanup(true);
	mpWoman1->removeFromParentAndCleanup(true);
	mpWoman2->removeFromParentAndCleanup(true);

	createSprite();

	//doActionEase();
	//doActionElastic();
	//doActionBounce();
	doActionspeed();
}

void HelloWorld::doActionEase()
{
	// EaseExponential, EaseSine, EaseBack

	auto move = MoveBy::create(3.0f, Vec2(400, 0));
	auto easeIn = EaseIn::create(move->clone(), 3.0f);
	auto easeOut = EaseOut::create(move->clone(), 3.0f);
	auto easeInOut = EaseInOut::create(move->clone(), 3.0f);

	mpBall->runAction(move);
	mpMan->runAction(easeIn);
	mpWoman1->runAction(easeOut);
	mpWoman2->runAction(easeInOut);
}

void HelloWorld::doActionElastic()
{
	auto move = MoveBy::create(3.0f, Vec2(400, 0));
	auto easeElasticIn = EaseElasticIn::create(move->clone(), 0.4f);
	auto easeElasticOut = EaseElasticOut::create(move->clone(), 0.4f);
	auto easeElasticInOut = EaseElasticInOut::create(move->clone(), 0.4f);

	mpBall->runAction(move);
	mpMan->runAction(easeElasticIn);
	mpWoman1->runAction(easeElasticOut);
	mpWoman2->runAction(easeElasticInOut);
}

void HelloWorld::doActionBounce()
{
	auto move = MoveBy::create(3.0f, Vec2(400, 0));
	auto easeBounceIn = EaseBounceIn::create(move->clone());
	auto easeBounceOut = EaseBounceOut::create(move->clone());
	auto easeBounceInOut = EaseBounceInOut::create(move->clone());

	mpBall->runAction(move);
	mpMan->runAction(easeBounceIn);
	mpWoman1->runAction(easeBounceOut);
	mpWoman2->runAction(easeBounceInOut);
}

void HelloWorld::doActionspeed()
{
	auto move = MoveBy::create(3.0f, Vec2(400, 0));
	auto speed1 = Speed::create(move->clone(), 1.0f);
	auto speed2 = Speed::create(move->clone(), 2.0f);
	auto speed3 = Speed::create(move->clone(), 3.0f);

	mpBall->runAction(move);
	mpMan->runAction(speed1);
	mpWoman1->runAction(speed2);
	mpWoman2->runAction(speed3);
}

