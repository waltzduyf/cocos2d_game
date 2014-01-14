#ifndef __PLANEJUMPSTRIKEEVENTLISTENER__
#define __PLANEJUMPSTRIKEEVENTLISTENER__

#include "PlaneChessEventListener.h"

class PlaneJumpStrikeEventListener : public PlaneChessEventListener
{
public:
    virtual void onPassNormalGridEvent(PassGridEvent *e);
};

#endif