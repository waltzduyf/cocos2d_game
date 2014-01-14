#include "PlaneChessEventManager.h"
#include "Enviroment.h"

PlaneChessEventManager::PlaneChessEventManager(void)
{
}


PlaneChessEventManager::~PlaneChessEventManager(void)
{
}

PlaneChessEventManager* PlaneChessEventManager::m_INSTANCE = 0;

PlaneChessEventManager* PlaneChessEventManager::getInstance()
{
    if (m_INSTANCE == 0)
    {
        m_INSTANCE = new PlaneChessEventManager();
    }
    return m_INSTANCE;
}

void PlaneChessEventManager::addEventListener(PlaneChessEventListener *listener)
{
    this->eventListeners.push_back(listener);
}

void PlaneChessEventManager::notifyTurnBegin()
{
    for (vector<PlaneChessEventListener*>::iterator it = eventListeners.begin();
        it != eventListeners.end(); it++)
    {
        (*it)->onTurnBegin();
    }
}

void PlaneChessEventManager::notifyPassNormalGridEvent(Airplane* plane, bool hasJumped)
{
    PassGridEvent *e = new PassGridEvent(plane, hasJumped);
    vector<PlaneChessEventListener*> &listeners = this->eventListeners;
    vector<PlaneChessEventListener*>::iterator iter = listeners.begin();
    while (iter != listeners.end())
    {
        (*iter)->onPassNormalGridEvent(e);
        iter++;
    }
    delete e;
}

void PlaneChessEventManager::notifyThrowingDiceEvent()
{
    for (vector<PlaneChessEventListener*>::iterator it = eventListeners.begin();
        it != eventListeners.end(); it++)
    {
        (*it)->onThrowingDiceEvent();
    }
}

void PlaneChessEventManager::notifyThrownDiceEvent(int point)
{
    ThrownDiceEvent *e = new ThrownDiceEvent();
    e->point = point;
    
    vector<PlaneChessEventListener*> &listeners = this->eventListeners;
    vector<PlaneChessEventListener*>::iterator iter = listeners.begin();
    while (iter != listeners.end())
    {
        (*iter)->onThrownDiceEvent(e);
        iter++;
    }

    delete e;
}

void PlaneChessEventManager::notifyPlaneStopEvent(Airplane* plane, bool hasJumped)
{
    PassGridEvent *e = new PassGridEvent(plane, hasJumped);
    vector<PlaneChessEventListener*> &listeners = this->eventListeners;
    vector<PlaneChessEventListener*>::iterator iter = listeners.begin();
    while (iter != listeners.end())
    {
        (*iter)->onPlaneStop(e);
        iter++;
    }
    delete e;
}
