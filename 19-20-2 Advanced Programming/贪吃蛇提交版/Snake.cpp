#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <time.h>
#include <conio.h>
using namespace std;
#pragma warning(disable : 4996)
#pragma warning(disable : 26812)

int PASS_SCORE = 10;    //ͨ�ط���
int MAX_ROUND = 10;    //���ջ�ʤ����
int HEIGHT = 17;    //���̸�߶�
int WIDTH = 63;    //���̸���
enum property { WALL, SNAKE, FOOD, TEMP, NONE };    //����ÿһ�������
enum direction { UP, DOWN, LEFT, RIGHT };    //�ߵ��˶�����

//���ϲ�ġ���ÿ���̨����������Ǻܶ�
void getHandle(int x, int y) {
	HANDLE handle;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//���ع�꣬���ÿ�һ��
	SetConsoleCursorPosition(handle, coord);
	CONSOLE_CURSOR_INFO set = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &set);
}

//����ÿ���ڵ��¼����ýں�������
struct SnakeNode {
	int location[2];
	SnakeNode* pre;
	SnakeNode* next;
};

//��
class Snake {
	SnakeNode* head;    //��ͷ
	SnakeNode* tail;    //��β
	bool alive;    //�Ƿ���
	direction direct;    //�˶�����
	friend class Board;
public:
	//��ʼ����
	Snake() {
		tail = new SnakeNode;
		tail->location[0] = 2;
		tail->location[1] = 2;
		tail->next = NULL;    //��β��(2, 2)
		head = new SnakeNode;
		head->location[0] = 2;
		head->location[1] = 3;
		head->pre = NULL;
		head->next = tail;
		tail->pre = head;    //��ͷ��(2, 3)
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

//ʳ��
class Food {
	int location[2];    //ʳ��ĺ�������
	friend class Board;
public:
	//��װ�ĳ�ʼ��ʳ��
	Food() {
		location[0] = -1;
		location[1] = -1;
	}
};

class TempFood {
	int location[2];
	int time;    //����ʱ��
	bool dropped;    //�Ƿ�Ͷ��
	friend class Board;
public:
	TempFood() {
		location[0] = -1;
		location[1] = -1;
		time = 30;
		dropped = false;
	}
};

//���̸�
class Board {
	property** board;    //���̸���һ����ά����
	Snake s;    //��
	Food f;    //ʳ��
	TempFood t;    //��ʱʳ��
	int SPEED;    //���˶����ٶ�
	int score;    //����
	int ROUND;    //ͳ�Ƶڼ���
	int HIGHEST;    //ͳ����߷�
public:
	Board() {
		int i, j;
		//��ʼ�����̸���ǽ���ֳ���Ϸ���ͼǷ���
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
		Snake s;    //��ʼ����
		Food f;    //��װ��ʼ��ʳ��
		TempFood t;    //��װ��ʼ����ʱʳ��
		SPEED = 500;    //��ʼ���ٶ�
		score = 0;    //��ʼ������
		ROUND = 1;    //��ʼ���ڼ���
		HIGHEST = 0;    //��ʼ����߷�
	}
	//�������ʳ��
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
	//���������ʱʳ��
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
	//�ƶ���
	void moveSnake() {
		//�Ӽ��̻�÷������Ҳ�������ҵ�
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
		//������ͷ
		SnakeNode* new_head = new SnakeNode;
		new_head->location[0] = s.head->location[0];
		new_head->location[1] = s.head->location[1];
		new_head->next = s.head;
		s.head->pre = new_head;
		//�����˶�����ȷ����ͷ����
		if (s.direct == UP)
			new_head->location[0] -= 1;
		else if (s.direct == DOWN)
			new_head->location[0] += 1;
		else if (s.direct == LEFT)
			new_head->location[1] -= 1;
		else
			new_head->location[1] += 1;
		s.head = new_head;
		//�����ͷ�����̸�����λ����ǽ��������������
		if (board[s.head->location[0]][s.head->location[1]] == WALL || board[s.head->location[0]][s.head->location[1]] == SNAKE)
			s.alive = false;
		//�����ͷ����λ����ʳ��߳���+1����λ��������ʳ���Ϊ��
		else if (board[s.head->location[0]][s.head->location[1]] == FOOD) {
			score += 1;
			board[s.head->location[0]][s.head->location[1]] = SNAKE;
			getHandle(s.head->location[1], s.head->location[0]);
			cout << "*";
			getHandle(54, 4);
			cout << score;
			dropFood();
			//�������̸���ͬʱӵ���������ϵ���ʱʳ��
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
		//�����ͷ����λ�ÿհף���λ�������ɿհױ�Ϊ��
		else {
			board[s.head->location[0]][s.head->location[1]] = SNAKE;
			getHandle(s.head->location[1], s.head->location[0]);
			cout << "*";
			getHandle(s.tail->location[1], s.tail->location[0]);
			cout << " ";
			//��β����λ�ñ�ɿհף���ɾ��β�ڵ�
			board[s.tail->location[0]][s.tail->location[1]] = NONE;
			SnakeNode* temp = s.tail;
			s.tail = s.tail->pre;
			s.tail->next = NULL;
			temp->pre = NULL;
			delete temp;
		}
		//����ʱʳ�ﵹ��ʱ
		if (t.dropped) {
			t.time -= 1;
			//�Ƴ��ﵽʱ�����Ƶ�ʳ��
			if (t.time == 0) {
				board[t.location[0]][t.location[1]] = NONE;
				getHandle(t.location[1], t.location[0]);
				cout << " ";
				t.dropped = false;
				t.time = 30;
			}
		}
	}
	//��ӡ���̸�
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
	//����Ϸ
	void playGame() {
		srand((unsigned)time(NULL));
		printBoard();
		getHandle(54, 3);
		cout << ROUND;
		dropFood();
		while (s.alive && score < PASS_SCORE) {
			//�������������Ӽ��ʱ����
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
		//�����һ�ֵ�����
		int i, j;
		for (i = 1; i < HEIGHT - 1; i++) {
			for (j = 1; j < 41; j++)
				if (board[i][j] != WALL)
					board[i][j] = NONE;
		}
		//ɾ���߲���ʼ������
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
		//�ж��Ƿ������߷�
		if (score > HIGHEST)
			HIGHEST = score;

		//���¸���ֻ�ڴﵽͨ�ط���ʱ����
		if (score >= PASS_SCORE) {
			ROUND += 1;
			//���˶��ٶȼӿ�
			if (SPEED >= 100)
				SPEED -= 50;
			//�������һ����ǽ
			int x, y, z, k;
			x = (rand() % 5) + 6;
			y = (rand() % 30) + 6;
			//��ǽ��������;�ǽ�ص�
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

		//�����߲����÷���
		s.alive = true;
		score = 0;
	}
	//����������ж����յ�ʤ��
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
