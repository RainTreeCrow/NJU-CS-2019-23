#include <windows.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <time.h>
using namespace std;

#define  _NULL_      0
#define  _MY_TANK_   1
#define  _TANKETTE_  2
#define  _AMORED_    3
#define  _PIAT_      4
#define  _HEAVY_     5
#define  _BRICK_     6
#define  _WALL_      7
#define  _STEEL_     8
#define  _HOME_      9
#define  _BULLET_    10

#define  _TANK_      -1
#define  _STAR_      -2
#define  _CLOCK_     -3
#define  _SHOVEL_    -4
#define  _BOMB_      -5

#define  _ALIVE_     1
#define  _KILLED_    2
#define  _VICTORY_   3

#define  _SLOW_      1
#define  _NORMAL_    2
#define  _FAST_      3

#define  _UP_        1
#define  _DOWN_      2
#define  _LEFT_      3
#define  _RIGHT_     4

int COUNT = _BULLET_;

struct Position {
	int X;
	int Y;
};

void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void MoveCursor(Position pos) {
	COORD Pos = { pos.X * 2, pos.Y };
	HANDLE OutPutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(OutPutHandle, Pos);
	HideCursor();
}

class Map {
	friend class Bullet;
	friend class MyTank;
	friend class EnemyTank;
	friend class Game;
private:
	int WIDTH;
	int HEIGHT;
	int LIFE;
	int SCORE;
	int ENEMY;
	int STATUS;
	int ME_STOP;
	int ENEMY_STOP;
	int** BOARD;
public:
	Map(int w, int h) {
		WIDTH = w;
		HEIGHT = h;
		LIFE = 0;
		SCORE = 0;
		ENEMY = 4;
		STATUS = _ALIVE_;
		ME_STOP = 0;
		ENEMY_STOP = 0;
		BOARD = new int* [WIDTH];
		for (int i = 0; i < WIDTH; i++) {
			BOARD[i] = new int[HEIGHT];
		}
		for (int w = 0; w < WIDTH; w++) {
			for (int h = 0; h < HEIGHT; h++) {
				BOARD[w][h] = _NULL_;
			}
		}
		for (int w = 0; w < WIDTH; w++) {
			BOARD[w][0] = _WALL_;
			BOARD[w][HEIGHT - 1] = _WALL_;
		}
		for (int h = 0; h < HEIGHT; h++) {
			BOARD[0][h] = _WALL_;
			BOARD[WIDTH - 1][h] = _WALL_;
		}
		for (int h = 0; h < HEIGHT; h++) {
			BOARD[WIDTH - 15][h] = _WALL_;
		}
	}
	~Map() {
		for (int i = 0; i < WIDTH; i++)
			delete BOARD[i];
		delete BOARD;
	}
	void set_home() {
		LIFE = 4;
		SCORE = 0;
		ENEMY = 4;
		STATUS = _ALIVE_;
		for (int i = 14; i < 17; i++) {
			for (int j = 4; j > 1; j--) {
				BOARD[i][HEIGHT - j] = _HOME_;
			}
		}
		for (int i = 13; i < 18; i++)
			BOARD[i][HEIGHT - 5] = _BRICK_;
		for (int j = 5; j > 1; j--) {
			BOARD[13][HEIGHT - j] = _BRICK_;
			BOARD[17][HEIGHT - j] = _BRICK_;
		}
		for (int j = 12; j < 17; j++) {
			for (int i = 1; i < 6; i++)
				BOARD[i][j] = _STEEL_;
			for (int i = 6; i < 25; i++)
				BOARD[i][j] = _BRICK_;
			for (int i = 25; i < 30; i++)
				BOARD[i][j] = _STEEL_;
		}
		for (int j = 20; j < 22; j++) {
			for (int i = 1; i < 12; i++)
				BOARD[i][j] = _BRICK_;
			for (int i = 12; i < 19; i++)
				BOARD[i][j] = _STEEL_;
			for (int i = 19; i < 30; i++)
				BOARD[i][j] = _BRICK_;
		}
		BOARD[3][14] = _BOMB_;
		BOARD[27][14] = _TANK_;
		BOARD[8][14] = _STAR_;
		BOARD[15][14] = _STAR_;
		BOARD[22][14] = _STAR_;
		BOARD[11][18] = _CLOCK_;
		BOARD[19][18] = _SHOVEL_;
		BOARD[3][27] = _TANK_;
		BOARD[27][27] = _BOMB_;
	}
	void print_map() {
		for (int h = 0; h < HEIGHT; h++) {
			for (int w = 0; w < WIDTH; w++) {
				if (BOARD[w][h] == _BRICK_ || BOARD[w][h] == _WALL_)
					cout << "〓";
				else if (BOARD[w][h] == _STEEL_)
					cout << "■";
				else if (BOARD[w][h] == _HOME_)
					cout << "★";
				else if (BOARD[w][h] == _TANK_)
					cout << "□";
				else if (BOARD[w][h] == _STAR_)
					cout << "☆";
				else if (BOARD[w][h] == _CLOCK_)
					cout << "◎";
				else if (BOARD[w][h] == _SHOVEL_)
					cout << "▲";
				else if (BOARD[w][h] == _BOMB_)
					cout << "●";
				else
					cout << "  ";
			}
			cout << endl;
		}
		GetStdHandle(STD_OUTPUT_HANDLE);
		Position InfoPos;
		InfoPos.X = WIDTH - 10;
		InfoPos.Y = 3;
		MoveCursor(InfoPos);
		cout << "分数: " << 0;
		InfoPos.X = WIDTH - 10;
		InfoPos.Y = 5;
		MoveCursor(InfoPos);
		cout << "生命: " << 4;
		InfoPos.X = WIDTH - 10;
		InfoPos.Y = 7;
		MoveCursor(InfoPos);
		cout << "敌方坦克: " << 4;
		InfoPos.X = WIDTH - 10;
		InfoPos.Y = 9;
		MoveCursor(InfoPos);
		cout << "状态: 存活";
		InfoPos.X = WIDTH - 14;
		InfoPos.Y = 13;
		MoveCursor(InfoPos);
		cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓";
		InfoPos.X = WIDTH - 9;
		InfoPos.Y = 16;
		MoveCursor(InfoPos);
		cout << "帮助";
		InfoPos.X = WIDTH - 11;
		InfoPos.Y = 18;
		MoveCursor(InfoPos);
		cout << "按方向键移动";
		InfoPos.X = WIDTH - 11;
		InfoPos.Y = 20;
		MoveCursor(InfoPos);
		cout << "按x键发射子弹";
		InfoPos.X = WIDTH - 11;
		InfoPos.Y = 22;
		MoveCursor(InfoPos);
		cout << "按回车重新开始";
		InfoPos.X = WIDTH - 11;
		InfoPos.Y = 24;
		MoveCursor(InfoPos);
		cout << "按ESC退出游戏";
	}
	void set_steel() {
		Position p;
		for (int i = 13; i < 18; i++) {
			p.X = i;
			p.Y = HEIGHT - 5;
			BOARD[i][HEIGHT - 5] = _STEEL_;
			MoveCursor(p);
			cout << "■";
		}
		for (int j = 5; j > 1; j--) {
			p.Y = HEIGHT - j;
			BOARD[13][HEIGHT - j] = _STEEL_;
			BOARD[17][HEIGHT - j] = _STEEL_;
			p.X = 13;
			MoveCursor(p);
			cout << "■";
			p.X = 17;
			MoveCursor(p);
			cout << "■";
		}
	}
	void set_null() {
		Position p;
		for (int i = 13; i < 18; i++) {
			p.X = i;
			p.Y = HEIGHT - 5;
			BOARD[i][HEIGHT - 5] = _NULL_;
			MoveCursor(p);
			cout << "  ";
		}
		for (int j = 5; j > 1; j--) {
			p.Y = HEIGHT - j;
			BOARD[13][HEIGHT - j] = _NULL_;
			BOARD[17][HEIGHT - j] = _NULL_;
			p.X = 13;
			MoveCursor(p);
			cout << "  ";
			p.X = 17;
			MoveCursor(p);
			cout << "  ";
		}
	}
	void update_info() {
		Position InfoPos;
		InfoPos.X = WIDTH - 10;
		InfoPos.Y = 3;
		MoveCursor(InfoPos);
		cout << "分数: " << SCORE << "   ";
		InfoPos.X = WIDTH - 10;
		InfoPos.Y = 5;
		MoveCursor(InfoPos);
		cout << "生命: " << LIFE << "   ";
		InfoPos.X = WIDTH - 10;
		InfoPos.Y = 7;
		MoveCursor(InfoPos);
		cout << "敌方坦克: " << ENEMY << "   ";
		InfoPos.X = WIDTH - 10;
		InfoPos.Y = 9;
		MoveCursor(InfoPos);
		cout << "状态: ";
		switch (STATUS) {
		case _ALIVE_:
			cout << "存活";
			break;
		case _KILLED_:
			cout << "死亡";
			break;
		case _VICTORY_:
			cout << "胜利";
		}
	}
	bool check_tank_route(Position p, int dir) {
		switch (dir) {
		case _UP_: {
			if (BOARD[p.X][p.Y - 2] <= _NULL_ && BOARD[p.X - 1][p.Y - 2] <= _NULL_ && BOARD[p.X + 1][p.Y - 2] <= _NULL_)
				return 1;
			else
				return 0;
		}
		case _DOWN_: {
			if (BOARD[p.X][p.Y + 2] <= _NULL_ && BOARD[p.X - 1][p.Y + 2] <= _NULL_ && BOARD[p.X + 1][p.Y + 2] <= _NULL_)
				return 1;
			else
				return 0;
		}
		case _LEFT_: {
			if (BOARD[p.X - 2][p.Y] <= _NULL_ && BOARD[p.X - 2][p.Y - 1] <= _NULL_ && BOARD[p.X - 2][p.Y + 1] <= _NULL_)
				return 1;
			else
				return 0;
		}
		case _RIGHT_: {
			if (BOARD[p.X + 2][p.Y] <= _NULL_ && BOARD[p.X + 2][p.Y - 1] <= _NULL_ && BOARD[p.X + 2][p.Y + 1] <= _NULL_)
				return 1;
			else
				return 0;
		}
		}
	}
	void clear_tank(Position p) {
		Position temp;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				temp.X = p.X + i - 1;
				temp.Y = p.Y + j - 1;
				BOARD[p.X + i - 1][p.Y + j - 1] = _NULL_;
				MoveCursor(temp);
				cout << "  ";
			}
	}
	void print_tank(int REPR, Position p, int dir) {
		Position temp;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				temp.X = p.X + i - 1;
				temp.Y = p.Y + j - 1;
				BOARD[p.X + i - 1][p.Y + j - 1] = REPR;
				MoveCursor(temp);
				cout << "█";
			}
		}
		MoveCursor(p);
		switch (REPR) {
		case _MY_TANK_: {
			cout << "我"; break; }
		case _TANKETTE_: {
			cout << "小"; break; }
		case _AMORED_: {
			cout << "甲"; break; }
		case _PIAT_: {
			cout << "反"; break; }
		case _HEAVY_: {
			cout << "重"; break; }
		}
		switch (dir) {
		case _UP_: {
			p.X -= 1;
			p.Y -= 1;
			MoveCursor(p);
			cout << "  ";
			p.X += 2;
			MoveCursor(p);
			cout << "  ";
			break;
		}
		case _DOWN_:{
			p.X -= 1;
			p.Y += 1;
			MoveCursor(p);
			cout << "  ";
			p.X += 2;
			MoveCursor(p);
			cout << "  ";
			break;
		}
		case _LEFT_: {
			p.X -= 1;
			p.Y -= 1;
			MoveCursor(p);
			cout << "  ";
			p.Y += 2;
			MoveCursor(p);
			cout << "  ";
			break;
		}
		case _RIGHT_: {
			p.X += 1;
			p.Y -= 1;
			MoveCursor(p);
			cout << "  ";
			p.Y += 2;
			MoveCursor(p);
			cout << "  ";
			break;
		}
		}
	}
	void clear_bullet(Position p) {
		BOARD[p.X][p.Y] = _NULL_;
		MoveCursor(p);
		cout << "  ";
	}
	void print_bullet(int NUMBER, Position p) {
		BOARD[p.X][p.Y] = NUMBER;
		MoveCursor(p);
		cout << "⊙";
	}
	void win() {
		STATUS = _VICTORY_;
		update_info();
	}
	void lose() {
		STATUS = _KILLED_;
		update_info();
	}
};

