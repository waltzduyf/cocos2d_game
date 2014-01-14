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
    // ����ģʽ
    static PlaneChessEventManager* getInstance();

    // ��Ӽ�����
    void addEventListener(PlaneChessEventListener *listener);

    void notifyTurnBegin();
    // ֪ͨ�¼���ͨ����ͨ���ӵ��¼�
    void notifyPassNormalGridEvent(Airplane* plane, bool hasJumped);
    // ֪ͨ�¼����ɻ�ֹͣ�ƶ�
    void notifyPlaneStopEvent(Airplane* plane, bool hasJumped);
    // ֪ͨ�¼���������
    void notifyThrowingDiceEvent();
    void notifyThrownDiceEvent(int point);
};

#endif