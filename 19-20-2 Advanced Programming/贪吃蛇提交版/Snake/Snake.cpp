#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <time.h>
#include <conio.h>
using namespace std;
#pragma warning(disable : 4996)
#pragma warning(disable : 26812)

int PASS_SCORE = 10;    //通关分数
int MAX_ROUND = 10;    //最终获胜轮数
int HEIGHT = 17;    //棋盘格高度
int WIDTH = 63;    //棋盘格宽度
enum property { WALL, SNAKE, FOOD, TEMP, NONE };    //棋盘每一格的属性
enum direction { UP, DOWN, LEFT, RIGHT };    //蛇的运动方向

//网上查的“获得控制台句柄”，不是很懂
void getHandle(int x, int y) {
	HANDLE handle;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//隐藏光标，更好看一点
	SetConsoleCursorPosition(handle, coord);
	CONSOLE_CURSOR_INFO set = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &set);
}

//链表每个节点记录蛇身该节横纵坐标
struct SnakeNode {
	int location[2];
	SnakeNode* pre;
	SnakeNode* next;
};

//蛇
class Snake {
	SnakeNode* head;    //蛇头
	SnakeNode* tail;    //蛇尾
	bool alive;    //是否存活
	direction direct;    //运动方向
	friend class Board;
public:
	//初始化蛇
	Snake() {
		tail = new SnakeNode;
		tail->location[0] = 2;
		tail->location[1] = 2;
		tail->next = NULL;    //蛇尾在(2, 2)
		head = new SnakeNode;
		head->location[0] = 2;
		head->location[1] = 3;
		head->pre = NULL;
		head->next = tail;
		tail->pre = head;    //蛇头在(2, 3)
		alive = true;
		direct = RIGHT;
	}
	~Snake() {
		SnakeNode* p, * q;
		for (p = head; p != NULL;) {
			q = p;
			p = p->next;
			delete q;
		}
	}
};

//食物
class Food {
	int location[2];    //食物的横纵坐标
	friend class Board;
public:
	//假装的初始化食物
	Food() {
		location[0] = -1;
		location[1] = -1;
	}
};

class TempFood {
	int location[2];
	int time;    //存在时间
	bool dropped;    //是否投放
	friend class Board;
public:
	TempFood() {
		location[0] = -1;
		location[1] = -1;
		time = 30;
		dropped = false;
	}
};

