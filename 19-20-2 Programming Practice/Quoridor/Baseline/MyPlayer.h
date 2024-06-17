#pragma once
#include <vector>

#include "Player.h"

namespace QuoridorUtils {
class MyPlayer final : public Player{
private:
    std::vector<BlockBar> blocks;                                           // �洢����
	int e_targetY = 0;
    int targetY = 0;                                                        // �洢Ŀ��λ��
    Location randomWalk(const Location& myLoc, const Location& enemyLoc);   // �������
	std::vector<Location> Find_Way(const Location& curLoc, const int targetLocY);//Ѱ·
	int Walkable[9][9][4];                                                  //�ж�ĳһ�������Ƿ����
	int tag[9][9] = { -1 };
	int startgame = 1;
	Location One_Step(const Location& myLoc);
	std::vector<Location> my_Way;
	std::vector<Location> e_Way;
	int My_Move = 0;                                                         //�Ƿ��л�ʤ·��
	int e_Move = 0;
	int count_board = 0;
	Step Next_To(Step cur_step, Location enmeyLoc, Location myLoc);
	BlockBar new_BlockBar(Location myLoc,Location enemyLoc);
	bool Judge_Blocks(BlockBar block);
public:
    MyPlayer(const std::string& key) : Player(key) {};            // �������, �����޸� 
    Step nextStep(const ChessboardChange& newChange) override;    // ��������ʵ�� 
    void restart() override;                                      // ��������ʵ�� 

};
}

// �������
//namespace QuoridorUtils {
//class MyPlayer final : public Player {
//public:
//    MyPlayer(const std::string& key) : Player(key) { };          // ������� 
//    Step nextStep(const ChessboardChange& newChange) override;   // ��������ʵ�� 
//    void restart() override;                                     // ��������ʵ�� 
//};
//}

/*
 *
 * ������������:                 ��������ṹ���£�
 * ��-��-��-��-��-��-��-��-��-��         ��-��-��-��-��-��-��-��-��-��9
 * ��-��-��-��-��-��-��-��-��-�ȨI9       ��-��-��-��-��-��-��-��-��-��8
 * ��-��-��-��-��-��-��-��-��-�ȨI8       ��-��-��-��-��-��-��-��-��-��7
 * ��-��-��-��-��-��-��-��-��-�ȨI7       ��-��-��-��-��-��-��-��-��-��6
 * ��-��-��-��-��-��-��-��-��-�ȨI6       ��-��-��-��-��-��-��-��-��-��5
 * ��-��-��-��-��-��-��-��-��-�ȨI5       ��-��-��-��-��-��-��-��-��-��4
 * ��-��-��-��-��-��-��-��-��-�ȨI4       ��-��-��-��-��-��-��-��-��-��3
 * ��-��-��-��-��-��-��-��-��-�ȨI3       ��-��-��-��-��-��-��-��-��-��2
 * ��-��-��-��-��-��-��-��-��-�ȨI2       ��-��-��-��-��-��-��-��-��-��1
 * ��-��-��-��-��-��-��-��-��-���I1 y     ��-��-��-��-��-��-��-��-��-��0 y
 *x 1 2 3 4 5 6 7 8 9         x0 1 2 3 4 5 6 7 8 9
 *
 *
 */