Map MAP(45, 30);

class Bullet {
	int NUMBER;
	int SPEED;
	int DAMAGE;
	int DIRECTION;
	int OWNER;
	bool MY;
	bool ABLE;
	bool EXIST;
	Position POS;
	friend class Game;
public:
	Bullet() {
		NUMBER = 0;
		SPEED = 0;
		DAMAGE = 0;
		DIRECTION = 0;
		OWNER = 0;
		MY = false;
		ABLE = false;
		EXIST = false;
		POS.X = 0;
		POS.Y = 0;
	}
	Bullet(int s, int d, int dir, int o, bool m, bool a, Position p) {
		NUMBER = COUNT;
		COUNT += 1;
		SPEED = s;
		DAMAGE = d;
		DIRECTION = dir;
		OWNER = o;
		MY = m;
		ABLE = a;
		EXIST = true;
		switch (dir) {
		case _UP_: {
			POS.X = p.X;
			POS.Y = p.Y - 1;
			break;
		}
		case _DOWN_: {
			POS.X = p.X;
			POS.Y = p.Y + 1;
			break;
		}
		case _LEFT_: {
			POS.X = p.X - 1;
			POS.Y = p.Y;
		}
		case _RIGHT_: {
			POS.X = p.X + 1;
			POS.Y = p.Y;
		}
		}
		if (MAP.BOARD[p.X][p.Y] == _WALL_)
			EXIST = false;
	}
	void fly();
	void hit();
};

