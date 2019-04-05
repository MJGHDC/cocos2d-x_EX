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

std::string LeftPadZero(size_t number, size_t padSize)
{
	char tempStr[10];
	itoa(number, tempStr, 10);

	std::string numStr(tempStr);

	if (numStr.size() < padSize)
	{
		size_t loopSize = padSize - numStr.size();
		for (size_t i = 0; i < loopSize; ++i)
		{
			numStr = "0" + numStr;
		}
	}

	return numStr;
}

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

	auto man1 = Sprite::create("Images/grossini_dance_01.png");
	man1->setPosition(Vec2(160, 160));
	this->addChild(man1);

	auto animation1 = Animation::create();
	animation1->setDelayPerUnit(0.3f);

	for (size_t i = 1; i < 15; ++i)
	{
		animation1->addSpriteFrameWithFile("Images/grossini_dance_" + LeftPadZero(i, 2) + ".png");
	}

	auto animate1 = Animate::create(animation1);
	auto rapeatForever1 = RepeatForever::create(animate1);
	man1->runAction(rapeatForever1);

	auto sprite = Sprite::create("Images/grossini_dance_atlas.png");
	auto texture1 = sprite->getTexture();
	//auto texture2 = Director::getInstance()->getTextureCache()->addImage("Images/grossini_dance_atlas.png");

	auto animation2 = Animation::create();
	animation2->setDelayPerUnit(0.3f);

	for (size_t i = 0; i < 14; ++i)
	{
		uint32_t column = i % 5;
		uint32_t row = i / 5;

		animation2->addSpriteFrameWithTexture(texture1, Rect(column * 85, row * 121, 85, 121));
	}

	auto man2 = Sprite::createWithTexture(texture1, Rect(0, 0, 85, 121));
	man2->setPosition(Vec2(320, 160));
	this->addChild(man2);

	auto animate2 = Animate::create(animation2);
	auto rapeatForever2 = RepeatForever::create(animate2);
	man2->runAction(rapeatForever2);

	return true;
}

