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
using namespace cocos2d::ui;

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

	auto wlayer = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(wlayer);

	const Size editBoxSize = Size(300, 60);

	std::string pNormalSprite = "Images/green_edit.png";
	mEditName = ui::EditBox::create(editBoxSize, ui::Scale9Sprite::create(pNormalSprite));
	mEditName->setPosition(Vec2(240, 250));
	mEditName->setFontSize(25);
	mEditName->setFontColor(Color3B::RED);
	mEditName->setPlaceHolder("Name:");
	mEditName->setPlaceholderFontColor(Color3B::WHITE);
	mEditName->setMaxLength(8);
	mEditName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	mEditName->setDelegate(this);
	addChild(mEditName);


	mEditPassword = ui::EditBox::create(editBoxSize, "Images/orange_edit.png");
	mEditPassword->setPosition(Vec2(240, 150));
	mEditPassword->setFontSize(25);
	mEditPassword->setFontColor(Color3B::GREEN);
	mEditPassword->setPlaceHolder("Password:");
	mEditPassword->setMaxLength(6);
	mEditPassword->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	mEditPassword->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
	mEditPassword->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	mEditPassword->setDelegate(this);
	addChild(mEditPassword);


	mEditEmail = ui::EditBox::create(Size(editBoxSize.width, editBoxSize.height), "Images/yellow_edit.png");
	mEditEmail->setPosition(Vec2(240, 50));
	mEditEmail->setFontSize(25);
	mEditEmail->setPlaceHolder("Email:");
	mEditEmail->setInputMode(ui::EditBox::InputMode::EMAIL_ADDRESS);
	mEditEmail->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	mEditEmail->setDelegate(this);
	addChild(mEditEmail);

	return true;
}

void HelloWorld::editBoxEditingDidBegin(EditBox* editBox)
{
	log("editBox %p DidBegin !", editBox);
}

void HelloWorld::editBoxEditingDidEnd(EditBox* editBox)
{
	log("editBox %p DidEnd !", editBox);
}

void HelloWorld::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
	log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void HelloWorld::editBoxReturn(EditBox* editBox)
{
	log("editBox %p was returned !", editBox);
}

