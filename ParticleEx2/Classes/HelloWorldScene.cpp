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

	auto item1 = MenuItemFont::create("Particle Change", CC_CALLBACK_1(HelloWorld::showParticle, this));

	auto pMenu = Menu::create(item1, nullptr);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);

	return true;
}

void HelloWorld::showParticle(Ref* pSender)
{
	this->removeChildByTag(10);
	this->removeChildByTag(11);

	static int nIndex = 0;

	Label* name;
	char* filename = "";

	switch (nIndex)
	{
	case 0:
		filename = "Particles/BoilingFoam.plist";
		name = Label::createWithSystemFont("BoilingFoam", "", 30);
		break;
	case 1:
		filename = "Particles/BoilingFoamStar.plist";
		name = Label::createWithSystemFont("BoilingFoamStar", "", 30);
		break;
	case 2:
		filename = "Particles/BurstPipe.plist";
		name = Label::createWithSystemFont("BurstPipe", "", 30);
		break;
	case 3:
		filename = "Particles/ButterFly.plist";
		name = Label::createWithSystemFont("ButterFly", "", 30);
		break;
	case 4:
		filename = "Particles/ButterFlyYFlipped.plist";
		name = Label::createWithSystemFont("ButterFlyYFlipped", "", 30);
		break;
	case 5:
		filename = "Particles/Comet.plist";
		name = Label::createWithSystemFont("Comet", "", 30);
		break;
	case 6:
		filename = "Particles/debian.plist";
		name = Label::createWithSystemFont("debian", "", 30);
		break;
	case 7:
		filename = "Particles/ExplodingRing.plist";
		name = Label::createWithSystemFont("ExplodingRing", "", 30);
		break;
	case 8:
		filename = "Particles/Flower.plist";
		name = Label::createWithSystemFont("Flower", "", 30);
		break;
	case 9:
		filename = "Particles/Galaxy.plist";
		name = Label::createWithSystemFont("Galaxy", "", 30);
		break;
	case 10:
		filename = "Particles/LavaFlow.plist";
		name = Label::createWithSystemFont("LavaFlow", "", 30);
		break;
	case 11:
		filename = "Particles/lines.plist";
		name = Label::createWithSystemFont("lines", "", 30);
		break;
	case 12:
		filename = "Particles/Phoenix.plist";
		name = Label::createWithSystemFont("Phoenix", "", 30);
		break;
	case 13:
		filename = "Particles/SmallSun.plist";
		name = Label::createWithSystemFont("SmallSun", "", 30);
		break;
	case 14:
		filename = "Particles/SpinningPeas.plist";
		name = Label::createWithSystemFont("SpinningPeas", "", 30);
		break;
	case 15:
		filename = "Particles/Spiral.plist";
		name = Label::createWithSystemFont("Spiral", "", 30);
		break;
	case 16:
		filename = "Particles/SpookyPeas.plist";
		name = Label::createWithSystemFont("SpookyPeas", "", 30);
		break;
	default: break;
	}

	nIndex++;
	if (nIndex > 16)
	{
		nIndex = 0;
	}

	ParticleSystem* particle = ParticleSystemQuad::create(filename);
	particle->setPosition(Vec2(240, 160));
	particle->setTag(10);
	particle->setDuration(2.0f);
	particle->setAutoRemoveOnFinish(true);
	this->addChild(particle);


	name->setPosition(Vec2(240, 280));
	name->setTag(11);
	this->addChild(name);
}

