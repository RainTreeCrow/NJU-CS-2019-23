#pragma once
#include <vector>

#include "Player.h"

namespace QuoridorUtils {
class MyPlayer final : public Player{
private:
    std::vector<BlockBar> blocks;                                           // 存储挡板
	int e_targetY = 0;
    int targetY = 0;                                                        // 存储目标位置
    Location randomWalk(const Location& myLoc, const Location& enemyLoc);   // 随机游走
	std::vector<Location> Find_Way(const Location& curLoc, const int targetLocY);//寻路
	int Walkable[9][9][4];                                                  //判断某一个四周是否可走
	int tag[9][9] = { -1 };
	int startgame = 1;
	Location One_Step(const Location& myLoc);
	std::vector<Location> my_Way;
	std::vector<Location> e_Way;
	int My_Move = 0;                                                         //是否有获胜路径
	int e_Move = 0;
	int count_board = 0;
	Step Next_To(Step cur_step, Location enmeyLoc, Location myLoc);
	BlockBar new_BlockBar(Location myLoc,Location enemyLoc);
	bool Judge_Blocks(BlockBar block);
public:
    MyPlayer(const std::string& key) : Player(key) {};            // 必须存在, 请勿修改 
    Step nextStep(const ChessboardChange& newChange) override;    // 必须自行实现 
    void restart() override;                                      // 必须自行实现 

};
}

// 面向过程
//namespace QuoridorUtils {
//class MyPlayer final : public Player {
//public:
//    MyPlayer(const std::string& key) : Player(key) { };          // 必须存在 
//    Step nextStep(const ChessboardChange& newChange) override;   // 必须自行实现 
//    void restart() override;                                     // 必须自行实现 
//};
//}

/*
 *
 * 棋子坐标如下:                 挡板坐标结构如下：
 * ┌-┬-┬-┬-┬-┬-┬-┬-┬-┐         ┌-┬-┬-┬-┬-┬-┬-┬-┬-┐9
 * ├-┼-┼-┼-┼-┼-┼-┼-┼-┤↖9       ├-┼-┼-┼-┼-┼-┼-┼-┼-┤8
 * ├-┼-┼-┼-┼-┼-┼-┼-┼-┤↖8       ├-┼-┼-┼-┼-┼-┼-┼-┼-┤7
 * ├-┼-┼-┼-┼-┼-┼-┼-┼-┤↖7       ├-┼-┼-┼-┼-┼-┼-┼-┼-┤6
 * ├-┼-┼-┼-┼-┼-┼-┼-┼-┤↖6       ├-┼-┼-┼-┼-┼-┼-┼-┼-┤5
 * ├-┼-┼-┼-┼-┼-┼-┼-┼-┤↖5       ├-┼-┼-┼-┼-┼-┼-┼-┼-┤4
 * ├-┼-┼-┼-┼-┼-┼-┼-┼-┤↖4       ├-┼-┼-┼-┼-┼-┼-┼-┼-┤3
 * ├-┼-┼-┼-┼-┼-┼-┼-┼-┤↖3       ├-┼-┼-┼-┼-┼-┼-┼-┼-┤2
 * ├-┼-┼-┼-┼-┼-┼-┼-┼-┤↖2       ├-┼-┼-┼-┼-┼-┼-┼-┼-┤1
 * └-┴-┴-┴-┴-┴-┴-┴-┴-┘↖1 y     └-┴-┴-┴-┴-┴-┴-┴-┴-┘0 y
 *x 1 2 3 4 5 6 7 8 9         x0 1 2 3 4 5 6 7 8 9
 *
 *
 */