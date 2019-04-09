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

	auto pLabel1 = Label::createWithSystemFont(
		"Fixed priority test",
		"",
		20);
	pLabel1->setPosition(Vec2(240, 300));
	pLabel1->setColor(Color3B(0, 0, 0));
	this->addChild(pLabel1, 101);

	auto pLabel2 = Label::createWithSystemFont(
		"Fixed Priority, Blue: 10, Red: 20, Yellow: 30\n"
		"작은 수가 더 높은 우선 순위를 가집니다",
		"",
		14);
	pLabel2->setPosition(Vec2(240, 270));
	pLabel2->setColor(Color3B::BLUE);
	this->addChild(pLabel2, 101);

	sprite1 = Monster::create("Images/CyanSquare.png");
	sprite1->setPosition(Vec2(240, 160) + Vec2(-50, 0));
	sprite1->setOpacity(180);
	sprite1->setPriority(10);
	sprite1->setPriorityWithThis(false);
	this->addChild(sprite1);

	sprite2 = Monster::create("Images/MagentaSquare.png");
	sprite2->setPosition(Vec2(240, 160));
	sprite2->setOpacity(180);
	sprite2->setPriority(20);
	sprite2->setPriorityWithThis(false);
	this->addChild(sprite2);

	sprite3 = Monster::create("Images/YellowSquare.png");
	sprite3->setPosition(Vec2(50, 0));
	sprite3->setOpacity(180);
	sprite3->setPriority(30);
	sprite3->setPriorityWithThis(false);
	sprite2->addChild(sprite3);

	return true;
}

