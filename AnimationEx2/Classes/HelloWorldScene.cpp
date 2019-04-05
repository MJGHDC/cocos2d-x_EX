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

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("animations/grossini.plist");

	Vector<SpriteFrame*> animationFrames1;

	for (size_t i = 1; i < 15; ++i)
	{
		SpriteFrame* frame = cache->getSpriteFrameByName("grossini_dance_" + LeftPadZero(i, 2) + ".png");
		animationFrames1.pushBack(frame);
	}

	auto man1 = Sprite::createWithSpriteFrameName("grossini_dance_01.png");
	man1->setPosition(Vec2(240, 160));
	this->addChild(man1);

	auto animation1 = Animation::createWithSpriteFrames(animationFrames1, 0.3f);
	auto animate1 = Animate::create(animation1);
	auto repeatForever = RepeatForever::create(animate1);

	man1->runAction(repeatForever);

	return true;
}