Bullet BULLETS[1000];

class Tank {
	friend class Game;
protected:
	int ARMOR;
	int LIFE;
	int DAMAGE;
	int MOVEMENT_SPEED;
	int BULLET_SPEED;
	int REPR;
	int DIRECTION;
	bool STEEL_ABLE;
	bool MY;
	bool ALIVE;
	Position POS;
public:
	Tank() {
		ARMOR = 0;
		LIFE = 0;
		DAMAGE = 0;
		MOVEMENT_SPEED = 0;
		BULLET_SPEED = 0;
		REPR = _NULL_;
		DIRECTION = 0;
		STEEL_ABLE = false;
		MY = false;
		ALIVE = false;
		POS.X = 0;
		POS.Y = 0;
	}
	virtual void move(){
		;
	}
	virtual void shoot() {
		;
	}
	void reduce_armor(int amount) {
		ARMOR -= amount;
		if (ARMOR <= 0)
			death_callback();
	}
	virtual void eat_tank() {
		;
	}
	virtual void eat_star() {
		;
	}
	virtual void eat_clock() {
		;
	}
	virtual void eat_shovel() {
		;
	}
	virtual void eat_bomb() {
		;
	}
	virtual void death_callback() {
		;
	}
	virtual void restart() {
		;
	}
};

