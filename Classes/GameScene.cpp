//
//  GameScene.cpp
//  MyCppGame
//
//  Created by Chao on 16/7/31.
//
//

#include "GameScene.hpp"

Scene* GameScene::createScene(){
    
    auto scene = Scene::createWithPhysics();
    auto layer = GameScene::create();
    scene->addChild(layer);
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);//调试
//    scene->getPhysicsWorld()->setGravity(Point(0, -98));
    
    return scene;
}



bool GameScene::init(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    auto sprite = Sprite::create("bj2.jpg");
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, -4);
    
    auto bg1 = Sprite::create("b2.png");
    bg1->setAnchorPoint(Point(0, 0));
    bg1->setPosition(Point(0, 10));
    this->addChild(bg1, -3);
    
    auto bg2 = Sprite::create("b2.png");
    bg2->setAnchorPoint(Point(0, 0));
    bg2->setPosition(Point(bg1->getContentSize().width, 10));
    this->addChild(bg2, -3);
    
    distanceBg.pushBack(bg1);
    distanceBg.pushBack(bg2);
    
    auto bg3 = Sprite::create("b1.png");
    bg3->setAnchorPoint(Point(0, 0));
    bg3->setPosition(Point(0, 0));
    this->addChild(bg3, -2);
    
    auto bg4 = Sprite::create("b1.png");
    bg4->setAnchorPoint(Point(0, 0));
    bg4->setPosition(bg3->getContentSize().width, 0);
    this->addChild(bg4, -2);
    
    nearbyBg.pushBack(bg3);
    nearbyBg.pushBack(bg4);
    
    ParticleSystemQuad *emiter = ParticleSystemQuad::create("dirt.plist");
    emiter->setPosition(visibleSize.width/2, visibleSize.height/2);
    this->addChild(emiter, -3);
    
    map = TMXTiledMap::create("map.tmx");
    map->setAnchorPoint(Point(0, 0));
    map->setPosition(Point(0, 0));
    this->addChild(map, -1);

    addPlayer(map);
    addHeart(map);
    
    playFlyToScene();
    
    Node *ground = Node::create();
    float width = map->getContentSize().width;
    float height = map->getContentSize().height * 3 / 16;

    auto bottomBody = PhysicsBody::createEdgeSegment(Point(0, height), Point(width, height));
    ground->setPhysicsBody(bottomBody);
    this->addChild(ground);
    
    return true;
}

void GameScene::startGame(){
    
    this->scheduleUpdate();
}

void GameScene::playFlyToScene(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    MoveTo* moveto = MoveTo::create(4, Point(120, visibleSize.height * 2 / 3));
    auto callBackFunc = [&](){
        
        mPlayer->getSprite()->getPhysicsBody()->setGravityEnable(true);
        mPlayer->drop();
        startGame();
    };
    CallFunc *callFunc = CallFunc::create(callBackFunc);
    
    mPlayer->flying();
    Action* action = Sequence::create(moveto, callFunc, NULL);
    mPlayer->getSprite()->runAction(action);
}

void GameScene::addPlayer(TMXTiledMap *tmx){
    
    auto physicsBody = PhysicsBody::createBox(Size(63, 155),  PhysicsMaterial(0, 0, 0));
    physicsBody->setGravityEnable(false);

    Sprite *player = Sprite::create("flying1.png");
    player->setPhysicsBody(physicsBody);
    mPlayer = Player::create();
    mPlayer->setPosition(Point(-33, 180));
    mPlayer->bindSprite(player);

    this->addChild(mPlayer);
    mPlayer->addAnimationCache();
}

void GameScene::addHeart(TMXTiledMap *tmx){
    
    ValueVector objects = map->getObjectGroup("heart")->getObjects();
    for (int i = 0; i < objects.size(); i++) {
        
        ValueMap& dict = objects.at(i).asValueMap();
        float x = dict["x"].asFloat();
        float y = dict["y"].asFloat();
        
        Sprite *heart = Sprite::create("heart.png");
        auto physicsBody = PhysicsBody::createCircle(heart->getContentSize().width/2, PhysicsMaterial(0, 0, 1));
        physicsBody->setGravityEnable(false);
        
        heart->setPhysicsBody(physicsBody); //加了物理属性后heart不跟随tmx一起移动
        
        heart->setPosition(Point(x, y));
        
        tmx->addChild(heart);
    }
}

void GameScene::update(float dt){
    
    if (distanceBg.at(1)->getPositionX() <= 0) {
        
        distanceBg.at(0)->setPositionX(0);
    }
    
    float x1 = distanceBg.at(0)->getPositionX() - 50 * dt;
    float x2 = x1 + distanceBg.at(1)->getContentSize().width;
    
    distanceBg.at(0)->setPositionX(x1);
    distanceBg.at(1)->setPositionX(x2);
    
    if(nearbyBg.at(1)->getPositionX() <= 0){
        
        nearbyBg.at(0)->setPositionX(0);
    }
    
    float x3 = nearbyBg.at(0)->getPositionX() - 100 * dt;
    float x4 = nearbyBg.at(1)->getContentSize().width + x3;
    
    nearbyBg.at(0)->setPositionX(x3);
    nearbyBg.at(1)->setPositionX(x4);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

    if(map->getPositionX() <= visibleSize.width - map->getContentSize().width){
        this->unscheduleUpdate();
    }
    float x5 = map->getPositionX() - 130 * dt;
    map->setPositionX(x5);
    
}