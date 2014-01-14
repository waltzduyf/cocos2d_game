#ifndef __CHESSSTATEEVENTLISTENER__
#define __CHESSSTATEEVENTLISTENER__

#include "PlaneChessEventListener.h"

class ChessStateEventListener : public PlaneChessEventListener
{
public:
    virtual void onThrowingDiceEvent();
    virtual void onThrownDiceEvent(ThrownDiceEvent *e);
    virtual void onPlaneStop(PassGridEvent *e);
};

#endif