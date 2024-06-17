#include "MyPlayer.h"

#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>

// �������ʵ�ֿ�ʼ
//using namespace QuoridorUtils;
//int targetY = 0;
//std::vector<QuoridorUtils::BlockBar> blocks;
//QuoridorUtils::Location randomWalk(const QuoridorUtils::Location& myLoc, const QuoridorUtils::Location& enemyLoc) {
//    bool directions[4];
//    directions[0] = myLoc.y < QuoridorUtils::SIZE;           // �Ƿ���������� 
//    directions[1] = myLoc.y > 0;                             // �Ƿ���������� 
//    directions[2] = myLoc.x > 0;                             // �Ƿ���������� 
//    directions[3] = myLoc.x < QuoridorUtils::SIZE;           // �Ƿ���������� 
//    for (auto block : blocks) {                        // ���������б�, �ҵ����赲�ķ��� 
//        if (block.isH()) {                                   // ˮƽ���򵲰�, start �� stop �� y ��� 
//            if (block.start.x == myLoc.x - 1 ||
//                block.start.x == myLoc.x - 2) {              // ���ܵ�·�ĵ��� 
//                if (block.start.y == myLoc.y) {
//                    directions[0] = false;
//                } else if (block.start.y == myLoc.y - 1) {
//                    directions[1] = false;
//                }
//            }
//        }
//        if (block.isV()) {                                   // ��ֱ���򵲰�, start �� stop �� x ��� 
//            if (block.start.y == myLoc.y - 1 ||
//                block.start.y == myLoc.y - 2) {              // ���ܵ�·�ĵ��� 
//                if (block.start.x == myLoc.x) {
//                    directions[2] = false;
//                } else if (block.start.x == myLoc.x - 1) {
//                    directions[3] = false;
//                }
//            }
//        }
//    }
//    int optionsCount = directions[0] + directions[1] + 
//                       directions[2] + directions[3];        // �����ܶ�������, �ض����ڵ���1 
//    int tmp = rand() % optionsCount;                         // ���һ�� [0, optionsCount - 1] ������
//    int directionIndex;                                      // �ҳ����������±� 
//    for (directionIndex = 0; directionIndex < 4; directionIndex++) {
//        if (directions[directionIndex]) {
//            if (tmp <= 0) {
//                break;
//            }
//            tmp--;
//        }
//    }
//    QuoridorUtils::Location nextLoc = myLoc;
//    switch (directionIndex) {
//    case 0:   // ������
//        nextLoc.y++;
//        break;
//    case 1:   // ������
//        nextLoc.y--;
//        break;
//    case 2:   // ������
//        nextLoc.x--;
//        break;
//    case 3:   // ������
//        nextLoc.x++;
//        break;
//    default: ;
//    }
//    if (nextLoc.distance(enemyLoc) == 0) {                   // ��һ���ǵо�λ����Ӧ�����о����� 
//        nextLoc.x = -1;                                      // �˴�����ʵ��, Ĭ����һ���ղ��� 
//        nextLoc.y = -1;
//    }
//    return nextLoc;
//}
// �������ʵ�ֽ���

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
 *  ������������:                           ��������ṹ���£�
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
 * x  1  2  3  4  5  6  7  8  9           x 0  1  2  3  4  5  6  7  8  9
 *
 */

// �������ʵ�ֿ�ʼ

struct node {
    int x, y;
    int step;
}no;

struct Spot {
    int x;
    int y;
    int G;
    int H;
    int F;
    Spot* prev = nullptr;
};

class A_Star {
public:
    A_Star(Location start, int tY);
    ~A_Star();
    Location solve(std::vector<BlockBar> blocks, Location myLoc);
    Spot* m_map = nullptr;
    Spot* m_start = nullptr;
    int targetY;
};

