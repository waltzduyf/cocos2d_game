#include "ChessBoard.h"
#include "Enviroment.h"
#include "RandomAsJava.h"
#include "ChessBoardScene.h"
#include "ThrownDiceEvent.h"
#include "PlaneChessEventManager.h"

ChessBoard::ChessBoard(void)
{

}

ChessBoard::~ChessBoard(void)
{

}

ChessBoardGrid* ChessBoard::getNextGrid(Airplane *plane, ChessBoardGrid* fromPos)
{
    map<ChessBoardGrid*, map<int, ChessBoardGrid*>*>::iterator cross = crosses.find(fromPos);
    if (cross != crosses.end())
    {
        map<int, ChessBoardGrid*> &crossMap = *(*cross).second;
        map<int, ChessBoardGrid*>::iterator road = crossMap.find(plane->color);
        if (road != crossMap.end())
        {
            return road->second;
        }
    }

    return fromPos->next;
}

ChessBoardGrid* ChessBoard::getPreGrid(Airplane *plane, ChessBoardGrid* fromPos)
{
    return fromPos->pre;
}

ChessBoard* ChessBoard::createChessBoard(string* filePath)
{
    // TODO 读取配置文件。。。先不读配置文件了
    ChessBoard* result = new ChessBoard();
    result->initChess();

    return result;
}

void ChessBoard::initPlanes()
{
    FOREACH_PLANES(planes)
    {
        delete *it;
    }
    planes.clear();

    const vector<int> &players = Enviroment::getInstance()->players.getVector();
    for (vector<int>::const_iterator it = players.begin(); it != players.end(); it++)
    {
        initPlaneColor(*it);
    }
}

void ChessBoard::initPlaneColor(int color)
{
    vector<ChessBoardGrid*> fields = this->airplaneFields.at(color);
    vector<ChessBoardGrid*>::iterator it = fields.begin();
    int t = 0;
    while (it != fields.end())
    {
        Airplane* plane = new Airplane(color);
        //if(color == 2) {
        //    plane->state = STATE_FLYING;
        //    ChessBoardGrid* grid = grids.at();
        //    plane->moveTo(grid);
        //    t++;
        //}
        //else
        //{
        ChessBoardGrid* grid = *it;
        addChild(plane, 20);
        plane->moveToNow(grid);
        //}
        this->planes.push_back(plane);
        it++;
    }
}

ChessBoardGrid* ChessBoard::createGrid(CCPoint* pos, int color, int type)
{
    ChessBoardGrid* grid = new ChessBoardGrid(nextGridId(), pos, color, type);
    this->grids.insert(map<int, ChessBoardGrid*>::value_type(grid->id, grid));

    return grid;
}

