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

	auto tmap = TMXTiledMap::create("TileMaps/TestDesert.tmx");
	this->addChild(tmap, 0, 11);

	Size s = tmap->getContentSize();
	log("ContentSize: %f, %f", s.width, s.height);
	
	return true;
}

void HelloWorld::onEnter()
{
	Scene::onEnter();

	mListener = EventListenerTouchOneByOne::create();
	mListener->setSwallowTouches(true);
	mListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	mListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mListener, this);
}

void HelloWorld::onExit()
{
	_eventDispatcher->removeEventListener(mListener);

	Scene::onExit();
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
	Vec2 diff = touch->getDelta();
	log("diff.x : %f, diff.y : %f", diff.x, diff.y);

	Node* node = this->getChildByTag(11);
	Vec2 currentPos = node->getPosition();
	log("currentPos.x : %f, currentPos.y : %f", currentPos.x, currentPos.y);

	Vec2 newPos = currentPos + diff;
	log("newPos.x : %f, newPos.y : %f", newPos.x, newPos.y);

	if (newPos.x < -160) {
		newPos.x = -160;
	}
	if (newPos.x > 0) {
		newPos.x = 0;
	}
	newPos.y = 0;

	node->setPosition(newPos);
}
