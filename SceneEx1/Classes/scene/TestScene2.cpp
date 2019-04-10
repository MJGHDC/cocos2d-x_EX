#include "TestScene2.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

Scene* TestScene2::createScene()
{
	return TestScene2::create();
}

bool TestScene2::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto wlayer = LayerColor::create(Color4B(255, 255, 0, 255));
	this->addChild(wlayer);

	auto item1 = MenuItemFont::create("Close Scene 3", CC_CALLBACK_1(TestScene2::doClose, this));
	item1->setColor(Color3B(0, 0, 0));

	auto pMenu = Menu::create(item1, nullptr);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);

	return true;
}

void TestScene2::doClose(Ref* pSender)
{
	auto pScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(pScene);
}