A_Star::A_Star(Location start, int tY) {
    targetY = tY;
    m_map = new Spot[100];
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            Spot& curr_spot = m_map[j * 9 + i];
            curr_spot.x = i;
            curr_spot.y = j;
            curr_spot.G = 100000;
            curr_spot.F = 100000;
        }
    }
    m_start = &m_map[start.y * 9 + start.x];
    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 9; j++) {
            Spot& curr_spot = m_map[j * 9 + i];
            curr_spot.H = std::abs(curr_spot.y - targetY);
        }
    }
}

A_Star::~A_Star() {
    delete[] m_map;
}

Location A_Star::solve(std::vector<BlockBar> blocks, Location myLoc) {
    std::vector<Spot*> openlist;
    std::vector<Spot*> closelist;
    m_start->G = 0;
    m_start->F = m_start->H;
    openlist.push_back(m_start);
    while (openlist.size() != 0) {
        Spot* curr_node = nullptr;
        for (std::vector<Spot*>::iterator node = openlist.begin(); node != openlist.end(); node++) {
            if (curr_node == nullptr) {
                curr_node = *node;
                continue;
            }
            else if ((*node)->F <= curr_node->F) {
                curr_node = *node;
            }
        }
        if (curr_node->y == targetY) {
            Location next;
            while (1) {
                if (curr_node->prev == nullptr || (curr_node->prev->x == m_start->x && curr_node->prev->y == m_start->y)) {
                    next.x = curr_node->x;
                    next.y = curr_node->y;
                    break;
                }
                else
                    curr_node = curr_node->prev;
            }
            //next.x = m_start->next->x;
            //next.y = m_start->next->x;
            return next;
        }
        bool has_prev_x = curr_node->x - 1 >= 1;
        bool has_next_x = curr_node->x + 1 <= 9;
        bool has_prev_y = curr_node->y - 1 >= 1;
        bool has_next_y = curr_node->y + 1 <= 9;
        bool left_a = true, right_a = true, up_a = true, down_a = true;
        for (auto block : blocks) {                        // ���������б�, �ҵ����赲�ķ��� 
            if (block.isH()) {                                   // ˮƽ���򵲰�, start �� stop �� y ��� 
                if (block.start.x == curr_node->x - 1 ||
                    block.start.x == curr_node->x - 2) {              // ���ܵ�·�ĵ��� 
                    if (block.start.y == curr_node->y) {
                        up_a = false;
                    }
                    else if (block.start.y == curr_node->y - 1) {
                        down_a = false;
                    }
                }
            }
            if (block.isV()) {                                   // ��ֱ���򵲰�, start �� stop �� x ��� 
                if (block.start.y == curr_node->y - 1 ||
                    block.start.y == curr_node->y - 2) {              // ���ܵ�·�ĵ��� 
                    if (block.start.x == curr_node->x) {
                        right_a = false;
                    }
                    else if (block.start.x == curr_node->x - 1) {
                        left_a = false;
                    }
                }
            }
        }
        if (has_prev_x) {
            Spot* left = &m_map[curr_node->y * 9 + curr_node->x - 1];
            if (left_a && std::find(closelist.begin(), closelist.end(), left) == closelist.end()) {
                if (curr_node->G + 1 < left->G) {
                    left->prev = curr_node;
                    left->G = curr_node->G + 1;
                    left->F = left->G + left->H;
                    if (std::find(openlist.begin(), openlist.end(), left) == openlist.end()) {
                        openlist.push_back(left);
                    }
                }
            }
        }
        if (has_next_x) {
            Spot* right = &m_map[curr_node->y * 9 + curr_node->x + 1];
            if (right_a && std::find(closelist.begin(), closelist.end(), right) == closelist.end()) {
                if (curr_node->G + 1 < right->G) {
                    right->prev = curr_node;
                    right->G = curr_node->G + 1;
                    right->F = right->G + right->H;
                    if (std::find(openlist.begin(), openlist.end(), right) == openlist.end()) {
                        openlist.push_back(right);
                    }
                }
            }
        }
        if (has_prev_y) {
            Spot* up = &m_map[curr_node->y * 9 + curr_node->x + 9];
            if (up_a && std::find(closelist.begin(), closelist.end(), up) == closelist.end()) {
                if (curr_node->G + 1 < up->G) {
                    up->prev = curr_node;
                    up->G = curr_node->G + 1;
                    up->F = up->G + up->H;
                    if (std::find(openlist.begin(), openlist.end(), up) == openlist.end()) {
                        openlist.push_back(up);
                    }
                }
            }
        }
        if (has_next_y) {
            Spot* down = &m_map[curr_node->y * 9 + curr_node->x - 9];
            if (down_a && std::find(closelist.begin(), closelist.end(), down) == closelist.end()) {
                if (curr_node->G + 1 < down->G) {
                    down->prev = curr_node;
                    down->G = curr_node->G + 1;
                    down->F = down->G + down->H;
                    if (std::find(openlist.begin(), openlist.end(), down) == openlist.end()) {
                        openlist.push_back(down);
                    }
                }
            }
        }
        openlist.erase(std::find(openlist.begin(), openlist.end(), curr_node));
        closelist.push_back(curr_node);
    }
    Location temp;
    temp.x = -1;
    temp.y = -1;
    return temp;
}

