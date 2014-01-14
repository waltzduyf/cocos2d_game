#include "HelloScene.h"
#include "VisibleRect.h"
#include "ChessBoardScene.h"
#include "Enviroment.h"

CCScene* HelloScene::scene()
{
    CCScene *scene = CCScene::create();
    HelloScene *thisLayer = HelloScene::create();

    scene->addChild(thisLayer);

    return scene;
}

bool HelloScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }

    CCSprite *bg = CCSprite::create("background.png");
    bg->setPosition(VisibleRect::center());
    //CCSize &winSize = CCDirector::sharedDirector()->getWinSize();
    //float scalex = winSize.width / 480;
    //float scaley = winSize.height / 800;
    //bg->setScaleX(scalex);
    //bg->setScaleY(scaley);
    addChild(bg);

    const CCPoint &center = VisibleRect::center();

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        this,
        menu_selector(HelloScene::menuCloseCallback));
    pCloseItem->setPosition(ccp(VisibleRect::rightBottom().x - pCloseItem->getContentSize().width/2 ,
        pCloseItem->getContentSize().height/2));
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    CCLabelTTF *title = CCLabelTTF::create("Lovexin Plane Chess", "Arial", 40);
    title->setPosition(ccp(center.x, center.y + 250));
    CCLabelTTF *author = CCLabelTTF::create("made by Waltz Duyf", "Arial", 20);
    author->setPosition(ccp(center.x + 100, center.y + 200));
    addChild(title);
    addChild(author);

    addSetupSwitch(ccp(center.x - 120, center.y + 50 ), "RED", ccc3(255, 0, 0), FORCE_COLOR_RED);//, cccontrol_selector(HelloScene::valueChangedJoinInR), cccontrol_selector(HelloScene::valueChangedAIR));
    addSetupSwitch(ccp(center.x - 120, center.y - 10 ), "YEL", ccc3(234, 165, 0), FORCE_COLOR_YELLOW);//, cccontrol_selector(HelloScene::valueChangedJoinInY), cccontrol_selector(HelloScene::valueChangedAIY));
    addSetupSwitch(ccp(center.x - 120, center.y - 70 ), "GRE", ccc3(0, 255, 0), FORCE_COLOR_GREEN);//, cccontrol_selector(HelloScene::valueChangedJoinInG), cccontrol_selector(HelloScene::valueChangedAIG));
    addSetupSwitch(ccp(center.x - 120, center.y - 130), "BLU", ccc3(0, 144, 255), FORCE_COLOR_BLUE);//, cccontrol_selector(HelloScene::valueChangedJoinInB), cccontrol_selector(HelloScene::valueChangedAIB));

    CCScale9Sprite *backgroundButton = CCScale9Sprite::create("button.png");
    CCScale9Sprite *backgroundHighlightedButton = CCScale9Sprite::create("buttonHighlighted.png");
    CCLabelTTF *titleButton = CCLabelTTF::create("Play Now", "Arial", 30);
    titleButton->setColor(ccc3(159, 168, 176));
    CCControlButton *button = CCControlButton::create(titleButton, backgroundButton);
    button->setBackgroundSpriteForState(backgroundHighlightedButton, CCControlStateHighlighted);
    button->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
    button->setMargins(70, 20);
    button->setPosition(ccp(center.x, center.y - 250));
    addChild(button);
    button->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloScene::playBtnCallback), CCControlEventTouchUpInside);

    return true;
}

void HelloScene::menuCloseCallback(CCObject* pSender)
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

void HelloScene::addSetupSwitch(const CCPoint &position, string lable, const ccColor3B &c, int colorCode)//, SEL_CCControlHandler joinInFunc, SEL_CCControlHandler aiFunc)
{
    CCLabelTTF *lab = CCLabelTTF::create(lable.c_str(), "Arial", 24);
    lab->setColor(c);
    lab->setPosition(position);
    addChild(lab);

    CCControlSwitch *consJoinIn = CCControlSwitch::create(
        CCSprite::create("switch-mask.png"),
        CCSprite::create("switch-on.png"),
        CCSprite::create("switch-off.png"),
        CCSprite::create("switch-thumb.png"),
        CCLabelTTF::create("In", "Arial", 20),
        CCLabelTTF::create("Out", "Arial", 20)
        );
    consJoinIn->setPosition(ccp(position.x + 110, position.y));
    addChild(consJoinIn, 10, 100 + colorCode * 10 + 1);
    //consJoinIn->addTargetWithActionForControlEvents(this, joinInFunc, CCControlEventValueChanged);

    CCControlSwitch *consAI = CCControlSwitch::create(
        CCSprite::create("switch-mask.png"),
        CCSprite::create("switch-on.png"),
        CCSprite::create("switch-off.png"),
        CCSprite::create("switch-thumb1.png"),
        CCLabelTTF::create("PLY", "Arial", 20),
        CCLabelTTF::create("NPC", "Arial", 20)
        );
    consAI->setPosition(ccp(position.x + 220, position.y));
    addChild(consAI, 10, 100 + colorCode * 10 + 2);
    //consAI->addTargetWithActionForControlEvents(this, aiFunc, CCControlEventValueChanged);
}

void HelloScene::playBtnCallback(CCObject* pSender, CCControlEvent e)
{
    Enviroment *env = Enviroment::getInstance();
    for (int i = 1; i <= 4; i++)
    {
        CCControlSwitch *consJoinIn = (CCControlSwitch*) getChildByTag(100 + i * 10 + 1);
        CCControlSwitch *consAI = (CCControlSwitch*) getChildByTag(100 + i * 10 + 2);

        if (consJoinIn->isOn())
        {
            env->players.add(i);
        }

        env->AIMap.insert(map<int, bool>::value_type(i, !consAI->isOn()));
    }

    CCDirector::sharedDirector()->purgeCachedData();
    CCScene *chessBoardScene = ChessBoardScene::scene();
    CCTransitionScene *tran = CCTransitionShrinkGrow::create(0.7f, chessBoardScene);
    CCDirector::sharedDirector()->replaceScene(tran);
}
