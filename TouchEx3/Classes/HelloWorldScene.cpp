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

	mListener = EventListenerTouchOneByOne::create();
	mListener->setSwallowTouches(true);

	mListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	mListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	mListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mListener, this);
}

void HelloWorld::onExit()
{
	_eventDispatcher->removeEventListener(mListener);

	Node::onExit();
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	auto touchPoint = touch->getLocation();

	mbSelect = mMan->getBoundingBox().containsPoint(touchPoint);

	return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
	if (mbSelect)
	{
		Vec2 oldPoint = touch->getPreviousLocation();
		Vec2 nowPoint = touch->getLocation();

		Vec2 firstVector = oldPoint - mMan->getPosition();
		float firstRotateAngle = -firstVector.getAngle();
		float previousTouch = CC_RADIANS_TO_DEGREES(firstRotateAngle);

		Vec2 secondVector = nowPoint - mMan->getPosition();
		float secondRotateAngle = -secondVector.getAngle();
		float currentTouch = CC_RADIANS_TO_DEGREES(secondRotateAngle);

		gRotation += currentTouch - previousTouch;
		gRotation = fmod(gRotation, 360.0f);

		mMan->setRotation(gRotation);
	}
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	mbSelect = false;
}