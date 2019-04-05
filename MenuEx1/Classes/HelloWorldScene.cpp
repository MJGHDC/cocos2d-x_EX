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
	
	// MenuEx1
	//auto pMenuItem1 = MenuItemImage::create("Images/btn-play-normal.png", "Images/btn-play-selected.png", CC_CALLBACK_1(HelloWorld::doClick1, this));
	//auto pMenuItem2 = MenuItemImage::create("Images/btn-highscores-normal.png", "Images/btn-highscores-selected.png", CC_CALLBACK_1(HelloWorld::doClick2, this));
	//auto pMenuItem3 = MenuItemImage::create("Images/btn-about-normal.png", "Images/btn-about-selected.png", CC_CALLBACK_1(HelloWorld::doClick3, this));

	//auto pMenu = Menu::create(pMenuItem1, pMenuItem2, pMenuItem3, nullptr);
	//pMenu->alignItemsVertically();
	//this->addChild(pMenu);

	// MenuEx2
	MenuItemImage* pMenuItem = MenuItemImage::create(R"(Images/btn-play-normal.png)", R"(Images/btn-play-selected.png)", CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenuItem->setPosition(Vec2(480, 320));
	pMenuItem->setAnchorPoint(Vec2(1, 1));

	auto pPostionMenu = Menu::create(pMenuItem, nullptr);
	pPostionMenu->setPosition(Vec2::ZERO);
	this->addChild(pPostionMenu);

	// MenuEx3
	auto pMenuItem1 = MenuItemFont::create(" Menu-1 ", CC_CALLBACK_1(HelloWorld::doClickTag, this));
	pMenuItem1->setColor(Color3B::BLACK);
	auto pMenuItem2 = MenuItemFont::create(" Menu-2 ", CC_CALLBACK_1(HelloWorld::doClickTag, this));
	pMenuItem2->setColor(Color3B::BLACK);
	auto pMenuItem3 = MenuItemImage::create("Images/btn-about-normal.png", "Images/btn-about-selected.png", CC_CALLBACK_1(HelloWorld::doClickTag, this));

	pMenuItem1->setTag(1);
	pMenuItem2->setTag(2);
	pMenuItem3->setTag(3);

	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, pMenuItem3, nullptr);
	pMenu->alignItemsHorizontally();
	this->addChild(pMenu);

	// MenuEx4
	auto pMenuItem4 = MenuItemFont::create(" Menu-1 ", CC_CALLBACK_1(HelloWorld::doClickSpriteTag, this));
	pMenuItem4->setColor(Color3B::BLACK);

	auto pMenuItem5 = MenuItemFont::create(" Menu-2 ", CC_CALLBACK_1(HelloWorld::doClickSpriteTag, this));
	pMenuItem5->setColor(Color3B::BLACK);

	pMenuItem4->setTag(1);
	pMenuItem5->setTag(2);

	auto pMenuSprite = Menu::create(pMenuItem4, pMenuItem5, nullptr);
	pMenuSprite->setPosition(Vec2(240, 220));
	pMenuSprite->alignItemsHorizontally();
	this->addChild(pMenuSprite);

	return true;
}

void HelloWorld::doClickSpriteTag(Ref* pSender)
{
	auto tItem = static_cast<MenuItem*>(pSender);
	int i = tItem->getTag();

	if (i == 1)
	{
		auto pMan = Sprite::create("Images/grossini.png");
		pMan->setPosition(Vec2(100, 160));
		pMan->setTag(11);

		this->addChild(pMan);
	}
	else
	{
		auto pMan = static_cast<Sprite*>(getChildByTag(11));
		this->removeChild(pMan, true);
	}
}

void HelloWorld::doClickTag(Ref * pSender)
{
	auto tItem = static_cast<MenuItem*>(pSender);

	int i = tItem->getTag();

	log("%d 번째 메뉴가 선택되었습니다.", i);
}

void HelloWorld::doClick(Ref * pSender)
{
	log("메뉴가 선택되었습니다.");
}

void HelloWorld::doClick1(Ref * pSender)
{
	log("첫 번째 메뉴가 선택되었습니다.");
}

void HelloWorld::doClick2(Ref * pSender)
{
	log("두 번째 메뉴가 선택되었습니다.");
}

void HelloWorld::doClick3(Ref * pSender)
{
	log("세 번째 메뉴가 선택되었습니다.");
}