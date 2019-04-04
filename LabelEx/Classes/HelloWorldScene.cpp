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

	auto wlayer = LayerColor::create(Color4B(125, 125, 125, 255));
	this->addChild(wlayer);

	//auto pLabel1 = Label::create("Hello World", "맑은고딕", 34);

	//pLabel1->setPosition(Vec2(240, 220));
	//pLabel1->setColor(Color3B::BLACK);
	//this->addChild(pLabel1);

	//const char* pText = "동해물과 백두산이 마르고 닳도록 하느님이 보우하사 우리나라 만세.";
	//auto pLabel2 = Label::createWithSystemFont(pText, "consolas", 34, Size(300, 200), TextHAlignment::CENTER, TextVAlignment::CENTER);

	//pLabel2->setPosition(Vec2(240, 120));
	//pLabel2->setColor(Color3B::BLUE);
	//this->addChild(pLabel2);

	//auto pLabel3 = Label::createWithBMFont("fonts/bitmapFontTest.fnt", "Hello World");
	//pLabel3->setPosition(Vec2(240, 260));
	//this->addChild(pLabel3);

	////auto pLabel4 = Label::createWithCharMap("fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
	//auto pLabel4 = Label::createWithCharMap("fonts/tuffy_bold_italic-charmap.plist");
	//pLabel4->setPosition(Vec2(240, 300));
	//pLabel4->setString("1234");
	//this->addChild(pLabel4);

	TTFConfig ttfConfig("fonts/Scissor Cuts.ttf", 40);

	auto pLabel1 = Label::createWithTTF(ttfConfig, "Normal");
	pLabel1->setPosition(Vec2(240, 160 + 90));
	pLabel1->setColor(Color3B::WHITE);
	this->addChild(pLabel1);

	auto pLabel2 = Label::createWithTTF(ttfConfig, "Glow");
	pLabel2->setPosition(Vec2(240, 160 + 30));
	pLabel2->setColor(Color3B::BLACK);
	pLabel2->enableGlow(Color4B::YELLOW);
	this->addChild(pLabel2);

	ttfConfig.outlineSize = 4;
	ttfConfig.bold = true;

	auto pLabel3 = Label::createWithTTF(ttfConfig, "OutLine");
	pLabel3->setPosition(Vec2(240, 160 - 30));
	pLabel3->setColor(Color3B::WHITE);
	pLabel3->enableOutline(Color4B::BLUE);
	this->addChild(pLabel3);

	auto pLabel4 = Label::createWithTTF(ttfConfig, "Shadow");
	pLabel4->setPosition(Vec2(240, 160 - 90));
	pLabel4->setColor(Color3B::RED);
	pLabel4->enableShadow(Color4B::BLACK);
	this->addChild(pLabel4);

	return true;
}

