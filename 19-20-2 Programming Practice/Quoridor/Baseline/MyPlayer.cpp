#include "MyPlayer.h"

#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


namespace QuoridorUtils {

	/*
	 * Step MyPlayer::nextStep(const ChessboardChange& newChange)
	 *
	 * newChange 为修改的棋局, 其格式为
	 * (GameStatus status, Location enemyLoc, Location myLoc, BlockBar newEnemyBlockBar)
	 * 其中棋子坐标和挡板坐标见下图, 当对手没有添加新的挡板时,
	 * newChange.newEnemyBlockBar.isNan()为true
	 *
	 * 需要返回的数据Step为
	 * (Location myNewLoc, BlockBar myNewBlockBar)
	 * 仅能选择让移动棋子一步（前后左右四个方向）或者放一个挡板:
	 * 当移动棋子时, step.myNewBlockBar.isNan()为true;
	 * 当放置挡板时, step.myNewLoc为newChange中的myLoc
	 *
	 * 所有错误(挡板位置错误, 挡板已用完, 移动位置错误, 同时移动并放置挡板, 超时等)均由服务器检测,
	 * 可能需要在自行实现错误避免功能.
	 *
	 *  棋子坐标如下:                 挡板坐标结构如下：
	 *  ┌-┬-┬-┬-┬-┬-┬-┬-┬-┐          ┌-┬-┬-┬-┬-┬-┬-┬-┬-┐9
	 *  ├-┼-┼-┼-┼-┼-┼-┼-┼-┤↖9       ├-┼-┼-┼-┼-┼-┼-┼-┼-┤8
	 *  ├-┼-┼-┼-┼-┼-┼-┼-┼-┤↖8       ├-┼-┼-┼-┼-┼-┼-┼-┼-┤7
	 *  ├-┼-┼-┼-┼-┼-┼-┼-┼-┤↖7       ├-┼-┼-┼-┼-┼-┼-┼-┼-┤6
	 *  ├-┼-┼-┼-┼-┼-┼-┼-┼-┤↖6       ├-┼-┼-┼-┼-┼-┼-┼-┼-┤5
	 *  ├-┼-┼-┼-┼-┼-┼-┼-┼-┤↖5       ├-┼-┼-┼-┼-┼-┼-┼-┼-┤4
	 *  ├-┼-┼-┼-┼-┼-┼-┼-┼-┤↖4       ├-┼-┼-┼-┼-┼-┼-┼-┼-┤3
	 *  ├-┼-┼-┼-┼-┼-┼-┼-┼-┤↖3       ├-┼-┼-┼-┼-┼-┼-┼-┼-┤2
	 *  ├-┼-┼-┼-┼-┼-┼-┼-┼-┤↖2       ├-┼-┼-┼-┼-┼-┼-┼-┼-┤1
	 *  └-┴-┴-┴-┴-┴-┴-┴-┴-┘↖1 y     └-┴-┴-┴-┴-┴-┴-┴-┴-┘0 y
	 * x 1 2 3 4 5 6 7 8 9        x 0 1 2 3 4 5 6 7 8 9
	 *
	 */

	 // 面向对象实现开始
	Location MyPlayer::randomWalk(const Location& myLoc, const Location& enemyLoc) {
		bool directions[4];
		directions[0] = myLoc.y < SIZE;                          // 是否可以向上走 
		directions[1] = myLoc.y > 1;                             // 是否可以向下走 
		directions[2] = myLoc.x > 1;                             // 是否可以向左走 
		directions[3] = myLoc.x < SIZE;                          // 是否可以向右走 
		for (auto block : this->blocks) {                        // 遍历挡板列表, 找到被阻挡的方向 
			if (block.isH()) {                                   // 水平方向挡板, start 与 stop 的 y 相等 
				if (block.start.x == myLoc.x - 1 ||
					block.start.x == myLoc.x - 2) {              // 可能挡路的挡板 
					if (block.start.y == myLoc.y) {
						directions[0] = false;
					}
					else if (block.start.y == myLoc.y - 1) {
						directions[1] = false;
					}
				}
			}
			if (block.isV()) {                                   // 竖直方向挡板, start 与 stop 的 x 相等 
				if (block.start.y == myLoc.y - 1 ||
					block.start.y == myLoc.y - 2) {              // 可能挡路的挡板 
					if (block.start.x == myLoc.x) {
						directions[3] = false;
					}
					else if (block.start.x == myLoc.x - 1) {
						directions[2] = false;
					}
				}
			}
		}
		int optionsCount = int(directions[0]) + int(directions[1]) +
			int(directions[2]) + int(directions[3]);    // 规则中不能堵死棋子, 必定大于等于1 
		int tmp = rand() % optionsCount;                               // 随机一个 [0, optionsCount - 1] 的整数
		int directionIndex;                                            // 找出随机方向的下标 
		for (directionIndex = 0; directionIndex < 4; directionIndex++) {
			if (directions[directionIndex]) {
				if (tmp <= 0) {
					break;
				}
				tmp--;
			}
		}
		Location nextLoc = myLoc;
		switch (directionIndex) {
		case 0:   // 向上走
			nextLoc.y++;
			break;
		case 1:   // 向下走
			nextLoc.y--;
			break;
		case 2:   // 向左走
			nextLoc.x--;
			break;
		case 3:   // 向右走
			nextLoc.x++;
			break;
		default:;
		}
		if (nextLoc.distance(enemyLoc) == 0) {                   // 下一步是敌军位置则应跳过敌军棋子
			nextLoc.x = -1;                                      // 此处不做实现, 默认下一步空操作
			nextLoc.y = -1;
		}
		return nextLoc;
	}

