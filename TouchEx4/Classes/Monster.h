#pragma once

#include "cocos2d.h"

class Monster : public cocos2d::Sprite
{
public:
	static Monster* create(const std::string& filename);

	void setPriority(int fixedPriority);
	void setPriorityWithThis(bool useNodePriority);

	void onEnter();
	void onExit();

private:
	cocos2d::EventListener* _listener;
	int _fixedPriority;
	bool _useNodePriority;
};