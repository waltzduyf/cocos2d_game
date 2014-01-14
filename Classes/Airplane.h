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
    
    // 慢慢移动到一个格子上
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
    // 移动方向，是向前还是向后
    int direction;
    int state;

    Airplane(int color);
    ~Airplane(void);

    Airplane *leader;
    vector<Airplane*> members;
    
    // 移动指定的点数
    void moveByStep(int step);
    void teamMoveByStep(int step);

    // 直接移动到一个格子上
    void moveToNow(ChessBoardGrid* grid);

    // 准备起飞
    void ready();
    // 完成任务
    void complete();
    // 回家，重新来
    void returnHome();

    // 小队都回家
    void teamReturnHome();
    // 打架
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