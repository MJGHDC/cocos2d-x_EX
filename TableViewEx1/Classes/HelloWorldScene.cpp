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

	TableView* tableView1 = TableView::create(this, Size(250, 60));
	tableView1->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView1->setPosition(Vec2(20, 130));
	tableView1->setDelegate(this);
	tableView1->setTag(100);
	this->addChild(tableView1);
	tableView1->reloadData();

	TableView* tableView2 = TableView::create(this, Size(60, 250));
	tableView2->setDirection(ScrollView::Direction::VERTICAL);
	tableView2->setPosition(Vec2(330, 40));
	tableView2->setTag(200);
	tableView2->setDelegate(this);
	tableView2->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	this->addChild(tableView2);
	tableView2->reloadData();

	return true;
}

void HelloWorld::tableCellTouched(TableView* table, TableViewCell* cell)
{
	log("Tag : %d\nCell touched at index: %ld",
		table->getTag(),
		cell->getIdx());
}

Size HelloWorld::tableCellSizeForIndex(TableView* table, ssize_t idx)
{
	if (idx == 2) {
		return Size(100, 100);
	}
	return Size(60, 60);
}

TableViewCell* HelloWorld::tableCellAtIndex(TableView* table, ssize_t idx)
{
	auto string = String::createWithFormat("%ld", idx);

	TableViewCell* cell = table->dequeueCell();
	if (!cell) {
		cell = new CustomTableViewCell();
		cell->autorelease();

		auto sprite = Sprite::create("Images/Icon.png");
		sprite->setAnchorPoint(Vec2::ZERO);
		sprite->setPosition(Vec2(0, 0));
		cell->addChild(sprite);

		auto label = Label::createWithSystemFont(string->getCString(), "", 20.0);
		label->setPosition(Vec2::ZERO);
		label->setAnchorPoint(Vec2::ZERO);
		label->setTag(123);
		cell->addChild(label);
	}
	else
	{
		auto label = (Label*)cell->getChildByTag(123);
		label->setString(string->getCString());
	}


	return cell;
}

ssize_t HelloWorld::numberOfCellsInTableView(TableView* table)
{
	return 20;
}
