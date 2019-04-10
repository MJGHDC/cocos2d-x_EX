#include "scene/TestScene3.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

Scene* TestScene3::createScene()
{
	return TestScene3::create();
}

bool TestScene3::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto wlayer = LayerColor::create(Color4B(0, 255, 0, 255));
	this->addChild(wlayer);

	/////////////////////////////

	// 메뉴 아이템 생성 및 초기화

	auto item1 = MenuItemFont::create("Scene2 -> Scene1", CC_CALLBACK_1(TestScene3::doChangeScene, this));
	item1->setColor(Color3B(0, 0, 0));

	// 메뉴 생성
	auto pMenu = Menu::create(item1, nullptr);

	// 레이어에 메뉴 객체 추가
	this->addChild(pMenu);

	log("TestScene3 :: init");


	return true;
}

void TestScene3::doChangeScene(Ref* pSender)
{
	// 두번째 장면
	auto pScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(pScene);
	//Director::getInstance()->replaceScene( TransitionProgressRadialCCW::create(1, pScene) );
}

void TestScene3::onEnter()
{
	Scene::onEnter();

	log("TestScene3 :: onEnter");
}

void TestScene3::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();

	log("TestScene3 :: onEnterTransitionDidFinish");
}

void TestScene3::onExitTransitionDidStart()
{
	Scene::onExitTransitionDidStart();

	log("TestScene3 :: onExitTransitionDidStart");
}

void TestScene3::onExit()
{
	Scene::onExit();

	log("TestScene3 :: onExit");
}

TestScene3::~TestScene3()
{
	log("TestScene3 :: dealloc");
}
