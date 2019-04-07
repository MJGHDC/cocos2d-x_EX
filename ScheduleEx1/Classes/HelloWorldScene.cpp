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

	// ScheduleEx1
	//this->schedule(schedule_selector(HelloWorld::CallEveryFrame));
	//this->schedule(schedule_selector(HelloWorld::MyTick), 1.0f);
	//this->scheduleOnce(schedule_selector(HelloWorld::MyTickOnce), 3.0f);

	// ScheduleEx2
	//auto item1 = MenuItemFont::create("start", CC_CALLBACK_1(HelloWorld::DoStart, this));
	//item1->setColor(Color3B::BLACK);

	//auto item2 = MenuItemFont::create("pause", CC_CALLBACK_1(HelloWorld::DoPause, this));
	//item2->setColor(Color3B::BLACK);

	//auto item3 = MenuItemFont::create("resume", CC_CALLBACK_1(HelloWorld::DoResume, this));
	//item3->setColor(Color3B::BLACK);

	//auto item4 = MenuItemFont::create("change", CC_CALLBACK_1(HelloWorld::DoChange, this));
	//item4->setColor(Color3B::BLACK);

	//auto item5 = MenuItemFont::create("stop", CC_CALLBACK_1(HelloWorld::DoStop, this));
	//item5->setColor(Color3B::BLACK);

	//auto menu = Menu::create(item1, item2, item3, item4, item5, nullptr);
	//menu->alignItemsVertically();
	//this->addChild(menu);

	// ScheduleEx3
	auto item1 = MenuItemFont::create("pause", CC_CALLBACK_1(HelloWorld::DoClick, this));
	item1->setColor(Color3B::BLACK);

	auto item2 = MenuItemFont::create("resume", CC_CALLBACK_1(HelloWorld::DoClick, this));
	item2->setColor(Color3B::BLACK);

	item1->setTag(1);
	item2->setTag(2);

	auto menu = Menu::create(item1, item2, nullptr);
	menu->setPosition(Vec2(240, 80));
	menu->alignItemsHorizontally();
	this->addChild(menu);

	auto man = Sprite::create("Images/grossini.png");
	man->setPosition(Vec2(140, 200));
	this->addChild(man);

	auto actionForward = MoveBy::create(2, Vec2(200, 0));
	auto actionBackward = actionForward->reverse();
	auto action = Sequence::create(actionForward, actionBackward, nullptr);
	auto rap = RepeatForever::create(action);

	man->runAction(rap);

	return true;
}

void HelloWorld::CallEveryFrame(float deltaTime)
{
	mNum++;
	if (mNum > 60)
	{
		mNum = 1;
	}

	log("fps..%d", mNum);
}

void HelloWorld::MyTick(float deltaTime)
{
	log("tick **************************");
}

void HelloWorld::MyTickOnce(float deltaTime)
{
	log("tickOnce after delay");
}

void HelloWorld::DoStart(Ref* sender)
{
	this->schedule(schedule_selector(HelloWorld::Tick1));
	this->schedule(schedule_selector(HelloWorld::Tick2));
}

void HelloWorld::DoPause(Ref* sender)
{
	Director::getInstance()->getScheduler()->pauseTarget(this);
}

void HelloWorld::DoResume(Ref* sender)
{
	Director::getInstance()->getScheduler()->resumeTarget(this);
}

void HelloWorld::DoChange(Ref* sender)
{
	if (true == mbChange)
	{
		mbChange = false;
		this->unschedule(schedule_selector(HelloWorld::Tick2));
		this->schedule(schedule_selector(HelloWorld::Tick2), 2.0f);
	}
	else
	{
		mbChange = true;
		this->unschedule(schedule_selector(HelloWorld::Tick2));
		this->schedule(schedule_selector(HelloWorld::Tick2), 3.0f);
	}
}

void HelloWorld::DoStop(Ref* sender)
{
	this->unschedule(schedule_selector(HelloWorld::Tick1));
	this->unschedule(schedule_selector(HelloWorld::Tick2));
}

void HelloWorld::Tick1(float deltaTime)
{
	log("tick1");
}

void HelloWorld::Tick2(float deltaTime)
{
	log("tick2");
}

void HelloWorld::DoClick(Ref* sender)
{
	auto item = static_cast<MenuItem*>(sender);
	int32_t i = item->getTag();

	if (1 == i)
	{
		Director::getInstance()->pause();
	}
	else
	{
		Director::getInstance()->resume();
	}
}