	//若只差最后一步即可到达底线，则直接行动，不做其他考虑
	Location MyPlayer::One_Step(const Location& myLoc) {

		Location tmp;
		tmp.x = -1;
		tmp.y = -1;
		if (myLoc.y + 1 == targetY && Walkable[myLoc.y - 1][myLoc.x - 1][0] == 0) {
			tmp.x = myLoc.x;
			tmp.y = myLoc.y + 1;

		}
		else if (myLoc.y - 1 == targetY && Walkable[myLoc.y - 1][myLoc.x - 1][2] == 0) {
			tmp.x = myLoc.x;
			tmp.y = myLoc.y - 1;
		}
		return tmp;

	}

	//所有数组的顺序[0][1][2][3]均为上、右、下、左

	vector<Location> MyPlayer::Find_Way(const Location& curLoc, const int targetLocY) {//用BFS算法寻找最短路径
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				tag[i][j] = -1;
			}
		}
		My_Move = 0;
		e_Move = 0;
		vector<Location>tmp_Way;
		tmp_Way.clear();
		tmp_Way.push_back(curLoc);
		tag[curLoc.y - 1][curLoc.x - 1] = 0;
		int i = 0;
		for (; i < tmp_Way.size(); i++) {

			Location cur = tmp_Way[i];
			//判断各个方向是否可以走，若可以，则将该点存入vector容器，并将tag设为上一层的tag+1
			if (Walkable[cur.y - 1][cur.x - 1][0] == 0) {
				int x = cur.x, y = cur.y + 1;
				Location tmp;
				tmp.x = x, tmp.y = y;
				if (tag[tmp.y - 1][tmp.x - 1] == -1) {
					tmp_Way.push_back(tmp);

					tag[y - 1][x - 1] = tag[cur.y - 1][cur.x - 1] + 1;
					if (tmp.y == targetLocY) {//若这一次寻路已到达底线，则停止寻路，这即为最短路线的终点
						break;
					}
				}
			}
			if (Walkable[cur.y - 1][cur.x - 1][1] == 0) {
				int x = cur.x + 1, y = cur.y;
				Location tmp;
				tmp.x = x, tmp.y = y;
				if (tag[tmp.y - 1][tmp.x - 1] == -1) {
					tmp_Way.push_back(tmp);

					tag[y - 1][x - 1] = tag[cur.y - 1][cur.x - 1] + 1;
					if (tmp.y == targetLocY) {//若这一次寻路已到达底线，则停止寻路，这即为最短路线的终点
						break;
					}
				}
			}
			if (Walkable[cur.y - 1][cur.x - 1][2] == 0) {
				int x = cur.x, y = cur.y - 1;
				Location tmp;
				tmp.x = x, tmp.y = y;
				if (tag[tmp.y - 1][tmp.x - 1] == -1) {
					tmp_Way.push_back(tmp);

					tag[y - 1][x - 1] = tag[cur.y - 1][cur.x - 1] + 1;
					if (tmp.y == targetLocY) {//若这一次寻路已到达底线，则停止寻路，这即为最短路线的终点
						break;
					}
				}
			}
			if (Walkable[cur.y - 1][cur.x - 1][3] == 0) {
				int x = cur.x - 1, y = cur.y;
				Location tmp;
				tmp.x = x, tmp.y = y;
				if (tag[tmp.y - 1][tmp.x - 1] == -1) {
					tmp_Way.push_back(tmp);

					tag[y - 1][x - 1] = tag[cur.y - 1][cur.x - 1] + 1;
					if (tmp.y == targetLocY) {//若这一次寻路已到达底线，则停止寻路，这即为最短路线的终点
						break;
					}
				}
			}
		}
		if (i == tmp_Way.size()) {
			if (targetLocY == targetY) {
				My_Move = -1;
				tmp_Way.clear();
			}
			else {
				e_Move = -1;
				tmp_Way.clear();
			}
			return tmp_Way;
		}


		int tag_tmp = tag[tmp_Way.back().y - 1][tmp_Way.back().x - 1];//储存终点位置的tag值
		Location flag = tmp_Way.back();//储存终点的坐标
		for (int i = tmp_Way.size() - 1; i--; i >= 0) {
			Location tmp = tmp_Way[i];
			if (tag[tmp.y - 1][tmp.x - 1] >= tag_tmp) {//当访问的点tag值大于等于当前目标的tag值时，舍去
				tmp_Way.erase(tmp_Way.begin() + i, tmp_Way.begin() + 1 + i);
			}
			//当访问的点tag值等于当前目标的tag值-1时
			if (tag[tmp.y - 1][tmp.x - 1] == tag_tmp - 1 && tag[tmp.y - 1][tmp.x - 1] > 0) {
				//当该点在目标点的上下左右相邻位置时，留下该点，将目标点和目标tag值均修改为该点的数值
				if ((tmp.y == flag.y && (tmp.x - flag.x == 1 || tmp.x - flag.x == -1)) || (tmp.x == flag.x && (tmp.y - flag.y == 1 || tmp.y - flag.y == -1))) {
					
					/*此处有bug，由于相邻两格且tag相差1中间可能会有隔板
					如
					
					 0 1
					 1|2
					  |

					*/
					//bug已修复

					if (tmp.y == flag.y && tmp.x - flag.x == 1) {
						if (Walkable[tmp.y - 1][tmp.x - 1][3] == 0) {
							flag = tmp;
							tag_tmp--;
						}
						else {
							tmp_Way.erase(tmp_Way.begin() + i, tmp_Way.begin() + 1 + i);
						}
					}

					if (tmp.y == flag.y && tmp.x - flag.x == -1) {
						if (Walkable[tmp.y - 1][tmp.x - 1][1] == 0) {
							flag = tmp;
							tag_tmp--;
						}
						else {
							tmp_Way.erase(tmp_Way.begin() + i, tmp_Way.begin() + 1 + i);
						}
					}

					if (tmp.x == flag.x && tmp.y - flag.y == 1) {
						if (Walkable[tmp.y - 1][tmp.x - 1][2] == 0) {
							flag = tmp;
							tag_tmp--;
						}
						else {
							tmp_Way.erase(tmp_Way.begin() + i, tmp_Way.begin() + 1 + i);
						}
					}

					if (tmp.x == flag.x && tmp.y - flag.y == -1) {
						if (Walkable[tmp.y - 1][tmp.x - 1][0] == 0) {
							flag = tmp;
							tag_tmp--;
						}
						else {
							tmp_Way.erase(tmp_Way.begin() + i, tmp_Way.begin() + 1 + i);
						}
					}

					
				}
				//否则，舍去该点
				else {
					tmp_Way.erase(tmp_Way.begin() + i, tmp_Way.begin() + 1 + i);
				}
			}
			//当tag值等于0时，跳出循环
			if (tag[tmp.y - 1][tmp.x - 1] == 0) {
				break;
			}
		}

		return tmp_Way;
	}

	//判断欲放置的木板是否与已有木板矛盾
	bool MyPlayer::Judge_Blocks(BlockBar block) {
		for (int i = 0; i < blocks.size(); i++) {
			if (block.isH() && blocks[i].isH()) {
				if (block.start.y == blocks[i].start.y) {
					if (block.start.x - blocks[i].start.x <= 1 && block.start.x - blocks[i].start.x >= -1) {
						return false;
					}
				}
			}
			if (block.isV() && blocks[i].isV()) {
				if (block.start.x == blocks[i].start.x) {
					if (block.start.y - blocks[i].start.y <= 1 && block.start.y - blocks[i].start.y >= -1) {
						return false;
					}
				}
			}

		}
		return true;
	}

	Step MyPlayer::Next_To(Step cur_step, Location enemyLoc, Location myLoc) {


		startgame = 1;
		if (enemyLoc.x == myLoc.x) {//如果和敌方棋子纵向相邻
			if (targetY == 9 && enemyLoc.y - myLoc.y == 1) {
				if (Walkable[enemyLoc.y - 1][enemyLoc.x - 1][0] == 0) {//如果可以跨越
					cur_step.myNewLoc.y++;

					std::cout << " -> " << cur_step << std::endl;                // 输出我的决策到控制台显示 
					startgame = 1;
					return cur_step;
				}

			}
			if (targetY == 1 && enemyLoc.y - myLoc.y == -1) {
				if (Walkable[enemyLoc.y - 1][enemyLoc.x - 1][2] == 0) {//如果可以跨越
					cur_step.myNewLoc.y--;
					std::cout << " -> " << cur_step << std::endl;                // 输出我的决策到控制台显示 
					startgame = 1;
					return cur_step;
				}
			}
		}

		else if (enemyLoc.y == myLoc.y) {//如果和敌方棋子横向相邻
			if (enemyLoc.x - myLoc.x == 1) {
				if (my_Way.size() > 2) {
					if (my_Way[2] == (enemyLoc.x + 1, enemyLoc.y)) {
						cur_step.myNewLoc = (enemyLoc.x + 1, enemyLoc.y);
						std::cout << " -> " << cur_step << std::endl;                // 输出我的决策到控制台显示 
						startgame = 1;
						my_Way.erase(my_Way.begin(), my_Way.begin() + 1);
						return cur_step;
					}
				}
			}
			if (enemyLoc.x - myLoc.x == -1) {
				if (my_Way.size() > 2) {
					if (my_Way[2] == (enemyLoc.x - 2, enemyLoc.y)) {
						cur_step.myNewLoc = (enemyLoc.x - 2, enemyLoc.y);
						std::cout << " -> " << cur_step << std::endl;                // 输出我的决策到控制台显示 
						startgame = 1;
						my_Way.erase(my_Way.begin(), my_Way.begin() + 1);
						return cur_step;
					}
				}
			}
		}

		if (Walkable[myLoc.y - 1][myLoc.x - 1][1] == 0) {
			cur_step.myNewLoc.x = myLoc.x + 1;
			cur_step.myNewLoc.y = myLoc.y;
			if (!(cur_step.myNewLoc == enemyLoc)) {
				std::cout << " -> " << cur_step << std::endl;                // 输出我的决策到控制台显示 
				startgame = 1;
				return cur_step;
			}
		}
		else if (Walkable[myLoc.y - 1][myLoc.x - 1][3] == 0) {
			cur_step.myNewLoc.x = myLoc.x - 1;
			cur_step.myNewLoc.y = myLoc.y;
			if (!(cur_step.myNewLoc == enemyLoc)) {
				std::cout << " -> " << cur_step << std::endl;                // 输出我的决策到控制台显示 
				startgame = 1;
				return cur_step;
			}
		}
		else if (Walkable[myLoc.y - 1][myLoc.x - 1][2] == 0) {
			cur_step.myNewLoc.x = myLoc.x;
			cur_step.myNewLoc.y = myLoc.y - 1;
			if (!(cur_step.myNewLoc == enemyLoc)) {
				std::cout << " -> " << cur_step << std::endl;                // 输出我的决策到控制台显示 
				startgame = 1;
				return cur_step;
			}
		}
		else if (Walkable[myLoc.y - 1][myLoc.x - 1][0] == 0) {
			cur_step.myNewLoc.x = myLoc.x;
			cur_step.myNewLoc.y = myLoc.y + 1;
			if (!(cur_step.myNewLoc == enemyLoc)) {
				std::cout << " -> " << cur_step << std::endl;                // 输出我的决策到控制台显示 
				startgame = 1;
				return cur_step;
			}
		}

		cur_step.myNewLoc = (-1, -1);
		return cur_step;

	}



	BlockBar MyPlayer::new_BlockBar(Location myLoc, Location enemyLoc) {
		vector<BlockBar>block;
		vector<int>bias;
		
		if (count_board < 9) {
			for (int i = 0; i < 8; i++) {
				for (int j = 1; j < 9; j++) {
					BlockBar tmp;
					tmp.start.x = i;
					tmp.start.y = j;
					tmp.stop.x = i + 2;
					tmp.stop.y = j;
					if (Judge_Blocks(tmp)) {
						Walkable[tmp.start.y - 1][tmp.start.x][0] = -1;
						Walkable[tmp.start.y - 1][tmp.start.x + 1][0] = -1;
						Walkable[tmp.start.y][tmp.start.x][2] = -1;
						Walkable[tmp.start.y][tmp.start.x + 1][2] = -1;
						int my = Find_Way(myLoc, targetY).size(), e = Find_Way(enemyLoc, e_targetY).size();
						int my_bias = my - my_Way.size();
						int e_bias = e - e_Way.size();
						if (my == 0 || e == 0 || e_bias - my_bias <= 0) {
							Walkable[tmp.start.y - 1][tmp.start.x][0] = 0;
							Walkable[tmp.start.y - 1][tmp.start.x + 1][0] = 0;
							Walkable[tmp.start.y][tmp.start.x][2] = 0;
							Walkable[tmp.start.y][tmp.start.x + 1][2] = 0;
							continue;
						}
						else {
							int tmp_bias = e_bias - my_bias;
							block.push_back(tmp);
							bias.push_back(tmp_bias);
							Walkable[tmp.start.y - 1][tmp.start.x][0] = 0;
							Walkable[tmp.start.y - 1][tmp.start.x + 1][0] = 0;
							Walkable[tmp.start.y][tmp.start.x][2] = 0;
							Walkable[tmp.start.y][tmp.start.x + 1][2] = 0;
						}
					}
				}
			}
			for (int i = 1; i < 9; i++) {
				for (int j = 0; j < 8; j++) {
					BlockBar tmp;
					tmp.start.x = i;
					tmp.start.y = j;
					tmp.stop.x = i;
					tmp.stop.y = j + 2;
					if (Judge_Blocks(tmp)) {
						Walkable[tmp.start.y][tmp.start.x - 1][1] = -1;
						Walkable[tmp.start.y + 1][tmp.start.x - 1][1] = -1;
						Walkable[tmp.start.y][tmp.start.x][3] = -1;
						Walkable[tmp.start.y + 1][tmp.start.x][3] = -1;
						int my = Find_Way(myLoc, targetY).size(), e = Find_Way(enemyLoc, e_targetY).size();
						int my_bias = my - my_Way.size();
						int e_bias = e - e_Way.size();
						if (my == 0 || e == 0 || e_bias - my_bias <= 0) {
							Walkable[tmp.start.y][tmp.start.x - 1][1] = 0;
							Walkable[tmp.start.y + 1][tmp.start.x - 1][1] = 0;
							Walkable[tmp.start.y][tmp.start.x][3] = 0;
							Walkable[tmp.start.y + 1][tmp.start.x][3] = 0;
							continue;
						}
						else {
							int tmp_bias = e_bias - my_bias;
							block.push_back(tmp);
							bias.push_back(tmp_bias);
							Walkable[tmp.start.y][tmp.start.x - 1][1] = 0;
							Walkable[tmp.start.y + 1][tmp.start.x - 1][1] = 0;
							Walkable[tmp.start.y][tmp.start.x][3] = 0;
							Walkable[tmp.start.y + 1][tmp.start.x][3] = 0;
						}
					}
				}
			}
			int max = 0;
			//int no;
			BlockBar ans;
			for (int i = 0; i < block.size(); i++) {
				if (bias[i] > max) {
					ans = block[i];
					max = bias[i];
				}
			}
			if (max == 0) {
				BlockBar new_bar;
				return new_bar;
			}
			else {
				return ans;
			}
		}
		else {
			BlockBar ans;
			return ans;
		}
	}



	Step MyPlayer::nextStep(const ChessboardChange& newChange) {
		My_Move = 0;                                                         //是否有获胜路径
		e_Move = 0;
		Step step;                                               // 初始化 step 默认不移动不放板 
		e_Way.clear();                                           //清空上一次的敌方路径，便于重新计算

		if (this->targetY == 0) {                                // 判断并记录自己的目标 
			const auto d = std::chrono::system_clock::now().time_since_epoch();
			const int nanosecond = (std::chrono::nanoseconds(d).count() / 100) % int64_t(INT32_MAX);
			srand(nanosecond);
			if (newChange.myLoc == PLAYER0_LOC) {                // 己方初始坐标为 (5,1) 则目标为 (x,9) 
				this->targetY = PLAYER1_LOC.y;
				this->e_targetY = PLAYER0_LOC.y;
			}
			else {                                             // 己方初始坐标为 (5,9) 则目标为 (x,1) 
				this->targetY = PLAYER0_LOC.y;
				this->e_targetY = PLAYER1_LOC.y;
			}
		}
		std::cout << newChange;                                  // 输出接收到的数据到控制台显示 



		if (!newChange.newEnemyBlockBar.isNan()) {               // 对方放置了挡板 
			BlockBar tmp = newChange.newEnemyBlockBar;
			tmp.normalization();                                 // 规范为 start 坐标小于 stop 坐标的形式 
			this->blocks.push_back(tmp);                         // 存储规范挡板
			if (newChange.newEnemyBlockBar.isH()) {              // 判断挡板所阻挡的格子及方向并存储
				Walkable[tmp.start.y - 1][tmp.start.x][0] = -1;
				Walkable[tmp.start.y - 1][tmp.start.x + 1][0] = -1;
				Walkable[tmp.start.y][tmp.start.x][2] = -1;
				Walkable[tmp.start.y][tmp.start.x + 1][2] = -1;
			}
			else {
				Walkable[tmp.start.y][tmp.start.x - 1][1] = -1;
				Walkable[tmp.start.y + 1][tmp.start.x - 1][1] = -1;
				Walkable[tmp.start.y][tmp.start.x][3] = -1;
				Walkable[tmp.start.y + 1][tmp.start.x][3] = -1;
			}
		}

		if (One_Step(newChange.myLoc).x != -1 && One_Step(newChange.myLoc).y != -1) {//如果一步就可以获胜
			if (One_Step(newChange.myLoc) == newChange.enemyLoc) {//敌方棋子在我的下一步路径上
				if (Walkable[newChange.myLoc.y - 1][newChange.myLoc.x - 1][1] == 0) {
					if (targetY == 9 && Walkable[newChange.myLoc.y - 1][newChange.myLoc.x][0] == 0) {
						step.myNewLoc.x = newChange.myLoc.x + 1;
						step.myNewLoc.y = newChange.myLoc.y;
						std::cout << " -> " << step << std::endl;                // 输出我的决策到控制台显示 
						startgame = 0;
						return step;                                             //返回决策
					}
					if (targetY == 1 && Walkable[newChange.myLoc.y - 1][newChange.myLoc.x][2] == 0) {
						step.myNewLoc.x = newChange.myLoc.x + 1;
						step.myNewLoc.y = newChange.myLoc.y;
						std::cout << " -> " << step << std::endl;                // 输出我的决策到控制台显示 
						startgame = 0;
						return step;                                             //返回决策
					}
				}
				else if (Walkable[newChange.myLoc.y - 1][newChange.myLoc.x - 1][3] == 0) {

					step.myNewLoc.x = newChange.myLoc.x - 1;
					step.myNewLoc.y = newChange.myLoc.y;
					std::cout << " -> " << step << std::endl;                // 输出我的决策到控制台显示 
					startgame = 0;
					return step;                                             //返回决策

				}
				else {
					if (targetY == 9 && Walkable[newChange.myLoc.y - 1][newChange.myLoc.x][0] == 0) {
						step.myNewLoc.x = newChange.myLoc.x;
						step.myNewLoc.y = newChange.myLoc.y - 1;
						std::cout << " -> " << step << std::endl;                // 输出我的决策到控制台显示 
						startgame = 0;
						return step;                                             //返回决策
					}
					if (targetY == 1 && Walkable[newChange.myLoc.y - 1][newChange.myLoc.x][2] == 0) {
						step.myNewLoc.x = newChange.myLoc.x;
						step.myNewLoc.y = newChange.myLoc.y + 1;
						std::cout << " -> " << step << std::endl;                // 输出我的决策到控制台显示 
						startgame = 0;
						return step;                                             //返回决策
					}
				}

			}
			step.myNewLoc = One_Step(newChange.myLoc);
			std::cout << " -> " << step << std::endl;                // 输出我的决策到控制台显示 
			startgame = 0;
			return step;                                             //返回决策
		}


		if ((!newChange.newEnemyBlockBar.isNan() || startgame == 1)) {
			startgame = 0;
			my_Way.clear();
			my_Way = Find_Way(newChange.myLoc, targetY);
		}


		e_Way = Find_Way(newChange.enemyLoc, e_targetY);

		//UNDONE
		if (my_Way.size() > 1 && my_Way.size() <= e_Way.size()) {
			my_Way.erase(my_Way.begin(), my_Way.begin() + 1);
			step.myNewLoc = my_Way.front();

		}

		//慢时则考虑放置木板
		else if (Find_Way(newChange.enemyLoc, e_targetY).size() > 2 )
		{
			BlockBar tmp;
			step.myNewLoc.x = -1;
			step.myNewLoc.y = -1;
			startgame = 1;
			tmp = new_BlockBar(newChange.myLoc, newChange.enemyLoc);
			if (!tmp.isNan()) {
				step.myNewBlockBar = tmp;
				blocks.push_back(tmp);
				count_board++;
				if (tmp.isH()) {              // 判断挡板所阻挡的格子及方向并存储
					Walkable[tmp.start.y - 1][tmp.start.x][0] = -1;
					Walkable[tmp.start.y - 1][tmp.start.x + 1][0] = -1;
					Walkable[tmp.start.y][tmp.start.x][2] = -1;
					Walkable[tmp.start.y][tmp.start.x + 1][2] = -1;
				}
				else {
					Walkable[tmp.start.y][tmp.start.x - 1][1] = -1;
					Walkable[tmp.start.y + 1][tmp.start.x - 1][1] = -1;
					Walkable[tmp.start.y][tmp.start.x][3] = -1;
					Walkable[tmp.start.y + 1][tmp.start.x][3] = -1;
				}
				std::cout << " -> " << step << std::endl;                // 输出我的决策到控制台显示 

				return step;
			}
			else {
				my_Way.clear();
				my_Way = Find_Way(newChange.myLoc, targetY);
				if (My_Move == 0) {
					my_Way.erase(my_Way.begin(), my_Way.begin() + 1);
					step.myNewLoc = my_Way.front();

				}
				else {
					step.myNewLoc = randomWalk(newChange.myLoc, newChange.enemyLoc);
				}
			}


		}

		//当敌方距离底线只有一步时
		else {
			if (e_targetY == 9 && count_board < 9) {
				BlockBar tmp;
				tmp.start.x = newChange.enemyLoc.x - 1;
				tmp.start.y = newChange.enemyLoc.y;
				tmp.stop.x = newChange.enemyLoc.x + 1;
				tmp.stop.y = newChange.enemyLoc.y;

				if (Judge_Blocks(tmp)) {
					step.myNewBlockBar = tmp;
					blocks.push_back(tmp);
					if (tmp.isH()) {              // 判断挡板所阻挡的格子及方向并存储
						Walkable[tmp.start.y - 1][tmp.start.x][0] = -1;
						Walkable[tmp.start.y - 1][tmp.start.x + 1][0] = -1;
						Walkable[tmp.start.y][tmp.start.x][2] = -1;
						Walkable[tmp.start.y][tmp.start.x + 1][2] = -1;
					}
					else {
						Walkable[tmp.start.y][tmp.start.x - 1][1] = -1;
						Walkable[tmp.start.y + 1][tmp.start.x - 1][1] = -1;
						Walkable[tmp.start.y][tmp.start.x][3] = -1;
						Walkable[tmp.start.y + 1][tmp.start.x][3] = -1;
					}
					count_board++;
					std::cout << " -> " << step << std::endl;                // 输出我的决策到控制台显示 

					return step;
				}
				tmp.start.x = newChange.enemyLoc.x - 2;
				tmp.start.y = newChange.enemyLoc.y;
				tmp.stop.x = newChange.enemyLoc.x;
				tmp.stop.y = newChange.enemyLoc.y;
				if (Judge_Blocks(tmp)) {
					step.myNewBlockBar = tmp;
					blocks.push_back(tmp);
					if (tmp.isH()) {              // 判断挡板所阻挡的格子及方向并存储
						Walkable[tmp.start.y - 1][tmp.start.x][0] = -1;
						Walkable[tmp.start.y - 1][tmp.start.x + 1][0] = -1;
						Walkable[tmp.start.y][tmp.start.x][2] = -1;
						Walkable[tmp.start.y][tmp.start.x + 1][2] = -1;
					}
					else {
						Walkable[tmp.start.y][tmp.start.x - 1][1] = -1;
						Walkable[tmp.start.y + 1][tmp.start.x - 1][1] = -1;
						Walkable[tmp.start.y][tmp.start.x][3] = -1;
						Walkable[tmp.start.y + 1][tmp.start.x][3] = -1;
					}
					count_board++;
					std::cout << " -> " << step << std::endl;                // 输出我的决策到控制台显示 

					return step;
				}
			}
			if (e_targetY == 1 && count_board < 9) {
				BlockBar tmp;
				tmp.start.x = newChange.enemyLoc.x - 1;
				tmp.start.y = newChange.enemyLoc.y - 1;
				tmp.stop.x = newChange.enemyLoc.x + 1;
				tmp.stop.y = newChange.enemyLoc.y - 1;

				if (Judge_Blocks(tmp)) {
					step.myNewBlockBar = tmp;
					blocks.push_back(tmp);
					if (tmp.isH()) {              // 判断挡板所阻挡的格子及方向并存储
						Walkable[tmp.start.y - 1][tmp.start.x][0] = -1;
						Walkable[tmp.start.y - 1][tmp.start.x + 1][0] = -1;
						Walkable[tmp.start.y][tmp.start.x][2] = -1;
						Walkable[tmp.start.y][tmp.start.x + 1][2] = -1;
					}
					else {
						Walkable[tmp.start.y][tmp.start.x - 1][1] = -1;
						Walkable[tmp.start.y + 1][tmp.start.x - 1][1] = -1;
						Walkable[tmp.start.y][tmp.start.x][3] = -1;
						Walkable[tmp.start.y + 1][tmp.start.x][3] = -1;
					}
					count_board++;
					std::cout << " -> " << step << std::endl;                // 输出我的决策到控制台显示 

					return step;
				}
				tmp.start.x = newChange.enemyLoc.x - 2;
				tmp.start.y = newChange.enemyLoc.y - 1;
				tmp.stop.x = newChange.enemyLoc.x;
				tmp.stop.y = newChange.enemyLoc.y - 1;
				if (Judge_Blocks(tmp)) {
					step.myNewBlockBar = tmp;
					blocks.push_back(tmp);
					if (tmp.isH()) {              // 判断挡板所阻挡的格子及方向并存储
						Walkable[tmp.start.y - 1][tmp.start.x][0] = -1;
						Walkable[tmp.start.y - 1][tmp.start.x + 1][0] = -1;
						Walkable[tmp.start.y][tmp.start.x][2] = -1;
						Walkable[tmp.start.y][tmp.start.x + 1][2] = -1;
					}
					else {
						Walkable[tmp.start.y][tmp.start.x - 1][1] = -1;
						Walkable[tmp.start.y + 1][tmp.start.x - 1][1] = -1;
						Walkable[tmp.start.y][tmp.start.x][3] = -1;
						Walkable[tmp.start.y + 1][tmp.start.x][3] = -1;
					}
					count_board++;
					std::cout << " -> " << step << std::endl;                // 输出我的决策到控制台显示 

					return step;
				}
			}


			my_Way.clear();
			my_Way = Find_Way(newChange.myLoc, targetY);
			if (My_Move == 0) {
				my_Way.erase(my_Way.begin(), my_Way.begin() + 1);
				step.myNewLoc = my_Way.front();

			}
			else {
				step.myNewLoc = randomWalk(newChange.myLoc, newChange.enemyLoc);
			}


		}

		if (step.myNewLoc == newChange.enemyLoc) {
			step = Next_To(step, newChange.enemyLoc, newChange.myLoc);

			//如果都不能走，则考虑放置挡板
			if(!step.isMove()){
				BlockBar tmp;
				step.myNewLoc.x = -1;
				step.myNewLoc.y = -1;
				startgame = 1;
				tmp = new_BlockBar(newChange.myLoc, newChange.enemyLoc);
				if (!tmp.isNan()) {
					blocks.push_back(tmp);
					step.myNewBlockBar = tmp;
					count_board++;
					if (tmp.isH()) {              // 判断挡板所阻挡的格子及方向并存储
						Walkable[tmp.start.y - 1][tmp.start.x][0] = -1;
						Walkable[tmp.start.y - 1][tmp.start.x + 1][0] = -1;
						Walkable[tmp.start.y][tmp.start.x][2] = -1;
						Walkable[tmp.start.y][tmp.start.x + 1][2] = -1;
					}
					else {
						Walkable[tmp.start.y][tmp.start.x - 1][1] = -1;
						Walkable[tmp.start.y + 1][tmp.start.x - 1][1] = -1;
						Walkable[tmp.start.y][tmp.start.x][3] = -1;
						Walkable[tmp.start.y + 1][tmp.start.x][3] = -1;
					}
					std::cout << " -> " << step << std::endl;                // 输出我的决策到控制台显示 

					return step;
				}
				else {

				}
			}
			else {
				std::cout << " -> " << step << std::endl;                // 输出我的决策到控制台显示 

				return step;
			}

		}

		//step.myNewLoc = randomWalk(newChange.myLoc, newChange.enemyLoc);
		

		if (!step.isMove() && !step.isNan()) {
			step.myNewLoc = randomWalk(newChange.myLoc, newChange.enemyLoc);
		}
		std::cout << " -> " << step << std::endl;                // 输出我的决策到控制台显示 

		return step;
	}

	void MyPlayer::restart() {//初始化

		this->blocks.clear();
		this->targetY = 0;
		this->e_targetY = 0;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				Walkable[i][j][0] = 0;
				Walkable[i][j][1] = 0;
				Walkable[i][j][2] = 0;
				Walkable[i][j][3] = 0;
				tag[i][j] = -1;

			}
		}

		for (int i = 0; i < 9; i++) {//初始化边界，避免运动时越界
			Walkable[0][i][2] = -1;
			Walkable[8][i][0] = -1;
			Walkable[i][0][3] = -1;
			Walkable[i][8][1] = -1;
		}
		startgame = 1;

		My_Move = 0;                                                         //是否有获胜路径
		e_Move = 0;
		count_board = 0;

		my_Way.clear();
		e_Way.clear();

	}
	// 面向对象实现结束

}

