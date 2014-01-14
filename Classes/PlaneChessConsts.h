#ifndef _CHESS_BOARD_GRID_CONSTS_

#define _CHESS_BOARD_GRID_CONSTS_

// ���ӵ�����
#define CHESS_BOARD_GRID_TYPE_NORMAL    1 // ��ͨ����
#define CHESS_BOARD_GRID_TYPE_AIRPORT   2 // �ɻ���
//#define CHESS_BOARD_GRID_TYPE_JUMP      3 // ����Ծ�ĸ���
//#define CHESS_BOARD_GRID_TYPE_CROSS     4 // �յ�ֲ�ڸ���
#define CHESS_BOARD_GRID_TYPE_END       5 // �յ�

// ��ɫ
#define FORCE_COLOR_NULL    0 // ��
#define FORCE_COLOR_RED     1 // ��
#define FORCE_COLOR_YELLOW  2 // ��
#define FORCE_COLOR_GREEN   3 // ��
#define FORCE_COLOR_BLUE    4 // ��

// ״̬
#define STATE_WAITING   1 // �ȴ�
#define STATE_READY     2 // ׼�����
#define STATE_FLYING    3 // ���ڷ�
#define STATE_COMPLETE  4 // ���

// ����
#define DIRECT_FORWARD  0 // ��ǰ
#define DIRECT_BACK     1 // ���

// ����״̬
#define CHESS_BOARD_STATE_THROW 1 // Ͷ����
#define CHESS_BOARD_STATE_MOVE  2 // ѡ��ɻ��ƶ�

#define PLAN_ACTION_MOVE      1
#define PLAN_ACTION_JUMP      2
#define PLAN_ACTION_LONG_JUMP 3

#define FOREACH_PLANES(planes) for (vector<Airplane*>::iterator it = planes.begin(); it != planes.end(); it++)

#endif
