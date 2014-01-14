#ifndef __CHESSBOARD_SCENE_H__
#define __CHESSBOARD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ChessBoardScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(ChessBoardScene);

    virtual void onEnter();

    void throwDice(CCObject* pSender, CCControlEvent e);
    void throw1(CCObject* pSender);
    void throw2(CCObject* pSender);
    void throw3(CCObject* pSender);
    void throw4(CCObject* pSender);
    void throw5(CCObject* pSender);
    void throw6(CCObject* pSender);
    void _throwDice(int point);

    void showTurn(int color);
    void resetDice();
};

#endif
