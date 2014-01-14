#include "Airplane.h"
#include "Enviroment.h"
#include "PlaneChessEventManager.h"
#include <string.h>
#include <algorithm>

Airplane::Airplane(int color) : direction(DIRECT_FORWARD), state(STATE_WAITING), leader(0), lastPosition(0), position(0)
{
    this->color = color;

    this->members.push_back(this);

    string imgName;
    switch (color)
    {
    case FORCE_COLOR_RED:
        imgName = "plane_r.png";
        break;
    case FORCE_COLOR_YELLOW:
        imgName = "plane_y.png";
        break;
    case FORCE_COLOR_GREEN:
        imgName = "plane_g.png";
        break;
    case FORCE_COLOR_BLUE:
        imgName = "plane_b.png";
        break;
    }
    
    CCSprite* plane = CCSprite::create(imgName.c_str());
    addChild(plane);

    setContentSize(CCSizeMake(30, 30));

    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}


Airplane::~Airplane(void)
{
}

void Airplane::move()
{
    if (this->position == NULL)
    {
        return;
    }

    Enviroment* env = Enviroment::getInstance();

    if (this->remainStep <= 0)
    {
        if (isCanJump())
        {
            ChessBoardGrid* jumpDest = Enviroment::getInstance()->currentChessBoard->getJumpDest(this, this->position);
            jump(jumpDest);
        }
        else
        {
            PlaneChessEventManager::getInstance()->notifyPlaneStopEvent(this, false);
        }

        return;
    }

    this->state = STATE_FLYING;

    Enviroment::getInstance()->isCanControl = false;

    this->remainStep--;

    ChessBoard* chessBoard = env->currentChessBoard;

    ChessBoardGrid* nextGrid;
    if (direction == DIRECT_FORWARD)
    {
        nextGrid = chessBoard->getNextGrid(this, this->position);
    }
    else
    {
        nextGrid = chessBoard->getPreGrid(this, this->position);
    }
    moveTo(nextGrid, callfunc_selector(Airplane::normalMoveCallback));
}

void Airplane::moveTo(ChessBoardGrid* grid, SEL_CallFunc callbackFunc)
{
    changePosition(grid);
    CCMoveTo* moveAction = CCMoveTo::create(0.3f, *(grid->position));
    this->runAction(CCSequence::create(moveAction, CCCallFunc::create(this, callbackFunc), NULL));
}

void Airplane::moveByStep(int step)
{
    this->remainStep = step;
    this->move();
}

void Airplane::teamMoveByStep(int step)
{
    FOREACH_PLANES(members)
    {
        (*it)->moveByStep(step);
    }
}

void Airplane::jump(ChessBoardGrid *position)
{
    if (position == 0)
    {
        return;
    }

    changePosition(position);
    CCMoveTo* moveAction = CCMoveTo::create(0.5f, *(position->position));
    this->runAction(CCSequence::create(moveAction, CCCallFunc::create(this, callfunc_selector(Airplane::jumpedCallback)), NULL));
}

void Airplane::moveToNow(ChessBoardGrid* grid)
{
    setPosition(ccp(grid->position->x, grid->position->y));
    changePosition(grid);
}

void Airplane::changePosition(ChessBoardGrid* p)
{
    this->lastPosition = this->position;
    this->position = p;
}

void Airplane::normalMoveCallback()
{
    // 触发经过格子事件
    PlaneChessEventManager::getInstance()->notifyPassNormalGridEvent(this, false);

    // 再来个move
    this->move();
}

void Airplane::jumpedCallback()
{
    // 触发经过格子事件
    PlaneChessEventManager::getInstance()->notifyPassNormalGridEvent(this, true);
    PlaneChessEventManager::getInstance()->notifyPlaneStopEvent(this, true);
}

void Airplane::ready()
{
    this->state = STATE_READY;
    ChessBoardGrid* field = Enviroment::getInstance()->currentChessBoard->getStartPointGrid(this->color);
    moveTo(field, callfunc_selector(Airplane::readyCallback));
}