void ChessBoard::initChess()
{
    CCSprite* bg = CCSprite::create("chessboard.png");
    bg->setPosition(ccp(0, 0));
    this->addChild(bg, 0, 1);

    // 组装棋盘格子 开始
    CircularLinkedList<int>* colorOrder = new CircularLinkedList<int>();
    colorOrder->add(FORCE_COLOR_YELLOW);
    colorOrder->add(FORCE_COLOR_GREEN);
    colorOrder->add(FORCE_COLOR_BLUE);
    colorOrder->add(FORCE_COLOR_RED);

    int joinPoint, firstCrossPoint;
    ChessBoardGrid* firstGrid = createGrid(new CCPoint(-90, -210), colorOrder->getCurrent(), CHESS_BOARD_GRID_TYPE_NORMAL);
    joinPoint = firstGrid->id;
    addStartPoint(FORCE_COLOR_GREEN, joinPoint, -120, -210);
    joinPoint = autoAddGrid(joinPoint, 0, 30, colorOrder, 3);
    joinPoint = autoAddGrid(joinPoint, -30, 30, colorOrder, 1);
    joinPoint = autoAddGrid(joinPoint, -30, 0, colorOrder, 3);
    joinPoint = autoAddGrid(joinPoint, 0, 30, colorOrder, 3);
    setLastGridNotJump();
    firstCrossPoint = addEndGrids(joinPoint, 30, 0, 6);
    genCross(joinPoint, firstCrossPoint, FORCE_COLOR_BLUE);
    joinPoint = autoAddGrid(joinPoint, 0, 30, colorOrder, 3);
    addStartPoint(FORCE_COLOR_BLUE, joinPoint, -210, 120);
    joinPoint = autoAddGrid(joinPoint, 30, 0, colorOrder, 3);
    joinPoint = autoAddGrid(joinPoint, 30, 30, colorOrder, 1);
    joinPoint = autoAddGrid(joinPoint, 0, 30, colorOrder, 3);
    joinPoint = autoAddGrid(joinPoint, 30, 0, colorOrder, 3);
    setLastGridNotJump();
    firstCrossPoint = addEndGrids(joinPoint, 0, -30, 6);
    genCross(joinPoint, firstCrossPoint, FORCE_COLOR_RED);
    joinPoint = autoAddGrid(joinPoint, 30, 0, colorOrder, 3);
    addStartPoint(FORCE_COLOR_RED, joinPoint, 120, 210);
    joinPoint = autoAddGrid(joinPoint, 0, -30, colorOrder, 3);
    joinPoint = autoAddGrid(joinPoint, 30, -30, colorOrder, 1);
    joinPoint = autoAddGrid(joinPoint, 30, 0, colorOrder, 3);
    joinPoint = autoAddGrid(joinPoint, 0, -30, colorOrder, 3);
    setLastGridNotJump();
    firstCrossPoint = addEndGrids(joinPoint, -30, 0, 6);
    genCross(joinPoint, firstCrossPoint, FORCE_COLOR_YELLOW);
    joinPoint = autoAddGrid(joinPoint, 0, -30, colorOrder, 3);
    addStartPoint(FORCE_COLOR_YELLOW, joinPoint, 210, -120);
    joinPoint = autoAddGrid(joinPoint, -30, 0, colorOrder, 3);
    joinPoint = autoAddGrid(joinPoint, -30, -30, colorOrder, 1);
    joinPoint = autoAddGrid(joinPoint, 0, -30, colorOrder, 3);
    joinPoint = autoAddGrid(joinPoint, -30, 0, colorOrder, 3);
    setLastGridNotJump();
    firstCrossPoint = addEndGrids(joinPoint, 0, 30, 6);
    genCross(joinPoint, firstCrossPoint, FORCE_COLOR_GREEN);
    joinPoint = autoAddGrid(joinPoint, -30, 0, colorOrder, 2);

    ChessBoardGrid* lastGrid = this->grids.at(joinPoint);
    lastGrid->next = firstGrid;
    firstGrid->pre = lastGrid;

    // 飞机场
    genPlaneFields(FORCE_COLOR_RED, new CCPoint(150, 150));
    genPlaneFields(FORCE_COLOR_YELLOW, new CCPoint(150, -180));
    genPlaneFields(FORCE_COLOR_GREEN, new CCPoint(-180, -180));
    genPlaneFields(FORCE_COLOR_BLUE, new CCPoint(-180, 150));

    // 大跳映射
    genLongJumpMaps( 6, 25);
    genLongJumpMaps(26, 45);
    genLongJumpMaps(46, 65);
    genLongJumpMaps(66, 5);

    // 大跳能打掉的格子映射
    // 起点-》被打掉的格子
    genLongJumpFightMaps( 6, 15);
    genLongJumpFightMaps(26, 35);
    genLongJumpFightMaps(46, 55);
    genLongJumpFightMaps(66, 75);

    CCLog("chess board ready, %d grids.", this->grids.size());

    delete colorOrder;
    // 组装棋盘格子完毕

    // 初始化飞机
    this->initPlanes();
    // 初始化飞机结束
}

