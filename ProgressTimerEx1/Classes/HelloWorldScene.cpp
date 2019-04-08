#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
	auto wlayer = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(wlayer);
	
	/////////////////////////////

	pWoman1 = Sprite::create("Images/grossinis_sister1.png");
	pWoman2 = Sprite::create("Images/grossinis_sister2.png");

	//this->SpriteProgressToRadial();
	//this->SpriteProgressToHorizontal();
	//this->SpriteProgressToVertical();
	//this->SpriteProgressToRadialMidpointChanged();
	//this->SpriteProgressBarVarious();
	this->SpriteProgressBarTintAndFade();

	return true;
}

//------------------------------------------------------------------
//
// SpriteProgressToRadial
//
//------------------------------------------------------------------

void HelloWorld::SpriteProgressToRadial()
{
	auto to1 = ProgressTo::create(4, 100);
	auto to2 = ProgressTo::create(2, 100);

	auto left = ProgressTimer::create(pWoman1);
	left->setType(ProgressTimer::Type::RADIAL);
	left->setPosition(Vec2(140, 160));
	addChild(left);
	left->runAction(to1);

	auto right = ProgressTimer::create(pWoman2);
	right->setType(ProgressTimer::Type::RADIAL);
	// Makes the ridial CCW
	right->setReverseProgress(true);
	right->setPosition(Vec2(340, 160));
	addChild(right);
	right->runAction(to2);
}

//------------------------------------------------------------------
//
// SpriteProgressToHorizontal
//
//------------------------------------------------------------------

void HelloWorld::SpriteProgressToHorizontal()
{
	auto to1 = ProgressTo::create(2, 100);
	auto to2 = ProgressTo::create(2, 100);

	auto left = ProgressTimer::create(pWoman1);
	left->setType(ProgressTimer::Type::BAR);
	// Setup for a bar starting from the left
	// since the midpoint is 0 for the x
	left->setMidpoint(Vec2(0, 0));
	// Setup for a horizontal bar since the bar change rate
	// is 0 for y meaning no vertical change
	left->setBarChangeRate(Vec2(1, 0));
	left->setPosition(Vec2(140, 160));
	addChild(left);
	left->runAction(to1);

	auto right = ProgressTimer::create(pWoman2);
	right->setType(ProgressTimer::Type::BAR);
	// Setup for a bar starting from the left since the midpoint is
	// 1 for the x
	right->setMidpoint(Vec2(1, 0));
	// Setup for a horizontal bar since the bar change rate is
	// 0 for y meaning no vertical change
	right->setBarChangeRate(Vec2(1, 0));
	right->setPosition(Vec2(340, 160));
	addChild(right);
	right->runAction(to2);
}

//------------------------------------------------------------------
//
// SpriteProgressToVertical
//
//------------------------------------------------------------------

void HelloWorld::SpriteProgressToVertical()
{
	auto to1 = ProgressTo::create(2, 100);
	auto to2 = ProgressTo::create(2, 100);

	auto left = ProgressTimer::create(pWoman1);
	left->setType(ProgressTimer::Type::BAR);

	// Setup for a bar starting from the bottom 
	// since the midpoint is 0 for the y
	left->setMidpoint(Vec2(0, 0));
	// Setup for a vertical bar since the bar change rate
	// is 0 for x meaning no horizontal change
	left->setBarChangeRate(Vec2(0, 1));
	left->setPosition(Vec2(140, 160));
	addChild(left);
	left->runAction(to1);

	auto right = ProgressTimer::create(pWoman2);
	right->setType(ProgressTimer::Type::BAR);
	// Setup for a bar starting from the bottom 
	// since the midpoint is 0 for the y
	right->setMidpoint(Vec2(0, 1));
	// Setup for a vertical bar since the bar change rate
	// is 0 for x meaning no horizontal change
	right->setBarChangeRate(Vec2(0, 1));
	right->setPosition(Vec2(340, 160));
	addChild(right);
	right->runAction(to2);
}

//------------------------------------------------------------------
//
// SpriteProgressToRadialMidpointChanged
//
//------------------------------------------------------------------

void HelloWorld::SpriteProgressToRadialMidpointChanged()
{
	auto to1 = ProgressTo::create(2, 100);
	auto to2 = ProgressTo::create(2, 100);

	/**
	*  Our image on the left should be a radial progress indicator, clockwise
	*/
	auto left = ProgressTimer::create(pWoman1);
	left->setType(ProgressTimer::Type::RADIAL);
	left->setMidpoint(Vec2(0.25f, 0.75f));
	left->setPosition(Vec2(140, 160));
	addChild(left);
	left->runAction(to1);

	/**
	*  Our image on the left should be a radial progress indicator,
	*  counter clockwise
	*/
	auto right = ProgressTimer::create(pWoman2);
	right->setType(ProgressTimer::Type::RADIAL);
	right->setMidpoint(Vec2(0.75f, 0.25f));

	/**
	*  Note the reverse property (default=NO) is only added to the right image.
	*  That's how we get a counter clockwise progress.
	*/
	right->setPosition(Vec2(340, 160));
	addChild(right);
	right->runAction(to2);
}

