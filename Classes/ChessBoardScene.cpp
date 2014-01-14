#include "ChessBoardScene.h"
#include "RandomAsJava.h"
#include "ChessBoard.h"
#include "Enviroment.h"
#include "PlaneChessEventManager.h"
#include "PlaneStrikeEventListener.h"
#include "ToEndEventListener.h"
#include "ChessStateEventListener.h"
#include "PlaneTeamEventListener.h"
#include "PlaneJumpStrikeEventListener.h"
#include "AIEventListener.h"
#include "Dice.h"
#include "VisibleRect.h"

using namespace std;

USING_NS_CC;

CCScene* ChessBoardScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ChessBoardScene *layer = ChessBoardScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    Enviroment::getInstance()->mainScene = layer;

    // ×¢²áÊÂ¼şÏìÓ¦
    PlaneChessEventManager::getInstance()->addEventListener(new PlaneTeamEventListener());
    PlaneChessEventManager::getInstance()->addEventListener(new PlaneStrikeEventListener());
    PlaneChessEventManager::getInstance()->addEventListener(new PlaneJumpStrikeEventListener());
    PlaneChessEventManager::getInstance()->addEventListener(new ToEndEventListener());
    PlaneChessEventManager::getInstance()->addEventListener(new AIEventListener());

    PlaneChessEventManager::getInstance()->addEventListener(new ChessStateEventListener());

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChessBoardScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSprite *bg = CCSprite::create("background.png");
    bg->setPosition(VisibleRect::center());
    addChild(bg);

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(ChessBoardScene::menuCloseCallback));
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    // »æÖÆÆåÅÌ
    ChessBoard* chessBoard = ChessBoard::createChessBoard(0);
    chessBoard->setContentSize(CCSizeMake(450, 450));
    Enviroment::getInstance()->currentChessBoard = chessBoard;
    chessBoard->setPosition(ccp(visibleSize.width / 2 + origin.x,
        visibleSize.height + origin.y - (visibleSize.width - chessBoard->getContentSize().width) / 2 - chessBoard->getContentSize().height / 2));
    this->addChild(chessBoard, 0, 10);

    //CCMenuItemImage *pDiceItemR = CCMenuItemImage::create(
    //    "btn.png",
    //    "btn_p.png",
    //    this,
    //    menu_selector(ChessBoardScene::throwDice));
    //CCMenuItemImage *pDiceItem1 = CCMenuItemImage::create(
    //    "btn.png",
    //    "btn_p.png",
    //    this,
    //    menu_selector(ChessBoardScene::throw1));
    //CCMenuItemImage *pDiceItem2 = CCMenuItemImage::create(
    //    "btn.png",
    //    "btn_p.png",
    //    this,
    //    menu_selector(ChessBoardScene::throw2));
    //CCMenuItemImage *pDiceItem3 = CCMenuItemImage::create(
    //    "btn.png",
    //    "btn_p.png",
    //    this,
    //    menu_selector(ChessBoardScene::throw3));
    //CCMenuItemImage *pDiceItem4 = CCMenuItemImage::create(
    //    "btn.png",
    //    "btn_p.png",
    //    this,
    //    menu_selector(ChessBoardScene::throw4));
    //CCMenuItemImage *pDiceItem5 = CCMenuItemImage::create(
    //    "btn.png",
    //    "btn_p.png",
    //    this,
    //    menu_selector(ChessBoardScene::throw5));
    //CCMenuItemImage *pDiceItem6 = CCMenuItemImage::create(
    //    "btn.png",
    //    "btn_p.png",
    //    this,
    //    menu_selector(ChessBoardScene::throw6));
    //CCMenu* pDiceMenu = CCMenu::create(pDiceItemR, pDiceItem1, pDiceItem2, pDiceItem3, pDiceItem4, pDiceItem5, pDiceItem6, NULL);
    //pDiceMenu->alignItemsHorizontally();
    //pDiceMenu->setPosition(ccp(visibleSize.width / 2 + origin.x, 250));
    //this->addChild(pDiceMenu, 1, 5);

    CCScale9Sprite *backgroundButton = CCScale9Sprite::create("button.png");
    CCScale9Sprite *backgroundHighlightedButton = CCScale9Sprite::create("buttonHighlighted.png");
    CCLabelTTF *titleButton = CCLabelTTF::create("Throw Dice", "Arial", 30);
    titleButton->setColor(ccc3(159, 168, 176));
    CCControlButton *button = CCControlButton::create(titleButton, backgroundButton);
    button->setBackgroundSpriteForState(backgroundHighlightedButton, CCControlStateHighlighted);
    button->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
    button->setMargins(70, 20);
    button->setPosition(ccp(visibleSize.width / 2 + origin.x, 250));
    addChild(button);
    button->addTargetWithActionForControlEvents(this, cccontrol_selector(ChessBoardScene::throwDice), CCControlEventTouchUpInside);

    Dice* dice = new Dice();
    dice->setPosition(ccp(origin.x + visibleSize.width/2, visibleSize.height - chessBoard->getContentSize().height - 180));
    this->addChild(dice, 10, 123);

    CCLabelTTF* pLabel2 = CCLabelTTF::create("", "Arial", 24);
    pLabel2->setPosition(ccp(origin.x + visibleSize.width/2, visibleSize.height - chessBoard->getContentSize().height - 240));
    this->addChild(pLabel2, 10, 124);

    return true;
}

void ChessBoardScene::onEnter()
{
    CCNode::onEnter();
    Enviroment::getInstance()->turnNext();
    Enviroment::getInstance()->isCanControl = true;
}


void ChessBoardScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void ChessBoardScene::throwDice(CCObject* pSender, CCControlEvent e)
{
    _throwDice(0);
}

void ChessBoardScene::throw1(CCObject* pSender)
{
    _throwDice(1);
}

void ChessBoardScene::throw2(CCObject* pSender)
{
    _throwDice(2);
}

void ChessBoardScene::throw3(CCObject* pSender)
{
    _throwDice(3);
}

void ChessBoardScene::throw4(CCObject* pSender)
{
    _throwDice(4);
}

void ChessBoardScene::throw5(CCObject* pSender)
{
    _throwDice(5);
}

void ChessBoardScene::throw6(CCObject* pSender)
{
    _throwDice(6);
}

void ChessBoardScene::_throwDice(int point)
{
    if (Enviroment::getInstance()->isCanControl 
        && Enviroment::getInstance()->state == CHESS_BOARD_STATE_THROW)
    {
        Dice* dice = (Dice*) getChildByTag(123);
        if (point == 0)
        {
            dice->throwIt();
        }
        else
        {
            dice->throwIt(point);
        }
    }
}

void ChessBoardScene::showTurn(int color)
{
    string* msg;
    ccColor3B color3b;
    switch (color)
    {
    case FORCE_COLOR_RED: 
        msg = new string("red");
        color3b = ccc3(255, 0, 0);
        break;
    case FORCE_COLOR_YELLOW: 
        msg = new string("yellow");
        color3b = ccc3(234, 165, 0);
        break;
    case FORCE_COLOR_GREEN: 
        msg = new string("green");
        color3b = ccc3(0, 255, 0);
        break;
    case FORCE_COLOR_BLUE: 
        msg = new string("blue");
        color3b = ccc3(0, 144, 255);
        break;
    }
    CCLabelTTF *pLabel = (CCLabelTTF *) this->getChildByTag(124);
    pLabel->setString(msg->c_str());
    pLabel->setColor(color3b);
    delete msg;
}

void ChessBoardScene::resetDice()
{
    Dice* dice = (Dice*) getChildByTag(123);
    dice->reset();
}