class MyTank :public Tank {
	int ATE;
	friend class Map;
	friend class EnemyTank;
	friend class Game;
public:
	MyTank() {
		ARMOR = 1;
		LIFE = 4;
		DAMAGE = 1;
		MOVEMENT_SPEED = _SLOW_;
		BULLET_SPEED = _SLOW_;
		REPR = _MY_TANK_;
		DIRECTION = _UP_;
		STEEL_ABLE = false;
		MY = true;
		ALIVE = true;
		POS.X = 9;
		POS.Y = 27;
		ATE = 0;
	}
	void move() {
		int count = 0;
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			DIRECTION = _UP_;
			if (MAP.check_tank_route(POS, DIRECTION)) {
				MAP.clear_tank(POS);
				POS.Y--;
				MAP.print_tank(REPR, POS, DIRECTION);
			}
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			DIRECTION = _DOWN_;
			if (MAP.check_tank_route(POS, DIRECTION)) {
				MAP.clear_tank(POS);
				POS.Y++;
				MAP.print_tank(REPR, POS, DIRECTION);
			}
		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			DIRECTION = _LEFT_;
			if (MAP.check_tank_route(POS, DIRECTION)) {
				MAP.clear_tank(POS);
				POS.X--;
				MAP.print_tank(REPR, POS, DIRECTION);
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			DIRECTION = _RIGHT_;
			if (MAP.check_tank_route(POS, DIRECTION)) {
				MAP.clear_tank(POS);
				POS.X++;
				MAP.print_tank(REPR, POS, DIRECTION);
			}
		}
		else if (count++ % 7 == 0) {
			;
		}
		if (GetAsyncKeyState(88) & 0x8000) {
			shoot();
		}
	}
	void shoot() {
		if (1) {
			Bullet b(BULLET_SPEED, DAMAGE, DIRECTION, REPR, MY, STEEL_ABLE, POS);
			BULLETS[COUNT - _BULLET_] = b;
			COUNT += 1;
			if (COUNT == _BULLET_ + 1000)
				COUNT = _BULLET_;
		}
	}
	void eat_tank() {
		LIFE += 1;
		MAP.LIFE += 1;
		Position InfoPos;
		InfoPos.X = MAP.WIDTH - 10;
		InfoPos.Y = 5;
		MoveCursor(InfoPos);
		cout << "生命: " << MAP.LIFE << "   ";
	}
	void eat_star() {
		if (ATE == 0)
			BULLET_SPEED += 1;
		else if (ATE == 1)
			DAMAGE *= 2;
		else if (ATE == 2)
			STEEL_ABLE = true;
		ATE++;
	}
	void eat_clock() {
		MAP.ENEMY_STOP = 5;
	}
	void eat_shovel() {
		MAP.set_steel();
	}
	void eat_bomb();
	void death_callback() {
		LIFE -= 1;
		MAP.LIFE -= 1;
		if (LIFE <= 0) {
			ALIVE = false;
			MAP.lose();
		}
		else {
			DAMAGE = 1;
			BULLET_SPEED = _SLOW_;
			STEEL_ABLE = false;
			MAP.clear_tank(POS);
			Position temp;
			temp.X = MAP.WIDTH - 10;
			temp.Y = 5;
			MoveCursor(temp);
			cout << "生命: " << LIFE;
			ARMOR = 1;
			DAMAGE = 1;
			MOVEMENT_SPEED = _SLOW_;
			BULLET_SPEED = _SLOW_;
			DIRECTION = _UP_;
			STEEL_ABLE = false;
			POS.X = 9;
			POS.Y = 27;
			MAP.print_tank(REPR, POS, DIRECTION);
		}
	}
	void restart() {
		ARMOR = 1;
		LIFE = 4;
		DAMAGE = 1;
		MOVEMENT_SPEED = _SLOW_;
		BULLET_SPEED = _SLOW_;
		REPR = _MY_TANK_;
		DIRECTION = _UP_;
		STEEL_ABLE = false;
		MY = true;
		ALIVE = true;
		POS.X = 9;
		POS.Y = 27;
		ATE = 0;
		MAP.print_tank(REPR, POS, DIRECTION);
	}
};

MyTank MINE;

