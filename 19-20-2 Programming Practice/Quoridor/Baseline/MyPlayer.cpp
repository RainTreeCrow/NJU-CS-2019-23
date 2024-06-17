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
	 * newChange Ϊ�޸ĵ����, ���ʽΪ
	 * (GameStatus status, Location enemyLoc, Location myLoc, BlockBar newEnemyBlockBar)
	 * ������������͵����������ͼ, ������û������µĵ���ʱ,
	 * newChange.newEnemyBlockBar.isNan()Ϊtrue
	 *
	 * ��Ҫ���ص�����StepΪ
	 * (Location myNewLoc, BlockBar myNewBlockBar)
	 * ����ѡ�����ƶ�����һ����ǰ�������ĸ����򣩻��߷�һ������:
	 * ���ƶ�����ʱ, step.myNewBlockBar.isNan()Ϊtrue;
	 * �����õ���ʱ, step.myNewLocΪnewChange�е�myLoc
	 *
	 * ���д���(����λ�ô���, ����������, �ƶ�λ�ô���, ͬʱ�ƶ������õ���, ��ʱ��)���ɷ��������,
	 * ������Ҫ������ʵ�ִ�����⹦��.
	 *
	 *  ������������:                 ��������ṹ���£�
	 *  ��-��-��-��-��-��-��-��-��-��          ��-��-��-��-��-��-��-��-��-��9
	 *  ��-��-��-��-��-��-��-��-��-�ȨI9       ��-��-��-��-��-��-��-��-��-��8
	 *  ��-��-��-��-��-��-��-��-��-�ȨI8       ��-��-��-��-��-��-��-��-��-��7
	 *  ��-��-��-��-��-��-��-��-��-�ȨI7       ��-��-��-��-��-��-��-��-��-��6
	 *  ��-��-��-��-��-��-��-��-��-�ȨI6       ��-��-��-��-��-��-��-��-��-��5
	 *  ��-��-��-��-��-��-��-��-��-�ȨI5       ��-��-��-��-��-��-��-��-��-��4
	 *  ��-��-��-��-��-��-��-��-��-�ȨI4       ��-��-��-��-��-��-��-��-��-��3
	 *  ��-��-��-��-��-��-��-��-��-�ȨI3       ��-��-��-��-��-��-��-��-��-��2
	 *  ��-��-��-��-��-��-��-��-��-�ȨI2       ��-��-��-��-��-��-��-��-��-��1
	 *  ��-��-��-��-��-��-��-��-��-���I1 y     ��-��-��-��-��-��-��-��-��-��0 y
	 * x 1 2 3 4 5 6 7 8 9        x 0 1 2 3 4 5 6 7 8 9
	 *
	 */

	 // �������ʵ�ֿ�ʼ
	Location MyPlayer::randomWalk(const Location& myLoc, const Location& enemyLoc) {
		bool directions[4];
		directions[0] = myLoc.y < SIZE;                          // �Ƿ���������� 
		directions[1] = myLoc.y > 1;                             // �Ƿ���������� 
		directions[2] = myLoc.x > 1;                             // �Ƿ���������� 
		directions[3] = myLoc.x < SIZE;                          // �Ƿ���������� 
		for (auto block : this->blocks) {                        // ���������б�, �ҵ����赲�ķ��� 
			if (block.isH()) {                                   // ˮƽ���򵲰�, start �� stop �� y ��� 
				if (block.start.x == myLoc.x - 1 ||
					block.start.x == myLoc.x - 2) {              // ���ܵ�·�ĵ��� 
					if (block.start.y == myLoc.y) {
						directions[0] = false;
					}
					else if (block.start.y == myLoc.y - 1) {
						directions[1] = false;
					}
				}
			}
			if (block.isV()) {                                   // ��ֱ���򵲰�, start �� stop �� x ��� 
				if (block.start.y == myLoc.y - 1 ||
					block.start.y == myLoc.y - 2) {              // ���ܵ�·�ĵ��� 
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
			int(directions[2]) + int(directions[3]);    // �����в��ܶ�������, �ض����ڵ���1 
		int tmp = rand() % optionsCount;                               // ���һ�� [0, optionsCount - 1] ������
		int directionIndex;                                            // �ҳ����������±� 
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
		case 0:   // ������
			nextLoc.y++;
			break;
		case 1:   // ������
			nextLoc.y--;
			break;
		case 2:   // ������
			nextLoc.x--;
			break;
		case 3:   // ������
			nextLoc.x++;
			break;
		default:;
		}
		if (nextLoc.distance(enemyLoc) == 0) {                   // ��һ���ǵо�λ����Ӧ�����о�����
			nextLoc.x = -1;                                      // �˴�����ʵ��, Ĭ����һ���ղ���
			nextLoc.y = -1;
		}
		return nextLoc;
	}

	//��ֻ�����һ�����ɵ�����ߣ���ֱ���ж���������������
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

	//���������˳��[0][1][2][3]��Ϊ�ϡ��ҡ��¡���

	vector<Location> MyPlayer::Find_Way(const Location& curLoc, const int targetLocY) {//��BFS�㷨Ѱ�����·��
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
			//�жϸ��������Ƿ�����ߣ������ԣ��򽫸õ����vector����������tag��Ϊ��һ���tag+1
			if (Walkable[cur.y - 1][cur.x - 1][0] == 0) {
				int x = cur.x, y = cur.y + 1;
				Location tmp;
				tmp.x = x, tmp.y = y;
				if (tag[tmp.y - 1][tmp.x - 1] == -1) {
					tmp_Way.push_back(tmp);

					tag[y - 1][x - 1] = tag[cur.y - 1][cur.x - 1] + 1;
					if (tmp.y == targetLocY) {//����һ��Ѱ·�ѵ�����ߣ���ֹͣѰ·���⼴Ϊ���·�ߵ��յ�
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
					if (tmp.y == targetLocY) {//����һ��Ѱ·�ѵ�����ߣ���ֹͣѰ·���⼴Ϊ���·�ߵ��յ�
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
					if (tmp.y == targetLocY) {//����һ��Ѱ·�ѵ�����ߣ���ֹͣѰ·���⼴Ϊ���·�ߵ��յ�
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
					if (tmp.y == targetLocY) {//����һ��Ѱ·�ѵ�����ߣ���ֹͣѰ·���⼴Ϊ���·�ߵ��յ�
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


		int tag_tmp = tag[tmp_Way.back().y - 1][tmp_Way.back().x - 1];//�����յ�λ�õ�tagֵ
		Location flag = tmp_Way.back();//�����յ������
		for (int i = tmp_Way.size() - 1; i--; i >= 0) {
			Location tmp = tmp_Way[i];
			if (tag[tmp.y - 1][tmp.x - 1] >= tag_tmp) {//�����ʵĵ�tagֵ���ڵ��ڵ�ǰĿ���tagֵʱ����ȥ
				tmp_Way.erase(tmp_Way.begin() + i, tmp_Way.begin() + 1 + i);
			}
			//�����ʵĵ�tagֵ���ڵ�ǰĿ���tagֵ-1ʱ
			if (tag[tmp.y - 1][tmp.x - 1] == tag_tmp - 1 && tag[tmp.y - 1][tmp.x - 1] > 0) {
				//���õ���Ŀ����������������λ��ʱ�����¸õ㣬��Ŀ����Ŀ��tagֵ���޸�Ϊ�õ����ֵ
				if ((tmp.y == flag.y && (tmp.x - flag.x == 1 || tmp.x - flag.x == -1)) || (tmp.x == flag.x && (tmp.y - flag.y == 1 || tmp.y - flag.y == -1))) {
					
					/*�˴���bug����������������tag���1�м���ܻ��и���
					��
					
					 0 1
					 1|2
					  |

					*/
					//bug���޸�

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
				//������ȥ�õ�
				else {
					tmp_Way.erase(tmp_Way.begin() + i, tmp_Way.begin() + 1 + i);
				}
			}
			//��tagֵ����0ʱ������ѭ��
			if (tag[tmp.y - 1][tmp.x - 1] == 0) {
				break;
			}
		}

		return tmp_Way;
	}

	//�ж������õ�ľ���Ƿ�������ľ��ì��
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
		if (enemyLoc.x == myLoc.x) {//����͵з�������������
			if (targetY == 9 && enemyLoc.y - myLoc.y == 1) {
				if (Walkable[enemyLoc.y - 1][enemyLoc.x - 1][0] == 0) {//������Կ�Խ
					cur_step.myNewLoc.y++;

					std::cout << " -> " << cur_step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 
					startgame = 1;
					return cur_step;
				}

			}
			if (targetY == 1 && enemyLoc.y - myLoc.y == -1) {
				if (Walkable[enemyLoc.y - 1][enemyLoc.x - 1][2] == 0) {//������Կ�Խ
					cur_step.myNewLoc.y--;
					std::cout << " -> " << cur_step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 
					startgame = 1;
					return cur_step;
				}
			}
		}

		else if (enemyLoc.y == myLoc.y) {//����͵з����Ӻ�������
			if (enemyLoc.x - myLoc.x == 1) {
				if (my_Way.size() > 2) {
					if (my_Way[2] == (enemyLoc.x + 1, enemyLoc.y)) {
						cur_step.myNewLoc = (enemyLoc.x + 1, enemyLoc.y);
						std::cout << " -> " << cur_step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 
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
						std::cout << " -> " << cur_step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 
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
				std::cout << " -> " << cur_step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 
				startgame = 1;
				return cur_step;
			}
		}
		else if (Walkable[myLoc.y - 1][myLoc.x - 1][3] == 0) {
			cur_step.myNewLoc.x = myLoc.x - 1;
			cur_step.myNewLoc.y = myLoc.y;
			if (!(cur_step.myNewLoc == enemyLoc)) {
				std::cout << " -> " << cur_step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 
				startgame = 1;
				return cur_step;
			}
		}
		else if (Walkable[myLoc.y - 1][myLoc.x - 1][2] == 0) {
			cur_step.myNewLoc.x = myLoc.x;
			cur_step.myNewLoc.y = myLoc.y - 1;
			if (!(cur_step.myNewLoc == enemyLoc)) {
				std::cout << " -> " << cur_step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 
				startgame = 1;
				return cur_step;
			}
		}
		else if (Walkable[myLoc.y - 1][myLoc.x - 1][0] == 0) {
			cur_step.myNewLoc.x = myLoc.x;
			cur_step.myNewLoc.y = myLoc.y + 1;
			if (!(cur_step.myNewLoc == enemyLoc)) {
				std::cout << " -> " << cur_step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 
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
		My_Move = 0;                                                         //�Ƿ��л�ʤ·��
		e_Move = 0;
		Step step;                                               // ��ʼ�� step Ĭ�ϲ��ƶ����Ű� 
		e_Way.clear();                                           //�����һ�εĵз�·�����������¼���

		if (this->targetY == 0) {                                // �жϲ���¼�Լ���Ŀ�� 
			const auto d = std::chrono::system_clock::now().time_since_epoch();
			const int nanosecond = (std::chrono::nanoseconds(d).count() / 100) % int64_t(INT32_MAX);
			srand(nanosecond);
			if (newChange.myLoc == PLAYER0_LOC) {                // ������ʼ����Ϊ (5,1) ��Ŀ��Ϊ (x,9) 
				this->targetY = PLAYER1_LOC.y;
				this->e_targetY = PLAYER0_LOC.y;
			}
			else {                                             // ������ʼ����Ϊ (5,9) ��Ŀ��Ϊ (x,1) 
				this->targetY = PLAYER0_LOC.y;
				this->e_targetY = PLAYER1_LOC.y;
			}
		}
		std::cout << newChange;                                  // ������յ������ݵ�����̨��ʾ 



		if (!newChange.newEnemyBlockBar.isNan()) {               // �Է������˵��� 
			BlockBar tmp = newChange.newEnemyBlockBar;
			tmp.normalization();                                 // �淶Ϊ start ����С�� stop �������ʽ 
			this->blocks.push_back(tmp);                         // �洢�淶����
			if (newChange.newEnemyBlockBar.isH()) {              // �жϵ������赲�ĸ��Ӽ����򲢴洢
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

		if (One_Step(newChange.myLoc).x != -1 && One_Step(newChange.myLoc).y != -1) {//���һ���Ϳ��Ի�ʤ
			if (One_Step(newChange.myLoc) == newChange.enemyLoc) {//�з��������ҵ���һ��·����
				if (Walkable[newChange.myLoc.y - 1][newChange.myLoc.x - 1][1] == 0) {
					if (targetY == 9 && Walkable[newChange.myLoc.y - 1][newChange.myLoc.x][0] == 0) {
						step.myNewLoc.x = newChange.myLoc.x + 1;
						step.myNewLoc.y = newChange.myLoc.y;
						std::cout << " -> " << step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 
						startgame = 0;
						return step;                                             //���ؾ���
					}
					if (targetY == 1 && Walkable[newChange.myLoc.y - 1][newChange.myLoc.x][2] == 0) {
						step.myNewLoc.x = newChange.myLoc.x + 1;
						step.myNewLoc.y = newChange.myLoc.y;
						std::cout << " -> " << step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 
						startgame = 0;
						return step;                                             //���ؾ���
					}
				}
				else if (Walkable[newChange.myLoc.y - 1][newChange.myLoc.x - 1][3] == 0) {

					step.myNewLoc.x = newChange.myLoc.x - 1;
					step.myNewLoc.y = newChange.myLoc.y;
					std::cout << " -> " << step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 
					startgame = 0;
					return step;                                             //���ؾ���

				}
				else {
					if (targetY == 9 && Walkable[newChange.myLoc.y - 1][newChange.myLoc.x][0] == 0) {
						step.myNewLoc.x = newChange.myLoc.x;
						step.myNewLoc.y = newChange.myLoc.y - 1;
						std::cout << " -> " << step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 
						startgame = 0;
						return step;                                             //���ؾ���
					}
					if (targetY == 1 && Walkable[newChange.myLoc.y - 1][newChange.myLoc.x][2] == 0) {
						step.myNewLoc.x = newChange.myLoc.x;
						step.myNewLoc.y = newChange.myLoc.y + 1;
						std::cout << " -> " << step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 
						startgame = 0;
						return step;                                             //���ؾ���
					}
				}

			}
			step.myNewLoc = One_Step(newChange.myLoc);
			std::cout << " -> " << step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 
			startgame = 0;
			return step;                                             //���ؾ���
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

		//��ʱ���Ƿ���ľ��
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
				if (tmp.isH()) {              // �жϵ������赲�ĸ��Ӽ����򲢴洢
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
				std::cout << " -> " << step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 

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

		//���з��������ֻ��һ��ʱ
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
					if (tmp.isH()) {              // �жϵ������赲�ĸ��Ӽ����򲢴洢
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
					std::cout << " -> " << step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 

					return step;
				}
				tmp.start.x = newChange.enemyLoc.x - 2;
				tmp.start.y = newChange.enemyLoc.y;
				tmp.stop.x = newChange.enemyLoc.x;
				tmp.stop.y = newChange.enemyLoc.y;
				if (Judge_Blocks(tmp)) {
					step.myNewBlockBar = tmp;
					blocks.push_back(tmp);
					if (tmp.isH()) {              // �жϵ������赲�ĸ��Ӽ����򲢴洢
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
					std::cout << " -> " << step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 

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
					if (tmp.isH()) {              // �жϵ������赲�ĸ��Ӽ����򲢴洢
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
					std::cout << " -> " << step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 

					return step;
				}
				tmp.start.x = newChange.enemyLoc.x - 2;
				tmp.start.y = newChange.enemyLoc.y - 1;
				tmp.stop.x = newChange.enemyLoc.x;
				tmp.stop.y = newChange.enemyLoc.y - 1;
				if (Judge_Blocks(tmp)) {
					step.myNewBlockBar = tmp;
					blocks.push_back(tmp);
					if (tmp.isH()) {              // �жϵ������赲�ĸ��Ӽ����򲢴洢
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
					std::cout << " -> " << step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 

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

			//����������ߣ����Ƿ��õ���
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
					if (tmp.isH()) {              // �жϵ������赲�ĸ��Ӽ����򲢴洢
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
					std::cout << " -> " << step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 

					return step;
				}
				else {

				}
			}
			else {
				std::cout << " -> " << step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 

				return step;
			}

		}

		//step.myNewLoc = randomWalk(newChange.myLoc, newChange.enemyLoc);
		

		if (!step.isMove() && !step.isNan()) {
			step.myNewLoc = randomWalk(newChange.myLoc, newChange.enemyLoc);
		}
		std::cout << " -> " << step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 

		return step;
	}

	void MyPlayer::restart() {//��ʼ��

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

		for (int i = 0; i < 9; i++) {//��ʼ���߽磬�����˶�ʱԽ��
			Walkable[0][i][2] = -1;
			Walkable[8][i][0] = -1;
			Walkable[i][0][3] = -1;
			Walkable[i][8][1] = -1;
		}
		startgame = 1;

		My_Move = 0;                                                         //�Ƿ��л�ʤ·��
		e_Move = 0;
		count_board = 0;

		my_Way.clear();
		e_Way.clear();

	}
	// �������ʵ�ֽ���

}