void Airplane::readyCallback()
{
    Enviroment::getInstance()->turnNext();
}

void Airplane::complete()
{
    ChessBoardGrid* field = Enviroment::getInstance()->currentChessBoard->getFreeAirplaneField(this->color);
    this->moveToNow(field);
    this->state = STATE_COMPLETE;
}

void Airplane::returnHome()
{
    ChessBoardGrid* field = Enviroment::getInstance()->currentChessBoard->getFreeAirplaneField(this->color);
    this->moveToNow(field);
    this->state = STATE_WAITING;
}

void Airplane::teamReturnHome()
{
    Airplane* leader = getLeader();
    vector<Airplane*> tempVector(leader->members);
    for (vector<Airplane*>::iterator it = tempVector.begin();
        it != tempVector.end(); it++)
    {
        Airplane* temp = *it;
        temp->leaveTeam();
        temp->returnHome();
    }
}

void Airplane::fight(Airplane* dest)
{
    vector<Airplane*>* newMem = dest->getTeamMembers();
    vector<Airplane*>* oldMem = getTeamMembers();
    if (newMem->size() < oldMem->size())
    {
        // 少打多，都回家
        dest->teamReturnHome();
        getLeader()->teamReturnHome();
    }
    else
    {
        // 多打少，或相等，被打的回家
        dest->teamReturnHome();
    }
}

bool Airplane::containsTouchLocation(CCTouch* touch)
{
    CCPoint touchP = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());

    float x1 = this->getParent()->getPositionX() + this->getPositionX() - this->getContentSize().width / 2;
    float y1 = this->getParent()->getPositionY() + this->getPositionY() - this->getContentSize().height / 2;

    float x2 = this->getParent()->getPositionX() + this->getPositionX() + this->getContentSize().width / 2;
    float y2 = this->getParent()->getPositionY() + this->getPositionY() + this->getContentSize().height / 2;

    return touchP.x > x1 && touchP.x < x2 && touchP.y > y1 && touchP.y < y2;
}

bool Airplane::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    if (!Enviroment::getInstance()->isCanControl
        || this->state == STATE_COMPLETE
        || Enviroment::getInstance()->state != CHESS_BOARD_STATE_MOVE
        || !isMyTurn() || !isLeader())
    {
        return false;
    }

    return containsTouchLocation(touch);
}

void Airplane::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    if (this->state == STATE_WAITING && Enviroment::getInstance()->currentPoint == 6)
    {
        this->ready();
    }
    else if (canMove())
    {
        int point = Enviroment::getInstance()->currentPoint;
        this->teamMoveByStep(point);
    }
}

bool Airplane::isMyTurn()
{
    return this->color == Enviroment::getInstance()->currentColor;
}

bool Airplane::isCanJump()
{
    return position->autoJump && position->color == this->color;
}

Airplane* Airplane::getLeader() {
    return leader == 0 ? this : leader;
}

vector<Airplane*>* Airplane::getTeamMembers()
{
    Airplane* leader = getLeader();
    return &(leader->members);
}

void Airplane::joinATeam(Airplane* memberInTeamToJoin)
{
    Airplane* leader = memberInTeamToJoin->getLeader();
    leader->members.push_back(this);
    this->leader = leader;
}

void Airplane::leaveTeam()
{
    if (this->isLeader())
    {
        return;
    }
    vector<Airplane*> *mem = getTeamMembers();
    vector<Airplane*>::iterator toRemove;
    for (vector<Airplane*>::iterator it = mem->begin();
        it != mem->end(); it++)
    {
        Airplane* temp = *it;
        if (temp == this)
        {
            toRemove = it;
            break;
        }
    }
    mem->erase(toRemove);

    this->leader = 0;
}

bool Airplane::isLeader()
{
    return leader == 0;
}

bool Airplane::canMove()
{
    return this->state == STATE_READY || this->state == STATE_FLYING;
}