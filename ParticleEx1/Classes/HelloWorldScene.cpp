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

	auto dir = Director::getInstance();
	ParticleSystem* particle;
	Texture2D* texture;
	Label* name;

	switch (nIndex)
	{
	case 0:
		particle = ParticleFire::create();
		texture = dir->getTextureCache()->addImage("Images/fire.png");
		name = Label::createWithSystemFont("Fire", "", 30);
		break;
	case 1:
		particle = ParticleSun::create();
		texture = dir->getTextureCache()->addImage("Images/fire.png");
		name = Label::createWithSystemFont("Sun", "", 30);
		break;
	case 2:
		particle = ParticleGalaxy::create();
		texture = dir->getTextureCache()->addImage("Images/fire.png");
		name = Label::createWithSystemFont("Galaxy", "", 30);
		break;
	case 3:
		particle = ParticleSpiral::create();
		texture = dir->getTextureCache()->addImage("Images/fire.png");
		name = Label::createWithSystemFont("Spiral", "", 30);
		break;
	case 4:
		particle = ParticleSmoke::create();
		texture = dir->getTextureCache()->addImage("Images/fire.png");
		name = Label::createWithSystemFont("Smoke", "", 30);
		break;
	case 5:
		particle = ParticleMeteor::create();
		texture = dir->getTextureCache()->addImage("Images/fire.png");
		name = Label::createWithSystemFont("Meteor", "", 30);
		break;
	case 6:
		particle = ParticleFlower::create();
		texture = dir->getTextureCache()->addImage("Images/stars.png");
		name = Label::createWithSystemFont("Flower", "", 30);
		break;
	case 7:
		particle = ParticleFireworks::create();
		texture = dir->getTextureCache()->addImage("Images/stars.png");
		name = Label::createWithSystemFont("Fireworks", "", 30);
		break;
	case 8:
		particle = ParticleExplosion::create();
		texture = dir->getTextureCache()->addImage("Images/stars.png");
		name = Label::createWithSystemFont("Explosion", "", 30);
		break;
	default: break;
	}

	nIndex++;
	if (nIndex > 8)
	{
		nIndex = 0;
	}

	particle->setTexture(texture);

	if (particle != nullptr)
	{
		particle->setScale(1.0);

		//particle->setDuration(1.0);

		particle->setPosition(Vec2(240, 160));
		particle->setTag(10);
		this->addChild(particle);


		name->setPosition(Vec2(240, 280));
		name->setTag(11);
		this->addChild(name);
	}
}

