#ifndef __DICE__
#define __DICE__

#include "cocos2d.h"
#include <vector>

using namespace std;
USING_NS_CC;

class Dice : public CCNode
{
private:
    CCSprite* progress;
    int point;
public:
    virtual void onEnter();
    void throwCallback();

    void reset();
    void throwIt();
    void throwIt(int point);
};
#endif