#include "TestScene1.h"

using namespace cocos2d;

Scene* TestScene1::createScene()
{
	return TestScene1::create();
}

bool TestScene1::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto wlayer = LayerColor::create(Color4B(0, 255, 0, 255));
	this->addChild(wlayer);

	auto item1 = MenuItemFont::create("Close Scene 2", CC_CALLBACK_1(TestScene1::doClose, this));
	item1->setColor(Color3B(0, 0, 0));

	auto pMenu = Menu::create(item1, nullptr);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);

	return true;
}

void TestScene1::doClose(Ref* pSender)
{
	Director::getInstance()->popScene();
	//    Director::getInstance()->popToRootScene();
}