class EnemyTank : public Tank{
protected:
	int COOL_DOWN;
public:
	EnemyTank() {
		ARMOR = 0;
		LIFE = 0;
		DAMAGE = 0;
		MOVEMENT_SPEED = 0;
		BULLET_SPEED = 0;
		REPR = _NULL_;
		DIRECTION = 0;
		STEEL_ABLE = false;
		MY = false;
		ALIVE = false;
		POS.X = 0;
		POS.Y = 0;
		COOL_DOWN = 3;
	}
	void move() {
		if (ALIVE) {
			if (!(rand() % 23)) {
				DIRECTION = rand() % 4 + 1;
				if (rand() % 3)
					return;
			}
			if (MAP.check_tank_route(POS, DIRECTION)) {
				MAP.clear_tank(POS);
				switch (DIRECTION) {
				case _UP_: {
					POS.Y--;
					break;
				}
				case _DOWN_: {
					POS.Y++;
					break;
				}
				case _LEFT_: {
					POS.X--;
					break;
				}
				case _RIGHT_: {
					POS.X++;
					break;
				}
				}
				MAP.print_tank(REPR, POS, DIRECTION);
			}
			else {
				if ((rand() % 4)) {
					DIRECTION = rand() % 4 + 1;
				}
				else {
					int j;
					for (j = 1; j <= 4; j++) {
						if (MAP.check_tank_route(POS, j)) {
							DIRECTION = j;
							break;
						}
					}
				}
				MAP.print_tank(REPR, POS, DIRECTION);
			}
		}
		if (COOL_DOWN <= 0) {
			shoot();
			COOL_DOWN = 3;
		}
		else
			COOL_DOWN -= 1;
	}
	void shoot() {
		if (1) {
			Bullet b(BULLET_SPEED, DAMAGE, DIRECTION, REPR, MY, STEEL_ABLE, POS);
			BULLETS[COUNT - _BULLET_] = b;
			COUNT += 1;
			if (COUNT == _BULLET_ + 1000)
				COUNT = _BULLET_;
		}
	}
	void eat_tank() {
		ARMOR += 1;
	}
	void eat_star() {
		STEEL_ABLE = true;
	}
	void eat_clock() {
		MAP.ME_STOP = 25;
	}
	void eat_shovel() {
		MAP.set_null();
	}
	void eat_bomb() {
		MINE.death_callback();
	}
	void death_callback() {
		if (ALIVE) {
			LIFE -= 1;
			if (LIFE <= 0) {
				ALIVE = false;
				MAP.clear_tank(POS);
				MAP.ENEMY -= 1;
				Position InfoPos;
				InfoPos.X = MAP.WIDTH - 10;
				InfoPos.Y = 7;
				MoveCursor(InfoPos);
				cout << "敌方坦克: " << MAP.ENEMY;
				if (MAP.ENEMY <= 0)
					MAP.win();
			}
		}
	}
	void restart() {
		;
	}
};

class Tankette : public EnemyTank {
	friend class Game;
public:
	Tankette() {
		ARMOR = 1;
		LIFE = 1;
		DAMAGE = 1;
		MOVEMENT_SPEED = _SLOW_;
		BULLET_SPEED = _SLOW_;
		REPR = _TANKETTE_;
		DIRECTION = _DOWN_;
		STEEL_ABLE = false;
		MY = false;
		ALIVE = true;
		POS.X = 2;
		POS.Y = 2;
		COOL_DOWN = 3;
	}
	void restart() {
		ARMOR = 1;
		LIFE = 1;
		DAMAGE = 1;
		MOVEMENT_SPEED = _SLOW_;
		BULLET_SPEED = _SLOW_;
		REPR = _TANKETTE_;
		DIRECTION = _DOWN_;
		STEEL_ABLE = false;
		MY = false;
		ALIVE = true;
		POS.X = 2;
		POS.Y = 2;
		COOL_DOWN = 3;
		MAP.print_tank(REPR, POS, DIRECTION);
	}
};

Tankette TANKETTE;

class AmoredCar : public EnemyTank {
	friend class Game;
public:
	AmoredCar() {
		ARMOR = 2;
		LIFE = 1;
		DAMAGE = 2;
		MOVEMENT_SPEED = _FAST_;
		BULLET_SPEED = _NORMAL_;
		REPR = _AMORED_;
		DIRECTION = _DOWN_;
		STEEL_ABLE = true;
		MY = false;
		ALIVE = true;
		POS.X = 11;
		POS.Y = 2;
		COOL_DOWN = 3;
	}
	void restart() {
		ARMOR = 2;
		LIFE = 1;
		DAMAGE = 2;
		MOVEMENT_SPEED = _FAST_;
		BULLET_SPEED = _NORMAL_;
		REPR = _AMORED_;
		DIRECTION = _DOWN_;
		STEEL_ABLE = true;
		MY = false;
		ALIVE = true;
		POS.X = 11;
		POS.Y = 2;
		COOL_DOWN = 3;
		MAP.print_tank(REPR, POS, DIRECTION);
	}
};

AmoredCar AMORED;

