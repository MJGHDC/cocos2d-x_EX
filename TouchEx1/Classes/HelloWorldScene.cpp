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

	mMan = Sprite::create("Images/grossini.png");
	mMan->setPosition(Vec2(240, 160));
	this->addChild(mMan);

	return true;
}

void HelloWorld::onEnter()
{
	Node::onEnter();
	//mOneListener = EventListenerTouchOneByOne::create();

	//mOneListener->setSwallowTouches(true);
	//mOneListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	//mOneListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	//mOneListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	//mOneListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);

	//_eventDispatcher->addEventListenerWithSceneGraphPriority(mOneListener, this);

	mMultiListener = EventListenerTouchAllAtOnce::create();

	mMultiListener->setEnabled(true);
	mMultiListener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
	mMultiListener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
	mMultiListener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);
	mMultiListener->onTouchesCancelled = CC_CALLBACK_2(HelloWorld::onTouchesCancelled, this);

	_eventDispatcher->addEventListenerWithFixedPriority(mMultiListener, 1);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(mMultiListener, this);
}

void HelloWorld::onExit()
{
	//_eventDispatcher->removeEventListener(mOneListener);
	_eventDispatcher->removeEventListener(mMultiListener);

	Node::onExit();
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto touchPoint = touch->getLocation();

	log("onTouchBegan id = %d, x = %f, y = %f", touch->getID(), touchPoint.x, touchPoint.y);

	bool bTouch = mMan->getBoundingBox().containsPoint(touchPoint);
	if (bTouch)
	{
		log("Sprite clicked...");
	}

	return true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto touchPoint = touch->getLocation();

	log("onTouchMoved id = %d, x = %f, y = %f", touch->getID(), touchPoint.x, touchPoint.y);
}

void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto touchPoint = touch->getLocation();

	log("onTouchEnded id = %d, x = %f, y = %f", touch->getID(), touchPoint.x, touchPoint.y);
}

void HelloWorld::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event)
{
	log("call onTouchCancelled...");
}

void HelloWorld::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
	for (auto& item : touches)
	{
		auto touch = item;
		auto touchPoint = touch->getLocation();

		log("onTouchesBegan id = %d, x = %f, y = %f", touch->getID(), touchPoint.x, touchPoint.y);

		bool bTouch = mMan->getBoundingBox().containsPoint(touchPoint);
		if (bTouch)
		{
			log("Sprite clicked... id = %d", touch->getID());
		}
	}
}

void HelloWorld::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
	for (auto& item : touches)
	{
		auto touch = item;
		auto touchPoint = touch->getLocation();

		log("onTouchesMoved id = %d, x = %f, y = %f", touch->getID(), touchPoint.x, touchPoint.y);
	}
}

void HelloWorld::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
	for (auto& item : touches)
	{
		auto touch = item;
		auto touchPoint = touch->getLocation();

		log("onTouchesEnded id = %d, x = %f, y = %f", touch->getID(), touchPoint.x, touchPoint.y);
	}
}

void HelloWorld::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
	log("call onTouchsCancelled...");
}

