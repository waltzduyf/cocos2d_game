#ifndef _CHESS_BOARD_GRID_CONSTS_

#define _CHESS_BOARD_GRID_CONSTS_

// 格子的类型
#define CHESS_BOARD_GRID_TYPE_NORMAL    1 // 普通格子
#define CHESS_BOARD_GRID_TYPE_AIRPORT   2 // 飞机场
//#define CHESS_BOARD_GRID_TYPE_JUMP      3 // 可跳跃的格子
//#define CHESS_BOARD_GRID_TYPE_CROSS     4 // 终点分叉口格子
#define CHESS_BOARD_GRID_TYPE_END       5 // 终点

// 颜色
#define FORCE_COLOR_NULL    0 // 无
#define FORCE_COLOR_RED     1 // 红
#define FORCE_COLOR_YELLOW  2 // 黄
#define FORCE_COLOR_GREEN   3 // 绿
#define FORCE_COLOR_BLUE    4 // 蓝

// 状态
#define STATE_WAITING   1 // 等待
#define STATE_READY     2 // 准备起飞
#define STATE_FLYING    3 // 正在飞
#define STATE_COMPLETE  4 // 完成

// 方向
#define DIRECT_FORWARD  0 // 向前
#define DIRECT_BACK     1 // 向后

// 棋盘状态
#define CHESS_BOARD_STATE_THROW 1 // 投骰子
#define CHESS_BOARD_STATE_MOVE  2 // 选择飞机移动

#define PLAN_ACTION_MOVE      1
#define PLAN_ACTION_JUMP      2
#define PLAN_ACTION_LONG_JUMP 3

#define FOREACH_PLANES(planes) for (vector<Airplane*>::iterator it = planes.begin(); it != planes.end(); it++)

#endif
