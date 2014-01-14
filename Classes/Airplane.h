#ifndef __AIR_PLANE__
#define __AIR_PLANE__

#include <vector>

#include "cocos2d.h"
#include "ChessBoardGrid.h"

using namespace std;
USING_NS_CC;

class Airplane : public CCNode, public CCTargetedTouchDelegate
{
private:
    bool containsTouchLocation(CCTouch* touch);
    
    // �����ƶ���һ��������
    void moveTo(ChessBoardGrid* grid, SEL_CallFunc callbackFunc);
    bool isCanJump();
    void move();
    void normalMoveCallback();
    void jump(ChessBoardGrid *position);
    void jumpedCallback();
    void readyCallback();
    void changePosition(ChessBoardGrid* p);

    bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    void ccTouchEnded(CCTouch* touch, CCEvent* event);

public:
    int remainStep;
    ChessBoardGrid *lastPosition;
    ChessBoardGrid *position;
    int color;
    // �ƶ���������ǰ�������
    int direction;
    int state;

    Airplane(int color);
    ~Airplane(void);

    Airplane *leader;
    vector<Airplane*> members;
    
    // �ƶ�ָ���ĵ���
    void moveByStep(int step);
    void teamMoveByStep(int step);

    // ֱ���ƶ���һ��������
    void moveToNow(ChessBoardGrid* grid);

    // ׼�����
    void ready();
    // �������
    void complete();
    // �ؼң�������
    void returnHome();

    // С�Ӷ��ؼ�
    void teamReturnHome();
    // ���
    void fight(Airplane* dest);

    bool isLeader();
    Airplane* getLeader();
    vector<Airplane*>* getTeamMembers();
    void joinATeam(Airplane* memberInTeamToJoin);
    void leaveTeam();

    bool isMyTurn();

    bool canMove();
};

#endif