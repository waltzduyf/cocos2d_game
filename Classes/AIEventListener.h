#ifndef __AIEVENTLISTENER__
#define __AIEVENTLISTENER__

#include "PlaneChessEventListener.h"

class AIEventListener : public PlaneChessEventListener
{
public:
    virtual void onTurnBegin();
    virtual void onThrownDiceEvent(ThrownDiceEvent *e);

private:

    int testMovePlane(Airplane *p);
    int testReadyToFly();
};

#endif