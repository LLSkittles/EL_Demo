//
//  Player.cpp
//  MyCppGame
//
//  Created by Chao on 16/8/2.
//
//

#include "Player.hpp"


bool Player::init(){
        
    return true;
}

void Player::addAnimationCache(){
    
    AnimationCache *animationCache = AnimationCache::getInstance();
    Vector<SpriteFrame*> frameVec1;
    char str[100]={0};

    for (int i = 1; i < 5; i++) {
        
        sprintf(str,"flying%d.png",i);

        SpriteFrame *frame = SpriteFrame::create(str, Rect(0, 0, 63, 155));
        frameVec1.pushBack(frame);
    }
    
    Animation *flying = Animation::createWithSpriteFrames(frameVec1);
    flying->setDelayPerUnit(0.1f);
    animationCache->addAnimation(flying, "fly");
    
    Vector<SpriteFrame*> frameVec2;
    for (int i = 1; i < 5; i++) {
        
        sprintf(str,"die%d.png",i);
        
        SpriteFrame *frame = SpriteFrame::create(str, Rect(0, 0, 111, 175));
        frameVec2.pushBack(frame);
    }
    
    Animation *die = Animation::createWithSpriteFrames(frameVec2);
    die->setDelayPerUnit(0.1f);
    animationCache->addAnimation(die, "die");

    Vector<SpriteFrame*> frameVec3;
    for (int i = 1; i < 4; i++) {
        
        sprintf(str,"drop%d.png",i);
        
        SpriteFrame *frame = SpriteFrame::create(str, Rect(0, 0, 78, 144));
        frameVec3.pushBack(frame);
    }
    
    Animation *drop = Animation::createWithSpriteFrames(frameVec3);
    drop->setDelayPerUnit(0.1f);
    animationCache->addAnimation(drop, "drop");
}

void Player::die(){
    
    AnimationCache *animationCache = AnimationCache::getInstance();

    Animation *die = animationCache->getAnimation("die");
    die->setLoops(1);
    
    this->getSprite()->stopAllActions();
    this->getSprite()->runAction(Animate::create(die));
}

void Player::flying(){
    
    AnimationCache *animationCache = AnimationCache::getInstance();
    
    Animation *fly = animationCache->getAnimation("fly");
    fly->setLoops(-1);
    
    this->getSprite()->stopAllActions();
    this->getSprite()->runAction(Animate::create(fly));
    
}

void Player::drop(){
    
    AnimationCache *animationCache = AnimationCache::getInstance();
    
    Animation *drop = animationCache->getAnimation("drop");
    drop->setLoops(-1);
    
    this->getSprite()->stopAllActions();
    this->getSprite()->runAction(Animate::create(drop));
}







