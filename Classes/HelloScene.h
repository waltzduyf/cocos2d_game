#ifndef __HELLOSCENE__
#define __HELLOSCENE__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

class HelloScene : public CCLayer
{
public:

    static CCScene* scene();
    virtual bool init();

    CREATE_FUNC(HelloScene);

private:

    void addSetupSwitch(const CCPoint &position, string lable, const ccColor3B &c, int colorCode);//, SEL_CCControlHandler joinInFunc, SEL_CCControlHandler aiFunc);

    void menuCloseCallback(CCObject* pSender);

    void playBtnCallback(CCObject* pSender, CCControlEvent e);
};

#endif