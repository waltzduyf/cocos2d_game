#ifndef __CHESS_BOARD__
#define __CHESS_BOARD__

#include <vector>
#include <map>
#include <string>

#include "cocos2d.h"
#include "Airplane.h"
#include "ChessBoardGrid.h"
#include "CircularLinkedList.h"
#include "MoveAction.h"

USING_NS_CC;

using namespace std;

class ChessBoard : public CCNode
{
private:
    ChessBoard(void);
    ~ChessBoard(void);

    ChessBoardGrid* createGrid(CCPoint* pos, int color, int type);

    void setLastGridNotJump();
    int addEndGrids(int joinPoint, float dx, float dy, int step);
    void genCross(int from, int to, int color);
    int autoAddGrid(int joinPoint, float dx, float dy, CircularLinkedList<int>* colorOrder, int step);
    void genPlaneFields(int color, CCPoint *leftButton);
    void genLongJumpMaps(int from, int to);
    void genLongJumpFightMaps(int from, int fightGrid);
    void addStartPoint(int color, int joinPoint, float dx, float dy);

    void initPlaneColor(int color);

    int nextGridId();
public:
    // 飞机们
    vector<Airplane*> planes;
    // 格子，不包括飞机场
    map<int, ChessBoardGrid*> grids;
    // 十字路口
    map<ChessBoardGrid*, map<int, ChessBoardGrid*>*> crosses;
    // 飞机场
    map<int, vector<ChessBoardGrid*> > airplaneFields;
    // 每个颜色的起点，即等待点
    map<int, ChessBoardGrid*> startPoints;
    // 大跳的几个点
    map<ChessBoardGrid*, ChessBoardGrid*> longJumpMaps;
    // 大跳能打掉的几个格子映射
    map<ChessBoardGrid*, ChessBoardGrid*> longJumpFightMaps;

    // 获得前进的一步
    ChessBoardGrid* getNextGrid(Airplane *plane, ChessBoardGrid* fromPos);
    // 获得后退的一步
    ChessBoardGrid* getPreGrid(Airplane *plane, ChessBoardGrid* fromPos);
    // 获得跳跃的目的地
    ChessBoardGrid* getJumpDest(Airplane *plane, ChessBoardGrid* fromPos);
    // 获得空闲的飞机场格子
    ChessBoardGrid* getFreeAirplaneField(int color);
    // 获得准备起飞的格子
    ChessBoardGrid* getStartPointGrid(int color);

    // 使用配置文件创建一个对象
    static ChessBoard* createChessBoard(string* filePath);

    void initChess();
    void initPlanes();

    // 生成飞行计划
    vector<MoveAction*>* genFlightPlan(Airplane* p, int point);
    // 判断是否有架要打
    Airplane* checkIfFight(Airplane* p, MoveAction* ma);
    // 获得在这个格子上与他重叠的飞机
    Airplane* getOverlapPlane(Airplane* p, ChessBoardGrid* pos);
};

#endif
