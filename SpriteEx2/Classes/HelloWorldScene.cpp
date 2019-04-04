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

	auto pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(240, 160));
	auto pManSize = pMan->getContentSize();
	
	auto pManHealth = Sprite::create("Images/white-512x512.png");
	pManHealth->setTextureRect(Rect(0, 0, 50, 5));
	pManHealth->setColor(Color3B::RED);
	pManHealth->setPosition(Vec2(pManSize.width / 2.0, pManSize.height + 10));
	
	pMan->addChild(pManHealth);
	this->addChild(pMan, 2);


	auto pWoman = Sprite::create("Images/grossinis_sister1.png");
	pWoman->setPosition(Vec2(300, 160));
	auto pWomanSize = pWoman->getContentSize();
	
	auto pWomanHealth = Sprite::create("Images/white-512x512.png");
	pWomanHealth->setTextureRect(Rect(0, 0, 50, 5));
	pWomanHealth->setColor(Color3B::RED);
	pWomanHealth->setPosition(Vec2(pWomanSize.width / 2.0, pWomanSize.height - 10));
	
	pWoman->addChild(pWomanHealth);
	this->addChild(pWoman, 1);

	return true;
}