int ChessBoard::autoAddGrid(int joinPoint, float dx, float dy, CircularLinkedList<int>* colorOrder, int step)
{
    ChessBoardGrid* before = grids.at(joinPoint);

    while (step > 0)
    {
        float x = before->position->x + dx;
        float y = before->position->y + dy;

        ChessBoardGrid* next = createGrid(new CCPoint(x, y), colorOrder->next(), CHESS_BOARD_GRID_TYPE_NORMAL);
        before->next = next;
        next->pre = before;

        before = next;
        step--;
    }

    return before->id;
}

void ChessBoard::setLastGridNotJump() 
{
    ChessBoardGrid* before = grids.at(grids.size());
    before->autoJump = false;
}

int ChessBoard::addEndGrids(int joinPoint, float dx, float dy, int step)
{
    ChessBoardGrid* before = grids.at(joinPoint);
    int tempStep = step;

    while (step > 0)
    {
        float x = before->position->x + dx;
        float y = before->position->y + dy;

        int type = step == 1 ? CHESS_BOARD_GRID_TYPE_END : CHESS_BOARD_GRID_TYPE_NORMAL;

        CCPoint* point = new CCPoint(x, y);
        ChessBoardGrid* next = createGrid(point, FORCE_COLOR_NULL, type);;

        if (tempStep != step)
        {
            before->next = next;
        }
        next->pre = before;

        before = next;
        step--;
    }

    return joinPoint + 1;
}

void ChessBoard::genCross(int from, int to, int color)
{
    ChessBoardGrid* fromPosition = this->grids.at(from);
    ChessBoardGrid* toPosition = this->grids.at(to);
    map<int, ChessBoardGrid*>* crossMap = new map<int, ChessBoardGrid*>();
    crossMap->insert(map<int, ChessBoardGrid*>::value_type(color, toPosition));
    this->crosses.insert(map<ChessBoardGrid*, map<int, ChessBoardGrid*>*>::value_type(fromPosition, crossMap));
}

void ChessBoard::genLongJumpMaps(int from, int to)
{
    ChessBoardGrid* fromGrid = grids.at(from);
    ChessBoardGrid* toGrid = grids.at(to);

    this->longJumpMaps.insert(map<ChessBoardGrid*, ChessBoardGrid*>::value_type(fromGrid, toGrid));
}

void ChessBoard::genLongJumpFightMaps(int from, int fightGrid)
{
    ChessBoardGrid* fromGrid = grids.at(from);
    ChessBoardGrid* fightGridObj = grids.at(fightGrid);

    this->longJumpFightMaps.insert(map<ChessBoardGrid*, ChessBoardGrid*>::value_type(fromGrid, fightGridObj));
}

void ChessBoard::genPlaneFields(int color, CCPoint *leftButton)
{
    vector<ChessBoardGrid*> fields;
    fields.push_back(new ChessBoardGrid(0, leftButton, CHESS_BOARD_GRID_TYPE_AIRPORT, FORCE_COLOR_NULL));
    fields.push_back(new ChessBoardGrid(0, new CCPoint(leftButton->x + 30, leftButton->y), CHESS_BOARD_GRID_TYPE_AIRPORT, FORCE_COLOR_NULL));
    fields.push_back(new ChessBoardGrid(0, new CCPoint(leftButton->x, leftButton->y + 30), CHESS_BOARD_GRID_TYPE_AIRPORT, FORCE_COLOR_NULL));
    fields.push_back(new ChessBoardGrid(0, new CCPoint(leftButton->x + 30, leftButton->y + 30), CHESS_BOARD_GRID_TYPE_AIRPORT, FORCE_COLOR_NULL));

    this->airplaneFields.insert(map<int, vector<ChessBoardGrid*> >::value_type(color, fields));
}

void ChessBoard::addStartPoint(int color, int joinPoint, float dx, float dy)
{
    ChessBoardGrid* startPoint = createGrid(new CCPoint(dx, dy), CHESS_BOARD_GRID_TYPE_NORMAL, FORCE_COLOR_NULL);
    startPoint->next = grids.at(joinPoint);
    this->startPoints.insert(map<int, ChessBoardGrid*>::value_type(color, startPoint));
}

