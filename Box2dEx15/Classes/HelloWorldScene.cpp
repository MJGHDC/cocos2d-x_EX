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

	int32_t seed = static_cast<int32_t>(time(nullptr));
	srand(seed);

	winSize = Director::getInstance()->getWinSize();
	texture = Director::getInstance()->getTextureCache()->addImage("blocks.png");
	
	createBox2dWorld();
	setBox2dWorld();
	schedule(schedule_selector(HelloWorld::tick));

	return true;
}

void HelloWorld::createBox2dWorld()
{
	b2Vec2 gravity = b2Vec2(0.0f, -30.0f);

	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);

#ifdef BOX2D_DEBUG
	// 디버그 드로잉 설정
	// 적색 : 현재 물리 운동을 하는 것
	// 회색 : 현재 물리 운동량이 없는 것
	m_debugDraw = new GLESDebugDraw(PTM_RATIO);
	_world->SetDebugDraw(m_debugDraw);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	//flags += b2Draw::e_aabbBit;
	//flags += b2Draw::e_pairBit;
	//flags += b2Draw::e_centerOfMassBit;
	m_debugDraw->SetFlags(flags);
#else
	auto* wlayer = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(wlayer);
#endif // BOX2D_DEBUG

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	b2Body* groundBody = _world->CreateBody(&groundBodyDef);

	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width * 2 / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(0, winSize.height / PTM_RATIO), b2Vec2(winSize.width * 2 / PTM_RATIO, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(winSize.width * 2 / PTM_RATIO, winSize.height / PTM_RATIO), b2Vec2(winSize.width * 2 / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);
}

void HelloWorld::setBox2dWorld()
{
	Sprite* bg1 = Sprite::create("background1.png");
	bg1->setPosition(Vec2(0, 0));
	bg1->setAnchorPoint(Vec2(0, 0));
	this->addChild(bg1);

	myBall = this->addNewSprite(Vec2(25, 50), Size(50, 50), b2_dynamicBody, "test", 0);
	Sprite* myBallSprite = (Sprite*)myBall->GetUserData();
	Rect myBoundary = Rect(0, 0, winSize.width * 2, winSize.height);

	// 손쉬운 화면 스크롤링 기법인 Follow 액션을 사용해 넓은 화면을 이동시킨다.
	// 바디를 던지면 해당 바디에 카메라가 붙어 있으므로 자동으로 화면이 스크롤된다.
	this->runAction(Follow::create(myBallSprite, myBoundary));

	// 오른쪽 구석에 쌓아 놓을 바디들의 벡터값을 구성하고 스프라이트를 추가한다.
	float start = winSize.width * 2 - 130;

	struct BLOCK 
	{
		Vec2 point;
		Size  size;
	};

	int const numBlocks = 6;
	struct BLOCK blocks[numBlocks] =
	{
		{ Vec2(start, 50), Size(10, 100) },
		{ Vec2(start + 50, 50), Size(10, 100) },
		{ Vec2(start + 25, 100 + 5), Size(200, 10) },
		{ Vec2(start, 120 + 50), Size(10, 100) },
		{ Vec2(start + 50, 120 + 50), Size(10, 100) },
		{ Vec2(start + 25, 220 + 5), Size(200, 10) }
	};

	for (int i = 0; i < numBlocks; i++)
	{
		this->addNewSprite(blocks[i].point, blocks[i].size, b2_dynamicBody, "test", 0);
	}
}

HelloWorld::~HelloWorld()
{
	delete _world;
	_world = nullptr;
}

#ifdef BOX2D_DEBUG
void HelloWorld::draw(Renderer * renderer, const Mat4 & transform, uint32_t flags)
{
	Scene::draw(renderer, transform, flags);

	_customCmd.init(_globalZOrder, transform, flags);
	_customCmd.func = CC_CALLBACK_0(HelloWorld::onDraw, this, transform, flags);
	renderer->addCommand(&_customCmd);
}

