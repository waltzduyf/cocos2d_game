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
    // �ɻ���
    vector<Airplane*> planes;
    // ���ӣ��������ɻ���
    map<int, ChessBoardGrid*> grids;
    // ʮ��·��
    map<ChessBoardGrid*, map<int, ChessBoardGrid*>*> crosses;
    // �ɻ���
    map<int, vector<ChessBoardGrid*> > airplaneFields;
    // ÿ����ɫ����㣬���ȴ���
    map<int, ChessBoardGrid*> startPoints;
    // �����ļ�����
    map<ChessBoardGrid*, ChessBoardGrid*> longJumpMaps;
    // �����ܴ���ļ�������ӳ��
    map<ChessBoardGrid*, ChessBoardGrid*> longJumpFightMaps;

    // ���ǰ����һ��
    ChessBoardGrid* getNextGrid(Airplane *plane, ChessBoardGrid* fromPos);
    // ��ú��˵�һ��
    ChessBoardGrid* getPreGrid(Airplane *plane, ChessBoardGrid* fromPos);
    // �����Ծ��Ŀ�ĵ�
    ChessBoardGrid* getJumpDest(Airplane *plane, ChessBoardGrid* fromPos);
    // ��ÿ��еķɻ�������
    ChessBoardGrid* getFreeAirplaneField(int color);
    // ���׼����ɵĸ���
    ChessBoardGrid* getStartPointGrid(int color);

    // ʹ�������ļ�����һ������
    static ChessBoard* createChessBoard(string* filePath);

    void initChess();
    void initPlanes();

    // ���ɷ��мƻ�
    vector<MoveAction*>* genFlightPlan(Airplane* p, int point);
    // �ж��Ƿ��м�Ҫ��
    Airplane* checkIfFight(Airplane* p, MoveAction* ma);
    // �������������������ص��ķɻ�
    Airplane* getOverlapPlane(Airplane* p, ChessBoardGrid* pos);
};

#endif
