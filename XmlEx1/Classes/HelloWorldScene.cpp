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
#include "tinyxml2/tinyxml2.h"

#include <memory>

USING_NS_CC;
using namespace tinyxml2;

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

	FileUtils* util = FileUtils::getInstance();

	std::string path = util->fullPathForFilename("data/test_data.xml");
	std::unique_ptr<tinyxml2::XMLDocument> doc = std::make_unique<tinyxml2::XMLDocument>();
	XMLError error = doc->LoadFile(path.c_str());

	if (error != XML_SUCCESS) {
		log("Error Number : %d", error);
		return false;
	}

	XMLElement* root = doc->RootElement();

	XMLElement* key = root->FirstChildElement("total");
	if (key) 
	{
		log("key element = %s", key->GetText());
	}

	key = key->NextSiblingElement("page");
	if (key) 
	{
		log("key element = %s", key->GetText());
	}

	key = key->NextSiblingElement("per");
	if (key) 
	{
		log("key element = %s", key->GetText());
	}

	XMLElement* array = key->NextSiblingElement();
	XMLElement* child = array->FirstChildElement();
	while (child) 
	{
		XMLElement* child2 = child->FirstChildElement();
		while (child2) 
		{
			log("child element= %s", child2->GetText());
			child2 = child2->NextSiblingElement();
		}
		child = child->NextSiblingElement();
	}
	
	return true;
}