class Piat : public EnemyTank {
	friend class Game;
public:
	Piat() {
		ARMOR = 1;
		LIFE = 1;
		DAMAGE = 3;
		MOVEMENT_SPEED = _NORMAL_;
		BULLET_SPEED = _FAST_;
		REPR = _PIAT_;
		DIRECTION = _DOWN_;
		STEEL_ABLE = true;
		MY = false;
		ALIVE = false;
		POS.X = 19;
		POS.Y = 2;
		COOL_DOWN = 3;
	}
	void restart() {
		ARMOR = 1;
		LIFE = 1;
		DAMAGE = 3;
		MOVEMENT_SPEED = _NORMAL_;
		BULLET_SPEED = _FAST_;
		REPR = _PIAT_;
		DIRECTION = _DOWN_;
		STEEL_ABLE = true;
		MY = false;
		ALIVE = true;
		POS.X = 19;
		POS.Y = 2;
		COOL_DOWN = 3;
		MAP.print_tank(REPR, POS, DIRECTION);
	}
};

Piat PIAT;

class HeavyTank : public EnemyTank {
	friend class Game;
public:
	HeavyTank() {
		ARMOR = 4;
		LIFE = 1;
		DAMAGE = 4;
		MOVEMENT_SPEED = _NORMAL_;
		BULLET_SPEED = _NORMAL_;
		REPR = _HEAVY_;
		DIRECTION = _DOWN_;
		STEEL_ABLE = true;
		MY = false;
		ALIVE = true;
		POS.X = 28;
		POS.Y = 2;
		COOL_DOWN = 3;
	}
	void restart() {
		ARMOR = 4;
		LIFE = 1;
		DAMAGE = 4;
		MOVEMENT_SPEED = _NORMAL_;
		BULLET_SPEED = _NORMAL_;
		REPR = _HEAVY_;
		DIRECTION = _DOWN_;
		STEEL_ABLE = true;
		MY = false;
		ALIVE = true;
		POS.X = 28;
		POS.Y = 2;
		COOL_DOWN = 3;
		MAP.print_tank(REPR, POS, DIRECTION);
	}
};

HeavyTank HEAVY;

void MyTank::eat_bomb() {
	TANKETTE.death_callback();
	AMORED.death_callback();
	PIAT.death_callback();
	HEAVY.death_callback();
}

void Bullet::fly() {
	if (EXIST)
	{
		if (MAP.BOARD[POS.X][POS.Y] >= _BULLET_)
			MAP.clear_bullet(POS);
		if (MAP.BOARD[POS.X][POS.Y] == _WALL_)
			EXIST = false;
		else {
			switch (DIRECTION) {
			case _UP_: {
				(POS.Y)--;
				break;
			}
			case _DOWN_: {
				(POS.Y)++;
				break;
			}
			case _LEFT_: {
				(POS.X)--;
				break;
			}
			case _RIGHT_: {
				(POS.X)++;
				break;
			}
			}
			if (MAP.BOARD[POS.X][POS.Y] == _NULL_)
				MAP.print_bullet(NUMBER, POS);
			else if (MAP.BOARD[POS.X][POS.Y] == _WALL_)
				EXIST = false;
			else
				hit();
		}
	}
}

