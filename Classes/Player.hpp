//
//  Player.hpp
//  MyCppGame
//
//  Created by Chao on 16/8/2.
//
//

#ifndef Player_hpp
#define Player_hpp

#include "Entity.hpp"
USING_NS_CC;

class Player: public Entity{
    
public:
    CREATE_FUNC(Player);
    virtual bool init();
    void addAnimationCache();
    void die();
    void drop();
    void flying();
};

#endif /* Player_hpp */
