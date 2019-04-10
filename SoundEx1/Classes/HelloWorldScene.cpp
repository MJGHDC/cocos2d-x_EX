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
#include "AudioEngine.h"

USING_NS_CC;
using namespace experimental;

const std::string BGM_1_PATH = "sounds/background.mp3";
const std::string BGM_2_PATH = "sounds/background-music-aac.mp3";

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

	//auto wlayer = LayerColor::create(Color4B(255, 255, 255, 255));
	//this->addChild(wlayer);

	_soundVolume = 1.0f;

	MenuItemFont::setFontSize(18);

	auto pMenuItem1A = MenuItemFont::create("Preload All", CC_CALLBACK_1(HelloWorld::preloadAll, this));
	auto pMenuItem1B = MenuItemFont::create("Uncache All", CC_CALLBACK_1(HelloWorld::uncacheAll, this));
	auto pMenuItem1C = MenuItemFont::create("Volume Up", CC_CALLBACK_1(HelloWorld::upVolume, this));
	auto pMenuItem1D = MenuItemFont::create("Volume Down", CC_CALLBACK_1(HelloWorld::downVolume, this));

	auto pMenu1 = Menu::create(pMenuItem1A, pMenuItem1B, pMenuItem1C, pMenuItem1D, nullptr);
	pMenu1->alignItemsHorizontallyWithPadding(20);
	pMenu1->setPosition(Vec2(240, 280));
	this->addChild(pMenu1);

	MenuItemFont::setFontSize(24);

	auto pMenuItem2A = MenuItemFont::create("Play Sound1", CC_CALLBACK_1(HelloWorld::playSound1, this));
	auto pMenuItem2B = MenuItemFont::create("Pause Sound1", CC_CALLBACK_1(HelloWorld::pauseSound1, this));
	auto pMenuItem2C = MenuItemFont::create("Resume Sound1", CC_CALLBACK_1(HelloWorld::resumeSound1, this));
	auto pMenuItem2D = MenuItemFont::create("Stop Sound1", CC_CALLBACK_1(HelloWorld::stopSound1, this));

	auto pMenu2 = Menu::create(pMenuItem2A, pMenuItem2B, pMenuItem2C, pMenuItem2D, nullptr);
	pMenu2->alignItemsVertically();
	pMenu2->setPosition(Vec2(140, 160));
	this->addChild(pMenu2);


	auto pMenuItem3A = MenuItemFont::create("Play Sound2", CC_CALLBACK_1(HelloWorld::playSound2, this));
	auto pMenuItem3B = MenuItemFont::create("Pause Sound2", CC_CALLBACK_1(HelloWorld::pauseSound2, this));
	auto pMenuItem3C = MenuItemFont::create("Resume Sound2", CC_CALLBACK_1(HelloWorld::resumeSound2, this));
	auto pMenuItem3D = MenuItemFont::create("Stop Sound2", CC_CALLBACK_1(HelloWorld::stopSound2, this));

	auto pMenu3 = Menu::create(pMenuItem3A, pMenuItem3B, pMenuItem3C, pMenuItem3D, nullptr);
	pMenu3->alignItemsVertically();
	pMenu3->setPosition(Vec2(360, 160));
	this->addChild(pMenu3);

	return true;
}

void HelloWorld::preloadAll(Ref* pSender)
{
	AudioEngine::preload(BGM_1_PATH);
	AudioEngine::preload(BGM_2_PATH);
}

void HelloWorld::uncacheAll(Ref* pSender)
{
	AudioEngine::stop(audioId1);
	AudioEngine::stop(audioId2);

	AudioEngine::uncache(BGM_1_PATH);
	AudioEngine::uncache(BGM_2_PATH);
}

void HelloWorld::playSound1(Ref* pSender)
{
	if (AudioEngine::getState(audioId1) != AudioEngine::AudioState::PLAYING)
	{
		audioId1 = AudioEngine::play2d(BGM_1_PATH, true, _soundVolume);
	}		
}

void HelloWorld::playSound2(Ref * pSender)
{
	if (AudioEngine::getState(audioId2) != AudioEngine::AudioState::PLAYING) 
	{
		audioId2 = AudioEngine::play2d(BGM_2_PATH, false, _soundVolume);
		if (audioId2 != AudioEngine::INVALID_AUDIO_ID)
		{
			AudioEngine::setFinishCallback(audioId2, CC_CALLBACK_2(HelloWorld::bgmPlayFinishedCallback, this));
		}
	}
}

void HelloWorld::pauseSound1(Ref * pSender)
{
	if (AudioEngine::getState(audioId1) == AudioEngine::AudioState::PLAYING)
	{
		AudioEngine::pause(audioId1);
	}
}

void HelloWorld::pauseSound2(Ref * pSender)
{
	if (AudioEngine::getState(audioId2) == AudioEngine::AudioState::PLAYING)
	{
		AudioEngine::pause(audioId2);
	}
}

void HelloWorld::resumeSound1(Ref * pSender)
{
	if (AudioEngine::getState(audioId1) == AudioEngine::AudioState::PAUSED)
	{
		AudioEngine::resume(audioId1);
	}
}

void HelloWorld::resumeSound2(Ref * pSender)
{
	if (AudioEngine::getState(audioId2) == AudioEngine::AudioState::PAUSED)
	{
		AudioEngine::resume(audioId2);
	}
}

void HelloWorld::stopSound1(Ref * pSender)
{
	if (AudioEngine::getState(audioId1) == AudioEngine::AudioState::PLAYING)
	{
		AudioEngine::stop(audioId1);
	}
}

void HelloWorld::stopSound2(Ref * pSender)
{
	if (AudioEngine::getState(audioId2) == AudioEngine::AudioState::PLAYING)
	{
		AudioEngine::stop(audioId2);
	}
}

void HelloWorld::upVolume(Ref * pSender)
{
	if (_soundVolume < 1.0f)
	{
		_soundVolume += 0.1f;
	}

	AudioEngine::setVolume(audioId1, _soundVolume);
	AudioEngine::setVolume(audioId2, _soundVolume);
}

void HelloWorld::downVolume(Ref * pSender)
{
	if (_soundVolume > 0.0f)
	{
		_soundVolume -= 0.1f;
	}		

	AudioEngine::setVolume(audioId1, _soundVolume);
	AudioEngine::setVolume(audioId2, _soundVolume);
}

void HelloWorld::bgmPlayFinishedCallback(int audioId, const std::string & filePath)
{
	log("[ %s ]", filePath.c_str());
}

HelloWorld::~HelloWorld()
{
	AudioEngine::end();
}

