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

	mWinSize = Director::getInstance()->getWinSize();

	mTmap = TMXTiledMap::create("TileMaps/TestDesert.tmx");
	mBackground = mTmap->getLayer("Background");
	mItems = mTmap->getLayer("Items");
	mMetainfo = mTmap->getLayer("MetaInfo");
	mMetainfo->setVisible(false);
	this->addChild(mTmap, 0, 11);

	TMXObjectGroup* objects = mTmap->getObjectGroup("Objects");
	ValueMap spawnPoint = objects->getObject("SpawnPoint");

	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();

	mDragonPosition = Vec2(x, y);
	this->createDragon();

	return true;
}

void HelloWorld::onEnter()
{
	Scene::onEnter();

	mListener = EventListenerTouchOneByOne::create();
	mListener->setSwallowTouches(true);
	mListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	mListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mListener, this);
}

void HelloWorld::onExit()
{
	_eventDispatcher->removeEventListener(mListener);

	Scene::onExit();
}

void HelloWorld::createDragon()
{
	auto texture = Director::getInstance()->getTextureCache()->addImage("Images/dragon_animation.png");

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 6; i++) 
	{
		int index = i % 4;
		int rowIndex = i / 4;

		animation->addSpriteFrameWithTexture(texture, Rect(index * 130, rowIndex * 140 + 70, 110, 70));
	}

	mDragon = Sprite::createWithTexture(texture, Rect(0, 70, 110, 70));
	mDragon->setPosition(mDragonPosition);
	mDragon->setFlippedX(true);
	mDragon->setScale(0.5);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	mDragon->runAction(rep);
	this->addChild(mDragon);
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);

	Vec2 playerPos = mDragon->getPosition();
	Vec2 diff = touchPoint - playerPos;

	if (abs(diff.x) > abs(diff.y)) 
	{
		if (diff.x > 0) 
		{
			playerPos.x += mTmap->getTileSize().width;
			mDragon->setFlippedX(true);
		}
		else 
		{
			playerPos.x -= mTmap->getTileSize().width;
			mDragon->setFlippedX(false);
		}
	}
	else 
	{
		if (diff.y > 0) 
		{
			playerPos.y += mTmap->getTileSize().height;
		}
		else 
		{
			playerPos.y -= mTmap->getTileSize().height;
		}
	}

	if (playerPos.x <= (mTmap->getMapSize().width * mTmap->getTileSize().width) &&
		playerPos.y <= (mTmap->getMapSize().height * mTmap->getTileSize().height) &&
		playerPos.y >= 0 &&
		playerPos.x >= 0)
	{
		//dragon->setPosition(playerPos);
		this->setPlayerPosition(playerPos);
	}
	this->setViewpointCenter(mDragon->getPosition());

}

void HelloWorld::setViewpointCenter(Vec2 position)
{
	int x = MAX(position.x, mWinSize.width / 2);
	int y = MAX(position.y, mWinSize.height / 2);

	x = MIN(x, (mTmap->getMapSize().width * mTmap->getTileSize().width) - mWinSize.width / 2);
	y = MIN(y, (mTmap->getMapSize().height * mTmap->getTileSize().height) - mWinSize.height / 2);

	Vec2 actualPosition = Vec2(x, y);
	Vec2 centerOfView = Vec2(mWinSize.width / 2, mWinSize.height / 2);
	Vec2 viewPoint = centerOfView - actualPosition;

	this->setPosition(viewPoint);
}

Vec2 HelloWorld::tileCoordForPosition(Vec2 position)
{
	int x = position.x / mTmap->getTileSize().width;
	int y = ((mTmap->getMapSize().height * mTmap->getTileSize().height) - position.y) / mTmap->getTileSize().height;

	return Vec2(x, y);
}

void HelloWorld::setPlayerPosition(Vec2 position)
{
	Vec2 tileCoord = this->tileCoordForPosition(position);

	int tileGid = this->mMetainfo->getTileGIDAt(tileCoord);

	if (tileGid) 
	{
		Value properties = mTmap->getPropertiesForGID(tileGid);

		if (!properties.isNull()) 
		{
			std::string wall = properties.asValueMap()["Wall"].asString();
			if (wall == "YES") 
			{
				log("Wall...");
				return;
			}

			std::string item1 = properties.asValueMap()["Items"].asString();
			if (item1 == "Apple") 
			{
				this->mMetainfo->removeTileAt(tileCoord);
				mItems->removeTileAt(tileCoord);
				log("아이템 획득!!! 이 메시지가 여러번 출력되는지 확인");
			}
		}
	}

	mDragon->setPosition(position);
}
