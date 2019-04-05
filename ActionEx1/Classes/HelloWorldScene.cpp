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

	mpMan = Sprite::create("Images/grossini.png");
	mpMan->setPosition(Vec2(50, 230));
	this->addChild(mpMan);

	mpWoman = Sprite::create("Images/grossinis_sister1.png");
	mpWoman->setPosition(Vec2(50, 110));
	this->addChild(mpWoman);

	MenuItemFont::setFontSize(28);

	auto pMenuItem = MenuItemFont::create(" action ", CC_CALLBACK_1(HelloWorld::doAction, this));
	pMenuItem->setColor(Color3B::BLACK);

	auto pMenu = Menu::create(pMenuItem, nullptr);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);

	return true;
}

void HelloWorld::doAction(Ref* pSender)
{
	//doActionMove();
	//doActionJump();
	//doActionRotate();
	//doActionScale();
	//doActionTint();
	//doActionPlace();
	//doActionBlink();
	//doActionShow();
	doActionFadeInOut();
}

void HelloWorld::doActionMove()
{
	auto moveTo = MoveTo::create(2, Vec2(400, 0));
	auto moveBy = MoveBy::create(2, Vec2(400, 0));

	mpMan->runAction(moveTo);
	mpWoman->runAction(moveBy);
}

void HelloWorld::doActionJump()
{
	auto jumpTo = JumpTo::create(2, Vec2(400, 0), 50, 3);
	auto jumpBy = JumpBy::create(2, Vec2(400, 0), 50, 3);

	mpMan->runAction(jumpTo);
	mpWoman->runAction(jumpBy);
}

void HelloWorld::doActionRotate()
{
	auto rotateTo = RotateTo::create(2, 270); // 가장 가까운 방향으로 회전
	auto rotateBy = RotateBy::create(2, 270); // 무조건 시계방량으로 회전

	mpMan->runAction(rotateTo);
	mpWoman->runAction(rotateBy);
}

void HelloWorld::doActionScale()
{
	auto scaleTo = ScaleTo::create(2, 2.0);
	auto scaleBy = ScaleBy::create(2, 2.0);

	mpMan->runAction(scaleTo);
	mpWoman->runAction(scaleBy);
}

void HelloWorld::doActionTint()
{
	auto tintTo = TintTo::create(2, 128, 128, 128);
	auto tintBy = TintBy::create(2, 0, -30, 30);

	mpMan->runAction(tintTo);
	mpWoman->runAction(tintBy);
}

void HelloWorld::doActionPlace()
{
	auto place = Place::create(Vec2(300, 200));

	mpMan->runAction(place);
}

void HelloWorld::doActionBlink()
{
	auto blink = Blink::create(2, 5);

	mpWoman->runAction(blink);
}

void HelloWorld::doActionShow()
{
	if (mpMan->isVisible() == true)
	{
		auto hide = Hide::create();
		mpMan->runAction(hide);
	}
	else
	{
		auto show = Show::create();
		mpMan->runAction(show);
	}
}

void HelloWorld::doActionFadeInOut()
{
	if (mpMan->getOpacity() == 0)
	{
		auto fadeIn = FadeIn::create(1.5);
		mpMan->runAction(fadeIn);
	}
	else
	{
		auto fadeOut = FadeOut::create(1.5);
		mpMan->runAction(fadeOut);
	}
}

