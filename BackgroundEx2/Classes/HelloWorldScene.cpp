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

	layer1 = Layer::create();
	this->addChild(layer1);

	layer2 = Layer::create();
	this->addChild(layer2);
	
	mWinSize = Director::getInstance()->getWinSize();

	this->createBackground();
	this->createDragon();
	this->createArrowButtons();

	return true;
}

void HelloWorld::createBackground()
{
	auto background1 = Sprite::create("Images/background1.png");
	background1->setAnchorPoint(Vec2(0, 0));
	background1->setPosition(Vec2(0, 0));

	auto background2 = Sprite::create("Images/background2.png");
	background2->setAnchorPoint(Vec2(0, 0));
	background2->setPosition(Vec2(512, 0));
	
	layer1->addChild(background1);
	layer1->addChild(background2);
}

void HelloWorld::createDragon()
{
	auto texture = Director::getInstance()->getTextureCache()->addImage("Images/dragon_animation.png");

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 6; i++) 
	{
		int index = i % 4;
		int rowIndex = i / 4;

		animation->addSpriteFrameWithTexture(texture, Rect(index * 130, rowIndex * 140 + 70, 110, 70));
	}

	mDragon = Sprite::createWithTexture(texture, Rect(0, 70, 110, 70));
	mDragon->setPosition(Vec2(240, 160));
	layer1->addChild(mDragon);


	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	mDragon->runAction(rep);
}

void HelloWorld::createArrowButtons()
{
	mLeftSprite = Sprite::create("Images/b1.png");
	mLeftSprite->setPosition(Vec2(180, 30));
	layer2->addChild(mLeftSprite, 2);

	mLeftPressedSprite = Sprite::create("Images/b2.png");
	mLeftPressedSprite->setPosition(mLeftSprite->getPosition());
	layer2->addChild(mLeftPressedSprite, 1);

	mRightSprite = Sprite::create("Images/f1.png");
	mRightSprite->setPosition(Vec2(300, 30));
	layer2->addChild(mRightSprite, 2);

	mRightPressedSprite = Sprite::create("Images/f2.png");
	mRightPressedSprite->setPosition(mRightSprite->getPosition());
	layer2->addChild(mRightPressedSprite, 1);
}

void HelloWorld::onEnter()
{
	Scene::onEnter();

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

	Scene::onExit();
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	mbLeftPressed = false;
	mbRightPressed = false;

	if (this->isTouchInside(mLeftSprite, touch) == true) 
	{
		mLeftSprite->setVisible(false);
		mbLeftPressed = true;

	}
	else if (this->isTouchInside(mRightSprite, touch) == true) 
	{
		mRightSprite->setVisible(false);
		mbRightPressed = true;
	}

	if (mbLeftPressed == true || mbRightPressed == true)
	{
		this->startMovingBackground();
	}		

	return true;
}

void HelloWorld::onTouchMoved(Touch * touch, Event * event)
{
	if (mbLeftPressed == true && this->isTouchInside(mLeftSprite, touch) == false) 
	{
		mLeftSprite->setVisible(true);
		this->stopMovingBackground();
	}
	else if (mbRightPressed == true && this->isTouchInside(mRightSprite, touch) == false) 
	{
		mRightSprite->setVisible(true);
		this->stopMovingBackground();
	}
	else if (mbLeftPressed == true && this->isTouchInside(mLeftSprite, touch) == true)
	{
		mLeftSprite->setVisible(false);
		startMovingBackground();
	}
	else if (mbRightPressed == true && this->isTouchInside(mRightSprite, touch) == true)
	{
		mRightSprite->setVisible(false);
		startMovingBackground();
	}
}

void HelloWorld::onTouchEnded(Touch * touch, Event * event)
{
	if (mbLeftPressed == true || mbRightPressed == true)
	{
		this->stopMovingBackground();
	}		

	if (mbLeftPressed == true)
	{
		mLeftSprite->setVisible(true);
	}
	
	if (mbRightPressed == true)
	{
		mRightSprite->setVisible(true);
	}		
}

bool HelloWorld::isTouchInside(Sprite * sprite, Touch * touch)
{
	auto touchPoint = touch->getLocation();

	bool bTouch = sprite->getBoundingBox().containsPoint(touchPoint);

	return bTouch;
}

void HelloWorld::startMovingBackground()
{
	log("start moving");
	this->schedule(schedule_selector(HelloWorld::moveBackground));
}

void HelloWorld::stopMovingBackground()
{
	log("stop moving");
	this->unschedule(schedule_selector(HelloWorld::moveBackground));
}

void HelloWorld::moveBackground(float t)
{
	int32_t moveStep = 0;
	if (true == mbLeftPressed)
	{
		moveStep = -3;
		mDragon->setFlippedX(false);
	}
	else
	{
		moveStep = 3;
		mDragon->setFlippedX(true);
	}

	Vec2 newPos = Vec2(mDragon->getPosition().x + moveStep, mDragon->getPosition().y);

	if (newPos.x < 0)
	{
		newPos.x = 0;
	}
	else if (newPos.x > 1024)
	{
		newPos.x = 1024;
	}
	mDragon->setPosition(newPos);
	layer1->runAction(Follow::create(mDragon, Rect(0, 0, 1024, 320)));
}

