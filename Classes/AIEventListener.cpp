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
    计算各种可能性，各种可能性都算分，选择分值大的来行动
    行动分为两种类型：1、移动飞机，2、准备起飞
    分值如下，
    不是队长：0（不会选他了）
    普通移动：1
    小跳跃  ：2
    可组队  ：3
    起飞    ：4
    大跳跃  ：5
    可打飞机：6
    完成任务：7
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
    
    // 取出分值最大的，执行它
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