void Bullet::hit() {
	if (MAP.BOARD[POS.X][POS.Y] == _BRICK_ || MAP.BOARD[POS.X][POS.Y] < _NULL_ || (MAP.BOARD[POS.X][POS.Y] == _STEEL_ && ABLE)) {
		Position temp;
		if (DIRECTION == _UP_ || DIRECTION == _DOWN_) {
			for (int i = -1; i < 2; i++) {
				temp.X = POS.X + i;
				temp.Y = POS.Y;
				if (MAP.BOARD[temp.X][temp.Y] == _BRICK_ || MAP.BOARD[temp.X][temp.Y] == _STEEL_) {
					MAP.BOARD[temp.X][temp.Y] = _NULL_;
					MoveCursor(temp);
					cout << "  ";
				}
				else if (MY && MAP.BOARD[temp.X][temp.Y] == _TANK_) {
					MINE.eat_tank();
					MAP.clear_bullet(temp);
				}
				else if (!MY && MAP.BOARD[temp.X][temp.Y] == _TANK_) {
					switch (OWNER) {
					case _TANKETTE_: {
						TANKETTE.eat_tank();
						break;
					}
					case _AMORED_: {
						AMORED.eat_tank();
						break;
					}
					case _PIAT_: {
						PIAT.eat_tank();
						break;
					}
					case _HEAVY_: {
						HEAVY.eat_tank();
					}
					}
					MAP.clear_bullet(temp);
				}
				else if (MY && MAP.BOARD[temp.X][temp.Y] == _STAR_) {
					MINE.eat_star();
					MAP.clear_bullet(temp);
				}
				else if (!MY && MAP.BOARD[temp.X][temp.Y] == _STAR_) {
					switch (OWNER) {
					case _TANKETTE_: {
						TANKETTE.eat_star();
						break;
					}
					case _AMORED_: {
						AMORED.eat_star();
						break;
					}
					case _PIAT_: {
						PIAT.eat_star();
						break;
					}
					case _HEAVY_: {
						HEAVY.eat_star();
					}
					}
					MAP.clear_bullet(temp);
				}
				else if (MY && MAP.BOARD[temp.X][temp.Y] == _CLOCK_) {
					MINE.eat_clock();
					MAP.clear_bullet(temp);
				}
				else if (!MY && MAP.BOARD[temp.X][temp.Y] == _CLOCK_) {
					TANKETTE.eat_clock();
					MAP.clear_bullet(temp);
				}
				else if (MY && MAP.BOARD[temp.X][temp.Y] == _SHOVEL_) {
					MINE.eat_shovel();
					MAP.clear_bullet(temp);
				}
				else if (!MY && MAP.BOARD[temp.X][temp.Y] == _SHOVEL_) {
					TANKETTE.eat_shovel();
					MAP.clear_bullet(temp);
				}
				else if (MY && MAP.BOARD[temp.X][temp.Y] == _BOMB_) {
					MINE.eat_bomb();
					MAP.clear_bullet(temp);
				}
				else if (!MY && MAP.BOARD[temp.X][temp.Y] == _BOMB_) {
					TANKETTE.eat_bomb();
					MAP.clear_bullet(temp);
				}
			}
		}
		else if (DIRECTION == _LEFT_ || DIRECTION == _RIGHT_) {
			for (int j = -1; j < 2; j++) {
				temp.X = POS.X;
				temp.Y = POS.Y + j;
				if (MAP.BOARD[temp.X][temp.Y] == _BRICK_ || MAP.BOARD[temp.X][temp.Y] == _STEEL_) {
					MAP.BOARD[temp.X][temp.Y] = _NULL_;
					MoveCursor(temp);
					cout << "  ";
				}
				else if (MY && MAP.BOARD[temp.X][temp.Y] == _TANK_) {
					MINE.eat_tank();
					MAP.clear_bullet(temp);
				}
				else if (!MY && MAP.BOARD[temp.X][temp.Y] == _TANK_) {
					switch (OWNER) {
					case _TANKETTE_: {
						TANKETTE.eat_tank();
						break;
					}
					case _AMORED_: {
						AMORED.eat_tank();
						break;
					}
					case _PIAT_: {
						PIAT.eat_tank();
						break;
					}
					case _HEAVY_: {
						HEAVY.eat_tank();
					}
					}
					MAP.clear_bullet(temp);
				}
				else if (MY && MAP.BOARD[temp.X][temp.Y] == _STAR_) {
					MINE.eat_star();
					MAP.clear_bullet(temp);
				}
				else if (!MY && MAP.BOARD[temp.X][temp.Y] == _STAR_) {
					switch (OWNER) {
					case _TANKETTE_: {
						TANKETTE.eat_star();
						break;
					}
					case _AMORED_: {
						AMORED.eat_star();
						break;
					}
					case _PIAT_: {
						PIAT.eat_star();
						break;
					}
					case _HEAVY_: {
						HEAVY.eat_star();
					}
					}
					MAP.clear_bullet(temp);
				}
				else if (MY && MAP.BOARD[temp.X][temp.Y] == _CLOCK_) {
					MINE.eat_clock();
					MAP.clear_bullet(temp);
				}
				else if (!MY && MAP.BOARD[temp.X][temp.Y] == _CLOCK_) {
					TANKETTE.eat_clock();
					MAP.clear_bullet(temp);
				}
				else if (MY && MAP.BOARD[temp.X][temp.Y] == _SHOVEL_) {
					MINE.eat_shovel();
					MAP.clear_bullet(temp);
				}
				else if (!MY && MAP.BOARD[temp.X][temp.Y] == _SHOVEL_) {
					TANKETTE.eat_shovel();
					MAP.clear_bullet(temp);
				}
				else if (MY && MAP.BOARD[temp.X][temp.Y] == _BOMB_) {
					MINE.eat_bomb();
					MAP.clear_bullet(temp);
				}
				else if (!MY && MAP.BOARD[temp.X][temp.Y] == _BOMB_) {
					TANKETTE.eat_bomb();
					MAP.clear_bullet(temp);
				}
			}
		}
		EXIST = false;
	}
	else if (MAP.BOARD[POS.X][POS.Y] == _WALL_ || (MAP.BOARD[POS.X][POS.Y] == _STEEL_ && !ABLE))
		EXIST = false;
	else if (MY && MAP.BOARD[POS.X][POS.Y] >= 2 && MAP.BOARD[POS.X][POS.Y] <= 5) {
		switch (MAP.BOARD[POS.X][POS.Y]) {
		case _TANKETTE_:
			TANKETTE.reduce_armor(DAMAGE);
			break;
		case _AMORED_:
			AMORED.reduce_armor(DAMAGE);
			break;
		case _PIAT_:
			PIAT.reduce_armor(DAMAGE);
			break;
		case _HEAVY_:
			HEAVY.reduce_armor(DAMAGE);
		}
		EXIST = false;
		MAP.SCORE += DAMAGE * 100;
		GetStdHandle(STD_OUTPUT_HANDLE);
		Position InfoPos;
		InfoPos.X = MAP.WIDTH - 10;
		InfoPos.Y = 3;
		MoveCursor(InfoPos);
		cout << "分数: " << MAP.SCORE << "  ";
	}
	else if (!MY && MAP.BOARD[POS.X][POS.Y] == _MY_TANK_) {
		EXIST = false;
		MINE.reduce_armor(DAMAGE);
		MAP.SCORE -= DAMAGE * 100;
		GetStdHandle(STD_OUTPUT_HANDLE);
		Position InfoPos;
		InfoPos.X = MAP.WIDTH - 10;
		InfoPos.Y = 3;
		MoveCursor(InfoPos);
		cout << "分数: " << MAP.SCORE << "  ";
	}
	else if (!MY && MAP.BOARD[POS.X][POS.Y] >= 2 && MAP.BOARD[POS.X][POS.Y] <= 5)
		EXIST = false;
	else if (MAP.BOARD[POS.X][POS.Y] >= _BULLET_) {
		EXIST = false;
		if ((MY && !BULLETS[MAP.BOARD[POS.X][POS.Y] - _BULLET_].MY) ||
			(!MY && BULLETS[MAP.BOARD[POS.X][POS.Y] - _BULLET_].MY)) {
			BULLETS[MAP.BOARD[POS.X][POS.Y] - _BULLET_].EXIST = false;
			MAP.clear_bullet(POS);
		}
	}
	else if (MAP.BOARD[POS.X][POS.Y] == _HOME_) {
		EXIST = false;
		MAP.lose();
	}
}

