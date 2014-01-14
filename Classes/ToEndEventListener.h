#ifndef __TOENDEVENTLISTENER__
#define __TOENDEVENTLISTENER__

#include "PlaneChessEventListener.h"

class ToEndEventListener : public PlaneChessEventListener
{
public:
    virtual void onPassNormalGridEvent(PassGridEvent *e);
    virtual void onPlaneStop(PassGridEvent *e);
};

#endif