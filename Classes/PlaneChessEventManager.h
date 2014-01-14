#ifndef __PLANE_CHESS_EVENT_MANAGER__
#define __PLANE_CHESS_EVENT_MANAGER__

#include <vector>

#include "PlaneChessEventListener.h"
#include "PassGridEvent.h"
#include "ThrownDiceEvent.h"

using namespace std;

class PlaneChessEventManager
{
private:
    static PlaneChessEventManager* m_INSTANCE;

    vector<PlaneChessEventListener*> eventListeners;

    PlaneChessEventManager(void);
    ~PlaneChessEventManager(void);
public:
    // 单例模式
    static PlaneChessEventManager* getInstance();

    // 添加监听器
    void addEventListener(PlaneChessEventListener *listener);

    void notifyTurnBegin();
    // 通知事件：通过普通格子的事件
    void notifyPassNormalGridEvent(Airplane* plane, bool hasJumped);
    // 通知事件：飞机停止移动
    void notifyPlaneStopEvent(Airplane* plane, bool hasJumped);
    // 通知事件：掷骰子
    void notifyThrowingDiceEvent();
    void notifyThrownDiceEvent(int point);
};

#endif