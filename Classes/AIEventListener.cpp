#include "AIEventListener.h"
#include "Enviroment.h"
#include <algorithm>

using namespace std;


class FlightPlan
{
public:
    Airplane* plane;
    int score;

    virtual void action() {}
};

class MoveFlightPlan : public FlightPlan
{
public:
    virtual void action();
};

class ReadyFlightPlan : public FlightPlan
{
public:
    virtual void action();
};

void MoveFlightPlan::action()
{
    plane->teamMoveByStep(Enviroment::getInstance()->currentPoint);
}

void ReadyFlightPlan::action()
{
    plane->ready();
}

static bool lessFP(FlightPlan *fp1, FlightPlan *fp2)
{
    return fp1->score < fp2->score;
}

void AIEventListener::onTurnBegin()
{
    Enviroment *env = Enviroment::getInstance();
    if (env->isCurrentPlayerAI())
    {
        env->mainScene->_throwDice(0);
    }
}

void AIEventListener::onThrownDiceEvent(ThrownDiceEvent *e)
{
    Enviroment *env = Enviroment::getInstance();
    if (!env->isCurrentPlayerAI() || !env->canMoveAnyPlane())
    {
        return;
    }

    env->isCanControl = false;

    /**
    ������ֿ����ԣ����ֿ����Զ���֣�ѡ���ֵ������ж�
    �ж���Ϊ�������ͣ�1���ƶ��ɻ���2��׼�����
    ��ֵ���£�
    ���Ƕӳ���0������ѡ���ˣ�
    ��ͨ�ƶ���1
    С��Ծ  ��2
    �����  ��3
    ���    ��4
    ����Ծ  ��5
    �ɴ�ɻ���6
    �������7
     **/
    vector<FlightPlan*> *plans = new vector<FlightPlan*>();
    vector<Airplane*> &planes = env->currentChessBoard->planes;
    FOREACH_PLANES(planes)
    {
        Airplane* p = *it;
        if (p->isMyTurn())
        {
            if (p->canMove())
            {
                FlightPlan* fp = new MoveFlightPlan();
                fp->plane = p;
                fp->score = testMovePlane(p);
                plans->push_back(fp);
            }
            else if (p->state == STATE_WAITING && e->point == 6)
            {
                FlightPlan* fp = new ReadyFlightPlan();
                fp->plane = p;
                fp->score = testReadyToFly();
                plans->push_back(fp);
            }
        }
    }

    if (plans->size() == 0)
    {
        return;
    }

    sort(plans->begin(), plans->end(), lessFP);
    
    // ȡ����ֵ���ģ�ִ����
    FlightPlan *goodPlane = plans->at(plans->size() - 1);
    goodPlane->action();

    delete plans;
}

int AIEventListener::testMovePlane(Airplane *p)
{
    if (!p->isLeader())
    {
        return 0;
    }

    ChessBoard* cb = Enviroment::getInstance()->currentChessBoard;

    int point = Enviroment::getInstance()->currentPoint;
    vector<MoveAction*>* flightPlan = cb->genFlightPlan(p, point);

    MoveAction *lastMA = *(flightPlan->end() - 1);
    ChessBoardGrid *end = lastMA->to;

    if (end->type == CHESS_BOARD_GRID_TYPE_END)
    {
        return 7;
    }

    Airplane *enemy = cb->checkIfFight(p, lastMA);
    if (enemy != 0)
    {
        return 6;
    }

    if (lastMA->type == PLAN_ACTION_LONG_JUMP)
    {
        return 5;
    }

    Airplane *overlap = cb->getOverlapPlane(p, end);
    if (overlap != 0)
    {
        return 3;
    }

    if (lastMA->type == PLAN_ACTION_JUMP)
    {
        return 2;
    }

    return 1;
}

int AIEventListener::testReadyToFly()
{
    return 4;
}
