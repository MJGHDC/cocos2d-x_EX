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

	/////////////////////////////
	mWinSize = Director::getInstance()->getWinSize();
	mTexture = Director::getInstance()->getTextureCache()->addImage("SpinningPeas.png");


	b2Vec2 gravity = b2Vec2(0.0f, -30.0f);
	mWorld = std::make_unique<b2World>(gravity);
	mWorld->SetAllowSleeping(true);
	mWorld->SetContinuousPhysics(true);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	b2Body* groundBody = mWorld->CreateBody(&groundBodyDef);
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	// 바닥
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(mWinSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	// 왼쪽 벽
	//groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, mWinSize.height / PTM_RATIO));
	//groundBody->CreateFixture(&boxShapeDef);

	// 천장
	groundEdge.Set(b2Vec2(0, mWinSize.height / PTM_RATIO), b2Vec2(mWinSize.width / PTM_RATIO, mWinSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	// 오른쪽 벽
	//groundEdge.Set(b2Vec2(mWinSize.width / PTM_RATIO, mWinSize.height / PTM_RATIO), b2Vec2(mWinSize.width / PTM_RATIO, 0));
	//groundBody->CreateFixture(&boxShapeDef);

	this->schedule(schedule_selector(HelloWorld::tick));

	return true;
}

void HelloWorld::onEnter()
{
	Scene::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit()
{
	Scene::onExit();
}

void HelloWorld::tick(float deltaTime)
{
	// 물리적 위치를 이용해서 그래픽 위치를 갱신한다.

	// 프로젝트 생성시 기본값
	// 값이 클수록 정확한 연산이 가능하지만 성능이 떨어진다.
    //int velocityIterations = 8;
    //int positionIterations = 1;

	// 매뉴얼상의 권장값
	// 바디들을 정상적으로 이동시키기 위해서 필요한 충돌들을 반복적으로 계산
	int velocityIterations = 8;
	// 조인트 분리와, 겹침현상을 줄이기 위해서 바디의 위치를 반복적으로 적용
	int positionIterations = 3;

	// Step : 물리 세계를 시뮬레이션한다.
	mWorld->Step(deltaTime, velocityIterations, positionIterations);

	// 모든 물리 객체들은 링크드 리스트에 저장되어 참조해 볼 수 있도록 구현되어 있다.
	// 만들어진 객체 만큼 루프를 돌리면서 바디에 붙인 스프라이트를 여기서 제어한다.
	for (b2Body* b = mWorld->GetBodyList(); b != nullptr; b = b->GetNext())
	{
		if (b->GetUserData() != nullptr) 
		{
			Sprite* spriteData = (Sprite*)b->GetUserData();
			spriteData->setPosition(Vec2(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}

bool HelloWorld::onTouchBegan(Touch * touch, Event * event)
{
	auto touchPoint = touch->getLocation();
	addNewSpriteAtPosition(touchPoint);

	return true;
}

void HelloWorld::addNewSpriteAtPosition(Vec2 location)
{
	// 스프라이트를 파라미터로 넘어온 위치에 만든다.
	Sprite* pSprite = Sprite::createWithTexture(mTexture, Rect(0, 0, 37, 37));
	pSprite->setPosition(Vec2(location.x, location.y));
	this->addChild(pSprite);

	// 바디데프 만들고 속성들을 지정한다.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
	// 유저데이터에 스프라이트를 붙인다.
	bodyDef.userData = pSprite;

	// 월드에 바디데프의 정보로 바디를 만든다.
	b2Body * body = mWorld->CreateBody(&bodyDef);

	// 바디에 적용할 물리 속성용 바디의 모양을 만든다.
	// 원형태를 선택하여 지름을 지정한다.
	b2CircleShape circle;
	circle.m_radius = 0.55;

	// 그리고 바디(addedBody)에 모양(circle)을 고정시킨다.

	b2FixtureDef fixtureDef;

	// 모양을 지정한다.
	fixtureDef.shape = &circle;
	// 밀도
	fixtureDef.density = 1.0f;
	// 마찰력 - 0 ~ 1
	fixtureDef.friction = 0.2f;
	// 반발력 - 물체가 다른 물체에 닿았을때 팅기는 값
	fixtureDef.restitution = 0.7f;

	body->CreateFixture(&fixtureDef);


	/*
	// 박스 모양의 객체 생성

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(.5f, .5f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 1.f;
	body->CreateFixture(&fixtureDef);

	// 다각형 모양의 객체 생성 - 벡터값의 크기에 따라 다양하고 복잡한 모양을 만들 수 있다.

	b2PolygonShape dynamicBox;
	b2Vec2 tri[3];

	tri[0].x = -.5;
	tri[0].y = 0.0;

	tri[1].x = .5;
	tri[1].y = 0.0;

	tri[2].x = 0;
	tri[2].y = 1.0;

	dynamicBox.Set(tri, 3);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 1.f;
	body->CreateFixture(&fixtureDef);
	*/

}
