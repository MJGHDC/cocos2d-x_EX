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
using namespace ui;

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

	auto sprite1 = Sprite::create("Images/grossini.png");
	auto sprite2 = Sprite::create("Images/grossinis_sister1.png");

	sprite1->setPosition(Vec2(40, 80));
	sprite2->setPosition(Vec2(920, 80));

	auto layer = LayerColor::create(Color4B(255, 0, 255, 255));
	layer->setAnchorPoint(Vec2::ZERO);
	layer->setPosition(Vec2::ZERO);
	layer->setContentSize(Size(960, 160));

	layer->addChild(sprite1);
	layer->addChild(sprite2);


	auto scrollView = ScrollView::create();

	scrollView->setSize(Size(480, 160));
	scrollView->setInnerContainerSize(layer->getContentSize());
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	scrollView->addChild(layer);
	scrollView->setBounceEnabled(true);
	scrollView->setScrollBarAutoHideEnabled(true);
	scrollView->addEventListener(CC_CALLBACK_2(HelloWorld::scrollEvent, this));
	scrollView->jumpToPercentHorizontal(50);
	scrollView->setPosition(Vec2(0, 100));
	this->addChild(scrollView);

	return true;
}

void HelloWorld::scrollEvent(Ref* pSender, ScrollView::EventType event) 
{
	switch (event) 
	{
	case ScrollView::EventType::BOUNCE_BOTTOM:
		log("BOUNCE_BOTTOM");
		break;
	case ScrollView::EventType::SCROLLING:
		log("SCROLLING");
		break;
	case ScrollView::EventType::CONTAINER_MOVED:
		log("CONTAINER_MOVED");
		break;
	case ScrollView::EventType::BOUNCE_LEFT:
		log("BOUNCE_LEFT");
		break;
	case ScrollView::EventType::BOUNCE_RIGHT:
		log("BOUNCE_RIGHT");
		break;
	case ScrollView::EventType::BOUNCE_TOP:
		log("BOUNCE_TOP");
		break;
	}
}

