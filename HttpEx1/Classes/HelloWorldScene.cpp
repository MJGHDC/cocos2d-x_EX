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

	MenuItemFont::setFontSize(24);
	MenuItemFont::setFontName("Courier New");

	auto pMenuItem1 = MenuItemFont::create(" Get ", CC_CALLBACK_1(HelloWorld::onGetTest, this));
	pMenuItem1->setColor(Color3B(0, 0, 0));

	auto pMenuItem2 = MenuItemFont::create(" Post ", CC_CALLBACK_1(HelloWorld::onPostTest, this));
	pMenuItem2->setColor(Color3B(0, 0, 0));

	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, nullptr);
	pMenu->alignItemsVertically();
	this->addChild(pMenu);

	lblStatusCode = LabelTTF::create("HTTP Status Code", "Courier New", 20);
	lblStatusCode->setPosition(Vec2(240, 260));
	lblStatusCode->setColor(Color3B::BLUE);
	this->addChild(lblStatusCode);

	return true;
}

void HelloWorld::onGetTest(Ref* sender)
{
	// test 1 : 에러를 내기 위한 코드
	{
		HttpRequest* request = new HttpRequest();
		request->setUrl("http://just-make-this-request-failed.com");
		request->setRequestType(HttpRequest::Type::GET);
		request->setResponseCallback(CC_CALLBACK_2(HelloWorld::onHttpRequestCompleted, this));
		request->setTag("GET test1");

		HttpClient::getInstance()->send(request);
		request->release();
	}

	// test 2
	{
		HttpRequest* request = new HttpRequest();
		request->setUrl("http://httpbin.org/get");
		request->setRequestType(HttpRequest::Type::GET);
		request->setResponseCallback(CC_CALLBACK_2(HelloWorld::onHttpRequestCompleted, this));
		request->setTag("GET test2");

		HttpClient::getInstance()->send(request);
		request->release();
	}

	lblStatusCode->setString("waiting...");
}

void HelloWorld::onPostTest(Ref* sender)
{
	// test 1: Normal Post Data
	{
		HttpRequest* request = new HttpRequest();
		request->setUrl("http://httpbin.org/post");
		request->setRequestType(HttpRequest::Type::POST);
		request->setResponseCallback(CC_CALLBACK_2(HelloWorld::onHttpRequestCompleted, this));

		const char* postData = "visitor=cocos2d&TestSuite=NetworkTest";
		request->setRequestData(postData, strlen(postData));
		request->setTag("POST test1");

		HttpClient::getInstance()->send(request);
		request->release();
	}

	// test 2: set Content-Type
	{
		HttpRequest* request = new HttpRequest();
		request->setUrl("http://httpbin.org/post");
		request->setRequestType(HttpRequest::Type::POST);
		request->setResponseCallback(CC_CALLBACK_2(HelloWorld::onHttpRequestCompleted, this));

		std::vector<std::string> headers;
		headers.push_back("Content-Type: application/json; charset=utf-8");
		request->setHeaders(headers);

		const char* postData = "visitor=cocos2d&TestSuite=NetworkTest";
		request->setRequestData(postData, strlen(postData));
		request->setTag("POST test2");

		HttpClient::getInstance()->send(request);
		request->release();
	}

	lblStatusCode->setString("waiting...");
}

void HelloWorld::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
	if (!response)
	{
		return;
	}

	// You can get original request type from: response->request->reqType
	if (0 != strlen(response->getHttpRequest()->getTag()))
	{
		log("%s completed", response->getHttpRequest()->getTag());
	}

	int statusCode = response->getResponseCode();
	char statusString[64] = { 0 };
	sprintf(statusString, "HTTP Status Code: %d,\n tag = %s", statusCode, response->getHttpRequest()->getTag());
	lblStatusCode->setString(statusString);

	if (!response->isSucceed())
	{
		log("response failed");
		log("error buffer: %s", response->getErrorBuffer());
		return;
	}

	std::vector<char>* buffer = response->getResponseData();
	log("Http Test, dump data: ");
	char str[1024] = { 0 };
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		sprintf(str, "%s%c", str, (*buffer)[i]);
	}
	log("%s", str);
}