//------------------------------------------------------------------
//
// SpriteProgressBarVarious
//
//------------------------------------------------------------------

void HelloWorld::SpriteProgressBarVarious()
{
	auto to1 = ProgressTo::create(2, 100);
	auto to2 = ProgressTo::create(2, 100);
	auto to3 = ProgressTo::create(2, 100);

	auto left = ProgressTimer::create(pWoman1);
	left->setType(ProgressTimer::Type::BAR);

	// Setup for a bar starting from the bottom 
	// since the midpoint is 0 for the y
	left->setMidpoint(Vec2(0.5f, 0.5f));
	// Setup for a vertical bar since the bar change rate
	// is 0 for x meaning no horizontal change
	left->setBarChangeRate(Vec2(1, 0));
	left->setPosition(Vec2(140, 160));
	addChild(left);
	left->runAction(to1);

	auto middle = ProgressTimer::create(pWoman2);
	middle->setType(ProgressTimer::Type::BAR);
	// Setup for a bar starting from the bottom since the midpoint
	// is 0 for the y
	middle->setMidpoint(Vec2(0.5f, 0.5f));
	// Setup for a vertical bar since the bar change rate
	// is 0 for x meaning no horizontal change
	middle->setBarChangeRate(Vec2(1, 1));
	middle->setPosition(Vec2(240, 160));
	addChild(middle);
	middle->runAction(to2);

	auto right = ProgressTimer::create(pWoman1);
	right->setType(ProgressTimer::Type::BAR);
	// Setup for a bar starting from the bottom since the midpoint
	// is 0 for the y
	right->setMidpoint(Vec2(0.5f, 0.5f));
	// Setup for a vertical bar since the bar change rate
	// is 0 for x meaning no horizontal change
	right->setBarChangeRate(Vec2(0, 1));
	right->setPosition(Vec2(340, 160));
	addChild(right);
	right->runAction(to3);
}

//------------------------------------------------------------------
//
// SpriteProgressBarTintAndFade
//
//------------------------------------------------------------------

void HelloWorld::SpriteProgressBarTintAndFade()
{
	auto to = ProgressTo::create(6, 100);

	auto tint = Sequence::create(
		TintTo::create(1, 255, 0, 0),
		TintTo::create(1, 0, 255, 0),
		TintTo::create(1, 0, 0, 255),
		nullptr);
	auto fade = Sequence::create(
		FadeTo::create(1.0f, 0),
		FadeTo::create(1.0f, 255),
		nullptr);

	auto left = ProgressTimer::create(pWoman1);
	left->setType(ProgressTimer::Type::BAR);
	// Setup for a bar starting from the bottom
	// since the midpoint is 0 for the y
	left->setMidpoint(Vec2(0.5f, 0.5f));
	// Setup for a vertical bar since the bar change rate
	// is 0 for x meaning no horizontal change
	left->setBarChangeRate(Vec2(1, 0));
	left->setPosition(Vec2(140, 160));
	addChild(left);
	left->runAction(RepeatForever::create(to->clone()));
	left->runAction(RepeatForever::create(tint->clone()));

	auto pLabelLeft = Label::createWithSystemFont("Tint", "", 20.0f);
	pLabelLeft->setColor(Color3B::BLACK);
	pLabelLeft->setPosition(Vec2(pWoman1->getContentSize().width / 2, -10));
	left->addChild(pLabelLeft);


	auto middle = ProgressTimer::create(pWoman2);
	middle->setType(ProgressTimer::Type::BAR);
	// Setup for a bar starting from the bottom
	// since the midpoint is 0 for the y
	middle->setMidpoint(Vec2(0.5f, 0.5f));
	// Setup for a vertical bar since the bar change rate
	// is 0 for x meaning no horizontal change
	middle->setBarChangeRate(Vec2(1, 1));
	middle->setPosition(Vec2(240, 160));
	addChild(middle);
	middle->runAction(RepeatForever::create(to->clone()));
	middle->runAction(RepeatForever::create(fade->clone()));

	auto pLabelMid = Label::createWithSystemFont("Fade", "", 20.0f);
	pLabelMid->setColor(Color3B::BLACK);
	pLabelMid->setPosition(Vec2(pWoman2->getContentSize().width / 2, -10));
	middle->addChild(pLabelMid);


	auto right = ProgressTimer::create(pWoman1);
	right->setType(ProgressTimer::Type::BAR);
	// Setup for a bar starting from the bottom
	// since the midpoint is 0 for the y
	right->setMidpoint(Vec2(0.5f, 0.5f));
	// Setup for a vertical bar since the bar change rate
	// is 0 for x meaning no horizontal change
	right->setBarChangeRate(Vec2(0, 1));
	right->setPosition(Vec2(340, 160));
	addChild(right);
	right->runAction(RepeatForever::create(to->clone()));
	right->runAction(RepeatForever::create(tint->clone()));
	right->runAction(RepeatForever::create(fade->clone()));

	auto pLabelRight = Label::createWithSystemFont("Tint & Fade", "", 20.0f);
	pLabelRight->setColor(Color3B::BLACK);
	pLabelRight->setPosition(Vec2(pWoman1->getContentSize().width / 2, -10));
	right->addChild(pLabelRight);
}
