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
	
	this->createBackground();
	this->createDragon();

	auto go = MoveBy::create(4, Vec2(-512, 0));
	auto goBack = go->reverse();
	auto seq = Sequence::create(go, goBack, NULL);
	auto act = RepeatForever::create(seq);

	mVoidNode->runAction(act);

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

	// 겹치는 부분에 검은선이 보이지 않도록 안티 얼라이어싱을 끄는거라는데 끄나 키나 우선 이 예제에선 차이가 없다.
	//background1->getTexture()->setAliasTexParameters();
	//background2->getTexture()->setAliasTexParameters();

	mVoidNode = Layer::create();

	mVoidNode->setTag(1);
	mVoidNode->addChild(background1);
	mVoidNode->addChild(background2);

	this->addChild(mVoidNode, 0);

}

void HelloWorld::createDragon()
{
	auto texture = Director::getInstance()->getTextureCache()->addImage("Images/dragon_animation.png");
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int32_t i = 0; i < 6; ++i)
	{
		int32_t index = i % 4;
		int32_t rowIndex = i / 4;

		animation->addSpriteFrameWithTexture(texture, Rect(index * 130, rowIndex * 140 + 70, 110, 70));
	}

	mDragon = Sprite::createWithTexture(texture, Rect(0, 70, 110, 70));
	mDragon->setPosition(Vec2(240, 160));
	this->addChild(mDragon);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	mDragon->runAction(rep);
}
