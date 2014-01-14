#ifndef __PLANE_CHESS_EVENT_LISTENER__
#define __PLANE_CHESS_EVENT_LISTENER__

#include <PassGridEvent.h>
#include <ThrownDiceEvent.h>

class PlaneChessEventListener
{
public:
    // ��һ�ֿ�ʼʱ
    virtual void onTurnBegin() {};
    // ���������̸����¼�
    virtual void onPassNormalGridEvent(PassGridEvent *e) {};
    // �ڷɻ�ֹͣ�ƶ���ʱ�򴥷�
    virtual void onPlaneStop(PassGridEvent *e) {};
    // �����������¼�
    virtual void onThrowingDiceEvent() {};
    virtual void onThrownDiceEvent(ThrownDiceEvent *e) {};
};

#endif