class Game {
public:
	Game() {}
	void start_up() {
		system("cls");
		srand(time(NULL));
		MAP.set_home();
		MAP.print_map();
		MINE.restart();
		TANKETTE.restart();
		AMORED.restart();
		PIAT.restart();
		HEAVY.restart();
		Tank *T[5];
		T[0] = &MINE;
		T[1] = &TANKETTE;
		T[2] = &AMORED;
		T[3] = &PIAT;
		T[4] = &HEAVY;
		for (long long int i = 0; ; i++) {
			if (MAP.STATUS == _KILLED_)
				raise_game_over();
			else if (MAP.STATUS == _VICTORY_)
				raise_you_win();
			if (!(i % 5)) {
				if (MAP.ENEMY_STOP > 0)
					MAP.ENEMY_STOP -= 1;
				else {
					for (int j = 1; j < 5; j++) {
						if (T[j]->ALIVE)
							T[j]->move();
					}
				}
			}
			if (MAP.ME_STOP > 0)
				MAP.ME_STOP -= 1;
			else
				T[0]->move();
			for (int k = 0; k < COUNT - _BULLET_; k++) {
				if (BULLETS[k].EXIST) {
					for (int c = 0; c < BULLETS[k].SPEED * 2; c++)
						BULLETS[k].fly();
				}
			}
			Sleep(100);
		}
	}
	void raise_game_over() {
		Position Pos;
		Pos.X = 7;
		Pos.Y = 12;
		MoveCursor(Pos);
		cout << "╭─────────────────────────────╮ ";
		Pos.Y += 1;
		MoveCursor(Pos);
		cout << "│                             │ ";
		Pos.Y += 1;
		MoveCursor(Pos);
		cout << "│     GAME OVER! YOU LOSE!    │ " << endl;
		Pos.Y += 1;
		MoveCursor(Pos);
		cout << "│                             │";
		Pos.Y += 1;
		MoveCursor(Pos);
		cout << "╰─────────────────────────────╯ ";
		while (1) {
			if (GetAsyncKeyState(0xD) & 0x8000) {
				start_up();
			}
			else if (GetAsyncKeyState(0x1B) & 0x8000) {
				Pos.X = 0;
				Pos.Y = 32;
				MoveCursor(Pos);
				exit(0);
			}
		}
	}
	void raise_you_win() {
		Position Pos;
		Pos.X = 7;
		Pos.Y = 12;
		MoveCursor(Pos);
		cout << "╭─────────────────────────────╮ ";
		Pos.Y += 1;
		MoveCursor(Pos);
		cout << "│                             │ ";
		Pos.Y += 1;
		MoveCursor(Pos);
		cout << "│     GAME OVER! YOU WIN!     │ " << endl;
		Pos.Y += 1;
		MoveCursor(Pos);
		cout << "│                             │ ";
		Pos.Y += 1;
		MoveCursor(Pos);
		cout << "╰─────────────────────────────╯ ";
		while (1) {
			if (GetAsyncKeyState(0xD) & 0x8000) {
				start_up();
			}
			else if (GetAsyncKeyState(0x1B) & 0x8000) {
				Pos.X = 0;
				Pos.Y = 32;
				MoveCursor(Pos);
				exit(0);
			}
		}
	}
};

int main()
{
	Game GAME;
	GAME.start_up();
	system("cls");
	return 0;
}