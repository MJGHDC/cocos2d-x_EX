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
	mpMan->setPosition(Vec2(50, 160));
	this->addChild(mpMan);

	auto pMenuItem = MenuItemFont::create(" action ", CC_CALLBACK_1(HelloWorld::DoAction, this));
	pMenuItem->setColor(Color3B::BLACK);

	auto pMenu = Menu::create(pMenuItem, nullptr);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);

	return true;
}

void HelloWorld::DoAction(Ref* pSender)
{
	mpMan->removeFromParentAndCleanup(true);

	this->removeChildByTag(1, true);
	this->removeChildByTag(2, true);
	this->removeChildByTag(3, true);

	mpMan = Sprite::create("Images/grossini.png");
	mpMan->setPosition(Vec2(50, 160));
	mpMan->setTag(100);
	this->addChild(mpMan);

	mpMan->setVisible(false);

	auto action = Sequence::create(
		Place::create(Vec2(200, 200)),
		DelayTime::create(1.5f),
		Show::create(),
		CallFunc::create(CC_CALLBACK_0(HelloWorld::Callback1, this)),
		MoveBy::create(1.5f, Vec2(200, 0)),
		CallFunc::create(CC_CALLBACK_0(HelloWorld::Callback2, this, mpMan)),
		MoveBy::create(1.5f, Vec2(0, -50)),
		CallFunc::create(CC_CALLBACK_0(HelloWorld::Callback3, this, mpMan, 42)),
		DelayTime::create(1.5f),
		RemoveSelf::create(),
		nullptr
	);

	mpMan->runAction(action);
}

void HelloWorld::Callback1()
{
	auto label = Label::createWithSystemFont("callback 1 called", "consolas", 16);
	label->setPosition(Vec2(120, 160));
	label->setColor(Color3B::BLACK);
	label->setTag(1);
	
	this->addChild(label);
}

void HelloWorld::Callback2(Ref* pSender)
{
	auto label = Label::createWithSystemFont("callback 2 called", "맑은고딕", 16);
	label->setPosition(Vec2(240, 140));
	label->setColor(Color3B::RED);
	label->setTag(2);

	this->addChild(label);

	auto item = (Sprite*)pSender;
	int i = item->getTag();
	log("tag num : %d", i);
}

void HelloWorld::Callback3(Ref* pSender, long data)
{
	auto label = Label::createWithSystemFont("callback 2 called", "바탕체", 16);
	label->setPosition(Vec2(360, 120));
	label->setColor(Color3B::BLUE);
	label->setTag(3);

	this->addChild(label);
	
	log("param data : %d", data);
}