int ChessBoard::nextGridId()
{
    return grids.size() + 1;
}

ChessBoardGrid* ChessBoard::getFreeAirplaneField(int color)
{
    ChessBoardGrid* toLand = 0;
    vector<ChessBoardGrid*> &planeField = airplaneFields.at(color);
    for (unsigned i = 0; i < planeField.size(); i++)
    {
        ChessBoardGrid* temp = planeField.at(i);
        bool isUsed = false;

        for (unsigned j = 0; j < planes.size(); j++)
        {
            Airplane* tempPlane = planes.at(j);
            if (tempPlane->position == temp)
            {
                isUsed = true;
                break;
            }
        }

        if (!isUsed)
        {
            toLand = temp;
            break;
        }
    }

    return toLand;
}

ChessBoardGrid* ChessBoard::getStartPointGrid(int color)
{
    return this->startPoints.at(color);
}

ChessBoardGrid* ChessBoard::getJumpDest(Airplane *plane, ChessBoardGrid* fromPos)
{
    ChessBoardGrid* result = fromPos;
    // 先从大跳的映射里面找
    map<ChessBoardGrid*, ChessBoardGrid*>::iterator it = longJumpMaps.find(result);
    if (it != longJumpMaps.end())
    {
        return (*it).second;
    }

    // 没找到，那就查找下一个颜色相同的
    while (true)
    {
        result = result->next;
        if (result->color == plane->color)
        {
            return result;
        }
    }

    return 0;
}

vector<MoveAction*>* ChessBoard::genFlightPlan(Airplane* p, int point)
{
    vector<MoveAction*>* flightPlan = new vector<MoveAction*>();

    int direction = p->direction;
    ChessBoardGrid* pre = p->position;

    while (point > 0)
    {
        ChessBoardGrid* next;

        if (pre->type == CHESS_BOARD_GRID_TYPE_END)
        {
            direction = DIRECT_BACK;
        }

        if (direction == DIRECT_FORWARD)
        {
            next = getNextGrid(p, pre);
        }
        else
        {
            next = getPreGrid(p, pre);
        }

        MoveAction* ma = new MoveAction(PLAN_ACTION_MOVE, pre, next);
        flightPlan->push_back(ma);

        pre = next;
        point--;
    }

    if (pre->autoJump && pre->color == p->color)
    {
        int actionType;
        if (longJumpMaps.find(pre) != longJumpMaps.end())
        {
            actionType = PLAN_ACTION_LONG_JUMP;
        }
        else
        {
            actionType = PLAN_ACTION_JUMP;
        }

        ChessBoardGrid* next = getJumpDest(p, pre);
        MoveAction* ma = new MoveAction(actionType, pre, next);
        flightPlan->push_back(ma);
    }

    return flightPlan;
}

Airplane* ChessBoard::checkIfFight(Airplane* p, MoveAction* ma)
{
    Airplane* old = getOverlapPlane(p, ma->to);
    if (old == 0)
    {
        return 0;
    }

    if (old->color != p->color)
    {
        // 颜色不一样，那开打吧
        return old;
    }

    map<ChessBoardGrid*, ChessBoardGrid*>::iterator rsIt = longJumpMaps.find(ma->from);
    if (rsIt == longJumpMaps.end() || (*rsIt).second != ma->to)
    {
        return 0;
    }

    ChessBoardGrid* fightGrid = longJumpFightMaps.at(ma->from);
    FOREACH_PLANES(planes)
    {
        Airplane* temp = *it;
        if (temp->position == fightGrid)
        {
            return temp;
        }
    }

    return 0;
}

Airplane* ChessBoard::getOverlapPlane(Airplane* p, ChessBoardGrid* pos)
{
    p = p->getLeader();

    vector<Airplane*>::iterator it = planes.begin();

    FOREACH_PLANES(planes)
    {
        Airplane* temp = *it;
        if (temp->isLeader() && temp != p
            && temp->position == pos)
        {
            return temp;
        }
    }

    return 0;
}