//棋盘格
class Board {
	property** board;    //棋盘格是一个二维数组
	Snake s;    //蛇
	Food f;    //食物
	TempFood t;    //限时食物
	int SPEED;    //蛇运动的速度
	int score;    //分数
	int ROUND;    //统计第几局
	int HIGHEST;    //统计最高分
public:
	Board() {
		int i, j;
		//初始化棋盘格，用墙划分出游戏区和记分栏
		board = new property * [HEIGHT];
		for (i = 0; i < HEIGHT; i++) {
			board[i] = new property[WIDTH];
			for (j = 0; j < WIDTH; j++)
				board[i][j] = NONE;
		}
		for (j = 0; j < WIDTH; j++) {
			board[0][j] = WALL;
			board[HEIGHT - 1][j] = WALL;
		}
		for (i = 1; i < HEIGHT - 1; i++) {
			board[i][0] = WALL;
			board[i][41] = WALL;
			board[i][62] = WALL;
		}
		Snake s;    //初始化蛇
		Food f;    //假装初始化食物
		TempFood t;    //假装初始化限时食物
		SPEED = 500;    //初始化速度
		score = 0;    //初始化分数
		ROUND = 1;    //初始化第几局
		HIGHEST = 0;    //初始化最高分
	}
	//随机生成食物
	~Board() {
		for (int i = 0; i < HEIGHT; i++)
			delete[]board[i];
	}
	void dropFood() {
		f.location[0] = (rand() % 15) + 1;
		f.location[1] = (rand() % 40) + 1;
		while (board[f.location[0]][f.location[1]] != NONE) {
			f.location[0] = (rand() % 15) + 1;
			f.location[1] = (rand() % 40) + 1;
		}
		board[f.location[0]][f.location[1]] = FOOD;
		getHandle(f.location[1], f.location[0]);
		cout << "@";
	}
	//随机生成限时食物
	void dropTempFood() {
		t.location[0] = (rand() % 15) + 1;
		t.location[1] = (rand() % 40) + 1;
		t.time = 30;
		t.dropped = true;
		while (board[t.location[0]][t.location[1]] != NONE) {
			t.location[0] = (rand() % 15) + 1;
			t.location[1] = (rand() % 40) + 1;
		}
		board[t.location[0]][t.location[1]] = TEMP;
		getHandle(t.location[1], t.location[0]);
		cout << "%";
	}
	//移动蛇
	void moveSnake() {
		//从键盘获得方向键，也是网上找的
		if (kbhit()) {
			int d = getch();
			if (d == 224)
				d = getch();
			if (d == 72 && s.direct != DOWN)
				s.direct = UP;
			if (d == 80 && s.direct != UP)
				s.direct = DOWN;
			if (d == 75 && s.direct != RIGHT)
				s.direct = LEFT;
			if (d == 77 && s.direct != LEFT)
				s.direct = RIGHT;
		}
		//生成新头
		SnakeNode* new_head = new SnakeNode;
		new_head->location[0] = s.head->location[0];
		new_head->location[1] = s.head->location[1];
		new_head->next = s.head;
		s.head->pre = new_head;
		//根据运动方向确定新头坐标
		if (s.direct == UP)
			new_head->location[0] -= 1;
		else if (s.direct == DOWN)
			new_head->location[0] += 1;
		else if (s.direct == LEFT)
			new_head->location[1] -= 1;
		else
			new_head->location[1] += 1;
		s.head = new_head;
		//如果新头在棋盘格所在位置是墙或者蛇身，蛇死了
		if (board[s.head->location[0]][s.head->location[1]] == WALL || board[s.head->location[0]][s.head->location[1]] == SNAKE)
			s.alive = false;
		//如果新头所在位置是食物，蛇长度+1，该位置属性由食物变为蛇
		else if (board[s.head->location[0]][s.head->location[1]] == FOOD) {
			score += 1;
			board[s.head->location[0]][s.head->location[1]] = SNAKE;
			getHandle(s.head->location[1], s.head->location[0]);
			cout << "*";
			getHandle(54, 4);
			cout << score;
			dropFood();
			//假设棋盘格不能同时拥有两个以上的限时食物
			if (score % 5 == 0 && t.dropped == false)
				dropTempFood();
		}
		else if (board[s.head->location[0]][s.head->location[1]] == TEMP) {
			score += 1;
			board[s.head->location[0]][s.head->location[1]] = SNAKE;
			getHandle(s.head->location[1], s.head->location[0]);
			cout << "*";
			getHandle(54, 4);
			cout << score;
		}
		//如果新头所在位置空白，该位置属性由空白变为蛇
		else {
			board[s.head->location[0]][s.head->location[1]] = SNAKE;
			getHandle(s.head->location[1], s.head->location[0]);
			cout << "*";
			getHandle(s.tail->location[1], s.tail->location[0]);
			cout << " ";
			//蛇尾所在位置变成空白，并删除尾节点
			board[s.tail->location[0]][s.tail->location[1]] = NONE;
			SnakeNode* temp = s.tail;
			s.tail = s.tail->pre;
			s.tail->next = NULL;
			temp->pre = NULL;
			delete temp;
		}
		//给限时食物倒计时
		if (t.dropped) {
			t.time -= 1;
			//移除达到时间限制的食物
			if (t.time == 0) {
				board[t.location[0]][t.location[1]] = NONE;
				getHandle(t.location[1], t.location[0]);
				cout << " ";
				t.dropped = false;
				t.time = 30;
			}
		}
	}
	//打印棋盘格
	void printBoard() {
		int i, j;
		for (i = 0; i < HEIGHT; i++) {
			for (j = 0; j < WIDTH; j++) {
				getHandle(j, i);
				if (board[i][j] == WALL)
					cout << "#";
				else
					cout << " ";
			}
			cout << endl;
			getHandle(47, 3);
			cout << "Round: " << ROUND;
			getHandle(47, 4);
			cout << "Score: 0";
			getHandle(47, 5);
			cout << "Highest: " << HIGHEST;
			getHandle(42, 8);
			cout << "####################";
		}
		cout << endl;
	}
	//玩游戏
	void playGame() {
		srand((unsigned)time(NULL));
		printBoard();
		getHandle(54, 3);
		cout << ROUND;
		dropFood();
		while (s.alive && score < PASS_SCORE) {
			//随着轮数的增加间隔时间变短
			Sleep(SPEED);
			moveSnake();
		}
		getHandle(45, 11);
		if (score == PASS_SCORE)
			cout << "You won!";
		else
			cout << "Game over!";
		getHandle(45, 12);
		cout << "Total score: " << score;
		getHandle(0, 20);
		system("pause");
		cout << "Press any key to continue";
	}
	void updateGame() {
		//清空上一轮的棋盘
		int i, j;
		for (i = 1; i < HEIGHT - 1; i++) {
			for (j = 1; j < 41; j++)
				if (board[i][j] != WALL)
					board[i][j] = NONE;
		}
		//删除蛇并初始化新蛇
		SnakeNode* p, * q;
		for (p = s.head; p != NULL;) {
			q = p;
			p = p->next;
			delete q;
		}
		s.tail = new SnakeNode;
		s.tail->location[0] = 2;
		s.tail->location[1] = 2;
		s.tail->next = NULL;
		s.head = new SnakeNode;
		s.head->location[0] = 2;
		s.head->location[1] = 3;
		s.head->pre = NULL;
		s.head->next = s.tail;
		s.tail->pre = s.head;
		s.alive = true;
		s.direct = RIGHT;
		//判断是否更新最高分
		if (score > HIGHEST)
			HIGHEST = score;

		//以下更新只在达到通关分数时进行
		if (score >= PASS_SCORE) {
			ROUND += 1;
			//蛇运动速度加快
			if (SPEED >= 100)
				SPEED -= 50;
			//随机生成一堵新墙
			int x, y, z, k;
			x = (rand() % 5) + 6;
			y = (rand() % 30) + 6;
			//新墙尽量避免和旧墙重叠
			while (board[x][y] == WALL) {
				x = (rand() % 5) + 6;
				y = (rand() % 30) + 6;
			}
			z = (rand() % 4);
			switch (z) {
			case 0: {
				for (k = 0; k < 5; k++)
					board[x + k][y] = WALL;
				break;
			}
			case 1: {
				for (k = 0; k < 5; k++)
					board[x - k][y] = WALL;
				break;
			}
			case 2: {
				for (k = 0; k < 5; k++)
					board[x][y + k] = WALL;
				break;
			}
			case 3: {
				for (k = 0; k < 5; k++)
					board[x][y - k] = WALL;
				break;
			}
			};
		}

		//复活蛇并重置分数
		s.alive = true;
		score = 0;
	}
	//获得轮数以判断最终的胜利
	int getRound() {
		return ROUND;
	}
};

int main()
{
	Board b;
	while (true && b.getRound() <= MAX_ROUND) {
		b.playGame();
		b.updateGame();
	}
	cout << " BIG WINNER!" << endl;
	return 0;
}