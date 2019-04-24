//
//  Monster.h
//  SpriteExtendEx
//
//  Created by Jaewhan Lee on 13. 11. 10.
//
//

#ifndef __SpriteExtendEx__Monster__
#define __SpriteExtendEx__Monster__

#include "cocos2d.h"

class Monster : public cocos2d::Sprite
{
public:
    Monster();

    void setPriority(int fixedPriority);
    void setPriorityWithThis(bool useNodePriority);

    void onEnter();
    void onExit();

private:
    cocos2d::EventListener* _listener;
    int _fixedPriority;
    bool _useNodePriority;
};

#endif /* defined(__SpriteExtendEx__Monster__) */
