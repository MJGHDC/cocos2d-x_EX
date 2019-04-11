#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;

class CustomTableViewCell : public TableViewCell
{
public:
	virtual void draw(Renderer* renderer, const Mat4& transform, uint32_t flags) override;
};