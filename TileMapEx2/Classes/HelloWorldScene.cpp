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

Scene *HelloWorld::createScene()
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

	mTmap = TMXTiledMap::create("TileMaps/TestDesert.tmx");
	this->addChild(mTmap, 0, 11);

	auto objects = mTmap->getObjectGroup("Objects");
	ValueMap spawnPoint = objects->getObject("SpawnPoint");

	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();

	mDragonPosition = Vec2(x, y);

	createDragon();

	return true;
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
	mDragon->setPosition(mDragonPosition);
	mDragon->setFlippedX(true);
	mDragon->setScale(0.5f);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	mDragon->runAction(rep);

	this->addChild(mDragon);
}
