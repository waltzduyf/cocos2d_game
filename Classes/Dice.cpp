#include "Dice.h"
#include "Enviroment.h"
#include "ThrownDiceEvent.h"
#include "PlaneChessEventManager.h"
#include "RandomAsJava.h"

void Dice::onEnter()
{
    CCNode::onEnter();

    progress = CCSprite::create();
    addChild(progress);
}

void Dice::throwIt(int point)
{
    PlaneChessEventManager::getInstance()->notifyThrowingDiceEvent();

    this->point = point;

    Enviroment *env = Enviroment::getInstance();
    env->currentPoint = point;

    CCAnimation *animation = CCAnimation::create();
    animation->addSpriteFrameWithFileName("d4.png");
    animation->addSpriteFrameWithFileName("d3.png");
    animation->addSpriteFrameWithFileName("d5.png");
    animation->addSpriteFrameWithFileName("d2.png");
    animation->addSpriteFrameWithFileName("d6.png");
    animation->addSpriteFrameWithFileName("d1.png");
    progress->setVisible(true);
    char fileName[10];
    sprintf(fileName, "dr%d.png", point);
    animation->addSpriteFrameWithFileName(fileName);

    animation->setDelayPerUnit(0.1f);

    progress->runAction(CCSequence::create(CCAnimate::create(animation), CCDelayTime::create(1), CCCallFunc::create(this, callfunc_selector(Dice::throwCallback)), 0));
}

void Dice::throwIt()
{
    int point = RandomAsJava::nextInt(5) + 1;
    throwIt(point);
}

void Dice::reset()
{
    progress->setVisible(false);
}

void Dice::throwCallback()
{
    PlaneChessEventManager::getInstance()->notifyThrownDiceEvent(this->point);
}
