//
//  GameScene.hpp
//  MyCppGame
//
//  Created by Chao on 16/7/31.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "cocos2d.h"
#include "Player.hpp"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    void addPlayer(TMXTiledMap *tmx);
    void addHeart(TMXTiledMap *tmx);

    void startGame();
    void playFlyToScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    virtual void update(float dt);
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
private:
    Vector<Sprite *> distanceBg;
    Vector<Sprite *> nearbyBg;
    TMXTiledMap *map;
    Player *mPlayer;
};


#endif /* GameScene_hpp */
