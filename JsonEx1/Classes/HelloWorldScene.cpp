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
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/prettywriter.h"

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

	FileUtils* util = FileUtils::getInstance();

	std::string jsonData = util->getStringFromFile("data/test_data.json");
	log("%s\n", jsonData.c_str());

	rapidjson::Document doc;
	doc.Parse<0>(jsonData.c_str());
	if (doc.HasParseError()) 
	{
		log("GetParseError %s\n", doc.GetParseError());
		return false;
	}

	std::string str = doc["string"].GetString();
	log("name = %s", str.c_str());

	int n1 = doc["integer"].GetInt();
	log("i = %d", n1);

	bool isTF = doc["bool"].GetBool();
	log("t = %d", isTF);

	float n2 = doc["float"].GetFloat();
	log("f = %.2f", n2);

	const rapidjson::Value& arr = doc["array"];
	if (arr.IsArray()) 
	{
		for (rapidjson::SizeType i = 0; i < arr.Size(); ++i) 
		{
			auto name = arr[i]["name"].GetString();
			auto age = arr[i]["age"].GetInt();
			log("name:%s, age:%d", name, age);
		}
	}

	return true;
}