int board[10][10];

int MyPlayer::route(const Location& Loc, int target, BlockBar &b, int repr) {
    int map[10][10];
    int min = 10000;
    memset(map, -1, sizeof(map));
    std::queue<node>route;
    no.x = Loc.x;
    no.y = Loc.y;
    no.step = 0;
    route.push(no);
    map[Loc.x][Loc.y] = 0;
    while (!route.empty()) {
        node now = route.front();
        route.pop();
        node tmp;
        tmp.step = now.step + 1;
        bool directions[4];
        directions[0] = now.y < SIZE; 
        directions[1] = now.y > 1; 
        directions[2] = now.x > 1;
        directions[3] = now.x < SIZE;
        for (auto block : this->blocks) {
            if (block.isH()) {
                if (block.start.x == now.x - 1 ||
                    block.start.x == now.x - 2) {
                    if (block.start.y == now.y) {
                        directions[0] = false;
                    }
                    else if (block.start.y == now.y - 1) {
                        directions[1] = false;
                    }
                }
            }
            if (block.isV()) {
                if (block.start.y == now.y - 1 ||
                    block.start.y == now.y - 2) {
                    if (block.start.x == now.x) {
                        directions[2] = false;
                    }
                    else if (block.start.x == now.x - 1) {
                        directions[3] = false;
                    }
                }
            }
        }
        if (b.isH()) {
            if (b.start.x == now.x - 1 ||
                b.start.x == now.x - 2) {
                if (b.start.y == now.y) {
                    directions[0] = false;
                }
                else if (b.start.y == now.y - 1) {
                    directions[1] = false;
                }
            }
        }
        if (b.isV()) {
            if (b.start.y == now.y - 1 ||
                b.start.y == now.y - 2) {
                if (b.start.x == now.x) {
                    directions[2] = false;
                }
                else if (b.start.x == now.x - 1) {
                    directions[3] = false;
                }
            }
        }
        for (int i = 0; i < 4; i++) {
            if (directions[i]) {
                switch (i) {
                case 0:   // ������
                    tmp.x = now.x;
                    tmp.y = now.y + 1;
                    break;
                case 1:   // ������
                    tmp.x = now.x;
                    tmp.y = now.y - 1;
                    break;
                case 2:   // ������
                    tmp.x = now.x - 1;
                    tmp.y = now.y;
                    break;
                case 3:   // ������
                    tmp.x = now.x + 1;
                    tmp.y = now.y;
                    break;
                default:;
                }
                if (map[tmp.x][tmp.y] == -1) {
                    map[tmp.x][tmp.y] = tmp.step;
                    board[tmp.x][tmp.y] += repr;
                    route.push(tmp);
                }
                if (tmp.y == target) {
                    if (tmp.step < min)
                        min = tmp.step;
                }
            }
        }
    }
    return min;
}

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
                } else if (block.start.y == myLoc.y - 1) {
                    directions[1] = false;
                }
            }
        }
        if (block.isV()) {                                   // ��ֱ���򵲰�, start �� stop �� x ��� 
            if (block.start.y == myLoc.y - 1 ||
                block.start.y == myLoc.y - 2) {              // ���ܵ�·�ĵ��� 
                if (block.start.x == myLoc.x) {
                    directions[2] = false;
                } else if (block.start.x == myLoc.x - 1) {
                    directions[3] = false;
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
    default: ;
    }
    if (nextLoc.distance(enemyLoc) == 0) {                   // ��һ���ǵо�λ����Ӧ�����о����� 
        nextLoc.x += (enemyLoc.x - myLoc.x);                                      // �˴�����ʵ��, Ĭ����һ���ղ��� 
        nextLoc.y += (enemyLoc.y - myLoc.y);
    }
    return nextLoc;
}

bool MyPlayer::cover(BlockBar& b) {
    if (b.isH()) {
        for (auto block : this->blocks) {                        // ���������б�, �ҵ����赲�ķ��� 
            if (block.isH()) {                                   // ˮƽ���򵲰�, start �� stop �� y ��� 
                if (block.start.x >= b.start.x - 1 && block.start.x <= b.start.x + 1)
                    return true;
            }
        }
    }
    if (b.isV()) {
        for (auto block : this->blocks) {                        // ���������б�, �ҵ����赲�ķ��� 
            if (block.isV()) {                                   // ��ֱ���򵲰�, start �� stop �� x ��� 
                if (block.start.y >= b.start.y - 1 && block.start.y <= b.start.y + 1)
                    return true;
            }
        }
    }
    return false;
}

Step MyPlayer::nextStep(const ChessboardChange& newChange) {
    // ��֪: ��ʾ���������Ϊ API ʹ���Լ���Ϸ�����˽ⷶ��, ������֤������ȷ��, �����ճ��հ� 
    if (this->targetY == 0) {                                // �жϲ���¼�Լ���Ŀ�� 
        const auto d = std::chrono::system_clock::now().time_since_epoch();
        const int nanosecond = (std::chrono::nanoseconds(d).count() / 100) % int64_t(INT32_MAX);
        srand(nanosecond);
        if (newChange.myLoc == PLAYER0_LOC) {                // ������ʼ����Ϊ (5,1) ��Ŀ��Ϊ (x,9) 
            this->targetY = PLAYER1_LOC.y;
        } else {                                             // ������ʼ����Ϊ (5,9) ��Ŀ��Ϊ (x,1) 
            this->targetY = PLAYER0_LOC.y;
        }
    }
    std::cout << newChange;                                  // ������յ������ݵ�����̨��ʾ 
    if (!newChange.newEnemyBlockBar.isNan()) {               // �Է������˵��� 
        BlockBar tmp = newChange.newEnemyBlockBar;
        tmp.normalization();                                 // �淶Ϊ start ����С�� stop �������ʽ 
        this->blocks.push_back(tmp);                         // �洢�淶���� 
    }
    Step step;                                               // ��ʼ�� step Ĭ�ϲ��ƶ����Ű� 

    memset(board, -1, sizeof(board));
    BlockBar fake_block(-1, -1, -1, -1);
    Location l = newChange.myLoc;
    bool up = false;
    bool down = false;
    if (targetY == 9) {
        up = true;
        for (auto block : this->blocks) {                        // ���������б�, �ҵ����赲�ķ��� 
            if (block.isH()) {                                   // ˮƽ���򵲰�, start �� stop �� y ��� 
                if (block.start.x == newChange.myLoc.x - 1 ||
                    block.start.x == newChange.myLoc.x - 2) {              // ���ܵ�·�ĵ��� 
                    if (block.start.y == newChange.myLoc.y) {
                        up = false;
                        break;
                    }
                }
            }
        }
    }
    else if (targetY == 1) {
        down = true;
        for (auto block : this->blocks) {                        // ���������б�, �ҵ����赲�ķ��� 
            if (block.isH()) {                                   // ˮƽ���򵲰�, start �� stop �� y ��� 
                if (block.start.x == newChange.myLoc.x - 1 ||
                    block.start.x == newChange.myLoc.x - 2) {              // ���ܵ�·�ĵ��� 
                    if (block.start.y == newChange.myLoc.y - 1) {
                        down = false;
                        break;
                    }
                }
            }
        }
    }
    if (up) {
        l.y += 1;
        step.myNewLoc = l;
    }
    else if (down) {
        l.y -= 1;
        step.myNewLoc = l;
    }
    if (l.distance(newChange.enemyLoc) == 0 && newChange.enemyLoc.y != targetY) {                   // ��һ���ǵо�λ����Ӧ�����о����� 
        l.x += (newChange.enemyLoc.x - newChange.myLoc.x);                                      // �˴�����ʵ��, Ĭ����һ���ղ��� 
        l.y += (newChange.enemyLoc.y - newChange.myLoc.y);
        step.myNewLoc = l;
    }
    else if (route(newChange.myLoc, targetY, fake_block, -1) <= route(newChange.enemyLoc, 10 - targetY, fake_block, 2)) {
        A_Star problem(newChange.myLoc, targetY);
        Location target = problem.solve(this->blocks, newChange.myLoc);
        if (target.x != -1 && targetY != -1) {
            if (target == newChange.enemyLoc) {
                if (l.distance(newChange.enemyLoc) == 0 && newChange.enemyLoc.y != targetY) {                   // ��һ���ǵо�λ����Ӧ�����о����� 
                    target.x += (newChange.enemyLoc.x - newChange.myLoc.x);                                      // �˴�����ʵ��, Ĭ����һ���ղ��� 
                    target.y += (newChange.enemyLoc.y - newChange.myLoc.y);
                }
                else if (l.distance(newChange.enemyLoc) == 0 && newChange.enemyLoc.y == targetY)
                    step.myNewLoc = randomWalk(newChange.myLoc, newChange.enemyLoc);
            }
            step.myNewLoc = target;
        }
        else
            step.myNewLoc = randomWalk(newChange.myLoc, newChange.enemyLoc);
    }
    else {
        int max_score = -1000;
        BlockBar max_block(-1, -1, -1, -1);
        for (int i = 2; i <= 7; i++) {
            for (int j = 2; j <= 7; j++) {
                if (board[i][j] > 0) {
                    BlockBar temp1(i, j, i + 2, j);
                    if (!cover(temp1) && ((route(newChange.myLoc, targetY, temp1, 0) != 1000 || route(newChange.enemyLoc, 10 - targetY, temp1, 0) != 1000))) {
                        int t = route(newChange.enemyLoc, 10 - targetY, temp1, 0) - route(newChange.myLoc, targetY, temp1, 0);
                        if (t > max_score) {
                            max_score = t;
                            max_block = temp1;
                        }
                    }
                    BlockBar temp2(i, j, i - 2, j);
                    if (!cover(temp2) && (route(newChange.myLoc, targetY, temp2, 0) != 1000 || route(newChange.enemyLoc, 10 - targetY, temp2, 0) != 1000)) {
                        int t = route(newChange.enemyLoc, 10 - targetY, temp2, 0) - route(newChange.myLoc, targetY, temp2, 0);
                        if (t > max_score) {
                            max_score = t;
                            max_block = temp2;
                        }
                    }
                    BlockBar temp3(i, j, i, j + 2);
                    if (!cover(temp3) && (route(newChange.myLoc, targetY, temp3, 0) != 1000 || route(newChange.enemyLoc, 10 - targetY, temp3, 0) != 1000)) {
                        int t = route(newChange.enemyLoc, 10 - targetY, temp3, 0) - route(newChange.myLoc, targetY, temp3, 0);
                        if (t > max_score) {
                            max_score = t;
                            max_block = temp3;
                        }
                    }
                    BlockBar temp4(i, j, i, j + 2);
                    if (!cover(temp4) && (route(newChange.myLoc, targetY, temp4, 0) != 1000 || route(newChange.enemyLoc, 10 - targetY, temp4, 0) != 1000)) {
                        int t = route(newChange.enemyLoc, 10 - targetY, temp4, 0) - route(newChange.myLoc, targetY, temp4, 0);
                        if (t > max_score) {
                            max_score = t;
                            max_block = temp4;
                        }
                    }
                }
            }
        }
        step.myNewBlockBar = max_block;
        if (max_block == fake_block) {
            A_Star problem(newChange.myLoc, targetY);
            Location target = problem.solve(this->blocks, newChange.myLoc);
            if (target.x != -1 && targetY != -1) {
                if (target == newChange.enemyLoc) {
                    if (l.distance(newChange.enemyLoc) == 0 && newChange.enemyLoc.y != targetY) {                   // ��һ���ǵо�λ����Ӧ�����о����� 
                        target.x += (newChange.enemyLoc.x - newChange.myLoc.x);                                      // �˴�����ʵ��, Ĭ����һ���ղ��� 
                        target.y += (newChange.enemyLoc.y - newChange.myLoc.y);
                    }
                    else if (l.distance(newChange.enemyLoc) == 0 && newChange.enemyLoc.y == targetY)
                        step.myNewLoc = randomWalk(newChange.myLoc, newChange.enemyLoc);
                }
                step.myNewLoc = target;
            }
            else
                step.myNewLoc = randomWalk(newChange.myLoc, newChange.enemyLoc);
        }
        else
            blocks.push_back(max_block);
    }
    std::cout << " -> " << step << std::endl;                // ����ҵľ��ߵ�����̨��ʾ 
    return step;
}

void MyPlayer::restart() {
    this->blocks.clear();
    this->targetY = 0;
}
// �������ʵ�ֽ���

// �������ʵ�ֿ�ʼ
//Step MyPlayer::nextStep(const ChessboardChange& newChange) {
//    // ��֪: ��ʾ���������Ϊ API ʹ���Լ���Ϸ�����˽ⷶ��, ������֤������ȷ��, �����ճ��հ� 
//    if (targetY == 0) {                                // �жϲ���¼�Լ���Ŀ��
//        const auto d = std::chrono::system_clock::now().time_since_epoch();
//        const int nanosecond = (std::chrono::nanoseconds(d).count() / 100) % int64_t(INT32_MAX);
//        srand(nanosecond);
//        if (newChange.myLoc == PLAYER0_LOC) {                // ������ʼ����Ϊ (5,1) ��Ŀ��Ϊ (x,9)
//            targetY = PLAYER1_LOC.y;
//        } else {                                             // ������ʼ����Ϊ (5,9) ��Ŀ��Ϊ (x,1)
//            targetY = PLAYER0_LOC.y;
//        }
//    }
//    std::cout << newChange << std::endl;                     // ������յ������ݵ�����̨��ʾ  
//    if (!newChange.newEnemyBlockBar.isNan()) {               // �Է������˵��� 
//        BlockBar tmp = newChange.newEnemyBlockBar;
//        tmp.normalization();                                 // �淶Ϊ start ����С�� stop �������ʽ 
//        blocks.push_back(tmp);                         // �洢���� 
//    }
//    Step step;                                               // ��ʼ�� step Ĭ�ϲ��ƶ����Ű� 
//    step.myNewLoc = randomWalk(newChange.myLoc, newChange.enemyLoc);
//    std::cout << step << std::endl;                          // ����ҵľ��ߵ�����̨��ʾ 
//    return step;
//}
//
//void MyPlayer::restart() {
//    blocks.clear();
//    targetY = 0;
//}
// �������ʵ�ֽ���
}

//"host": "118.25.152.44"