#ifndef __PLANE_CHESS_EVENT_LISTENER__
#define __PLANE_CHESS_EVENT_LISTENER__

#include <PassGridEvent.h>
#include <ThrownDiceEvent.h>

class PlaneChessEventListener
{
public:
    // 在一轮开始时
    virtual void onTurnBegin() {};
    // 处理经过棋盘格子事件
    virtual void onPassNormalGridEvent(PassGridEvent *e) {};
    // 在飞机停止移动的时候触发
    virtual void onPlaneStop(PassGridEvent *e) {};
    // 处理掷骰子事件
    virtual void onThrowingDiceEvent() {};
    virtual void onThrownDiceEvent(ThrownDiceEvent *e) {};
};

#endif