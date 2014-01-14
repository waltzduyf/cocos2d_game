#ifndef __CHESS_BOARD_GRID__
#define __CHESS_BOARD_GRID__

#include "PlaneChessConsts.h"
#include "cocos2d.h"

USING_NS_CC;

/************************************************************************/
/* 棋盘上的格子 */
/************************************************************************/
class ChessBoardGrid
{
public:
    int id;
    // 格子所在的位置
    CCPoint *position;
    // 格子的颜色
    int color;
    // 格子的类型
    int type;
    // 是否自动有跳跃动作
    bool autoJump;
    // 上一个格子
    ChessBoardGrid* pre;
    // 下一个格子
    ChessBoardGrid* next;

    ChessBoardGrid(int id, CCPoint* position, int type, int color);
    ~ChessBoardGrid(void);
};

#endif