void HelloWorld::onDraw(const Mat4 & transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when setting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	_world->DrawDebugData();
	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
#endif // BOX2D_DEBUG

void HelloWorld::onEnter()
{
	Scene::onEnter();

	auto* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit()
{
	Scene::onExit();
}

void HelloWorld::tick(float deltaTime)
{
	int32_t velocityIterations = 8;
	int32_t positionIterations = 1;

	_world->Step(deltaTime, velocityIterations, positionIterations);

	for (b2Body* body = _world->GetBodyList(); body != nullptr; body = body->GetNext())
	{
		if (body->GetUserData() != nullptr) 
		{
			Sprite* spriteData = (Sprite*)body->GetUserData();
			spriteData->setPosition(Vec2(body->GetPosition().x * PTM_RATIO, body->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));
		}
	}
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 touchPoint = touch->getLocation();
	Vec2 touchPoint2 = Node::convertToNodeSpace(touchPoint);
	//log("nodeSpace..%f", touchPoint2.x);

	b2Body* tBall = this->getBodyAtTab(touchPoint2);

	bBallTouch = false;

	if (tBall == myBall)
	{
		log("touch start..");
		bBallTouch = true;
		startPoint = b2Vec2(touchPoint2.x / PTM_RATIO, touchPoint2.y / PTM_RATIO);
	}

	return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	Vec2 touchPoint = touch->getLocation();
	Vec2 touchPoint2 = Node::convertToNodeSpace(touchPoint);

	if (myBall && bBallTouch)
	{
		log("touch end..");
		endPoint = b2Vec2(touchPoint2.x / PTM_RATIO, touchPoint2.y / PTM_RATIO);

		b2Vec2 force = endPoint - startPoint;

		force.x *= 250.0f;
		force.y *= 250.0f;

		myBall->ApplyForceToCenter(force, true);

		bBallTouch = false;
	}
}

b2Body* HelloWorld::addNewSprite(Vec2 point, Size size, b2BodyType bodytype, const char* spriteName, int type)
{
	b2BodyDef bodyDef;
	bodyDef.type = bodytype;
	bodyDef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);

	if (spriteName != nullptr)
	{
		if (strcmp(spriteName, "test") == 0) 
		{
			int idx = (CCRANDOM_0_1() > 0.5 ? 0 : 1);
			int idy = (CCRANDOM_0_1() > 0.5 ? 0 : 1);
			Sprite * sprite = Sprite::createWithTexture(texture, Rect(32 * idx, 32 * idy, 32, 32));
			sprite->setPosition(point);
			this->addChild(sprite);

			bodyDef.userData = sprite;
		}
		else 
		{
			Sprite* sprite = Sprite::create(spriteName);
			sprite->setPosition(point);
			this->addChild(sprite);

			bodyDef.userData = sprite;
		}
	}
	else
	{
		bodyDef.userData = nullptr;
	}
	
	b2Body* body = _world->CreateBody(&bodyDef);
	b2FixtureDef fixtureDef;
	b2PolygonShape dynamicBox;
	b2CircleShape circle;

	if (type == 0) 
	{
		dynamicBox.SetAsBox(size.width / 2 / PTM_RATIO, size.height / 2 / PTM_RATIO);
		fixtureDef.shape = &dynamicBox;
	}
	else 
	{
		circle.m_radius = (size.width / 2) / PTM_RATIO;
		fixtureDef.shape = &circle;
	}

	// Define the dynamic body fixture.
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;

	body->CreateFixture(&fixtureDef);

	return body;
}

b2Body* HelloWorld::getBodyAtTab(Point p)
{
	b2Fixture* fix;
	for (b2Body* body = _world->GetBodyList(); body != nullptr; body = body->GetNext())
	{
		// if (body->GetUserData() != nullptr) 
		{
			if (body->GetType() == b2_staticBody) 
			{ 
				continue;
			}

			fix = body->GetFixtureList();
			if (fix->TestPoint(b2Vec2(p.x / PTM_RATIO, p.y / PTM_RATIO))) 
			{
				return body;
			}
		}
	}

	return nullptr;
}


void HelloWorld::addNewSpriteAtPosition(Vec2 location)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);

#ifdef BOX2D_DEBUG	
	bodyDef.userData = nullptr;
#else

#endif // BOX2D_DEBUG
	b2Body* body = _world->CreateBody(&bodyDef);
	b2FixtureDef fixtureDef;
	b2CircleShape circle;

	circle.m_radius = 20 / PTM_RATIO;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;

	body->CreateFixture(&fixtureDef);
}
