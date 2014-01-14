#ifndef __ENVIROMENT__
#define __ENVIROMENT__

#include "ChessBoard.h"
#include "ChessBoardScene.h"

class Enviroment
{
private:
    Enviroment(void);

    static Enviroment* m_INSTANCE;

    bool currentPlayerHasFlyingPlane();
public:

    static Enviroment* getInstance();

    // 轮到下一个颜色
    void turnNext();

    // 玩家数量
    int playerNum;
    // 出场的玩家
    CircularLinkedList<int> players;
    // 哪些是AI
    map<int, bool> AIMap;

    // 目前是哪个颜色的回合
    int currentColor;

    // 棋盘状态
    int state;

    // 投的点数
    int currentPoint;
    // 当前正在玩的棋盘
    ChessBoard* currentChessBoard;

    ChessBoardScene* mainScene;

    // 是否可以控制
    bool isCanControl;

    // 当前玩家是否能够移动任何飞机
    bool canMoveAnyPlane();

    // 当前玩家是否是AI
    bool isCurrentPlayerAI();
};

#endif
