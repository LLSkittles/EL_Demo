//
//  Entity.hpp
//  MyCppGame
//
//  Created by Chao on 16/8/2.
//
//

#ifndef Entity_hpp
#define Entity_hpp

#include "cocos2d.h"
USING_NS_CC;

class Entity: public Node{
public:
    void bindSprite(Sprite *sprite);
    Sprite *getSprite();
protected:
    Sprite *m_sprite;
};

#endif /* Entity_hpp */
