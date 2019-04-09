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

	mEnemy = Sprite::create("Images/MagentaSquare.png");
	mEnemy->setPosition(Vec2(340, 160));
	this->addChild(mEnemy);

	this->createBullet();

	this->schedule(schedule_selector(HelloWorld::myTick));
	
	return true;
}

void HelloWorld::createBullet()
{
	mBullet = Sprite::create("Images/f1.png");
	mBullet->setPosition(Vec2(140, 160));
	this->addChild(mBullet);

	auto myActionForward = MoveBy::create(3, Vec2(400, 0));
	auto myAction = Sequence::create(
		Place::create(Vec2(140, 160)),
		myActionForward, nullptr);
	auto rep = RepeatForever::create(myAction);

	mBullet->runAction(rep);
}

void HelloWorld::onEnter()
{
	Node::onEnter();

	mListener = EventListenerTouchOneByOne::create();

	mListener->setSwallowTouches(true);

	mListener->onTouchBegan = [](Touch * touch, Event * event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		auto touchPoint = touch->getLocation();		
		Vec2 locationInNode = target->convertToNodeSpace(touchPoint);
		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);

		if (rect.containsPoint(locationInNode))
		{
			return true;
		}

		return false;
	};

	mListener->onTouchMoved = [](Touch * touch, Event * event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setPosition(target->getPosition() + touch->getDelta());
	};

	mListener->onTouchEnded = [](Touch * touch, Event * event)
	{
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mListener, mEnemy);
}

void HelloWorld::onExit()
{
	Node::onExit();
}

void HelloWorld::myTick(float f)
{
	if (mBullet == nullptr) {
		log("pBullet is null!");
		this->createBullet();
		return;
	}

	if (mBullet->getBoundingBox().intersectsRect(mEnemy->getBoundingBox())) {
		log("Collision Check!");
		mBullet->removeFromParentAndCleanup(true);
		mBullet = nullptr;
	}
}

