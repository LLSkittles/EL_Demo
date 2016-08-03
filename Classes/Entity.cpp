//
//  Entity.cpp
//  MyCppGame
//
//  Created by Chao on 16/8/2.
//
//

#include "Entity.hpp"


void Entity::bindSprite(Sprite *sprite){
    
    m_sprite = sprite;
    this->addChild(m_sprite);
}

Sprite* Entity::getSprite(){
    
    return  m_sprite;
}