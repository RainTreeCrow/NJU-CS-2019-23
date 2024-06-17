#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<dos.h>
#include<conio.h>
#include<assert.h>

struct Node
{
	int quantity;
	struct Node* next;
};

struct grid
{
	int sick;
	int infected;
	int susceptible;
	int cured;
	int dead;
	int isolated;
	struct Node* headsick;
	struct Node* headinfected;
	struct Node* headsusceptible;
	struct Node* headcured;

};

struct individual
{
	int px;
	int py;
	int state;					//病人1；感染者2；易感者3；治愈者4；死者5；隔离6；
	int latentperiod;			//潜伏期
	int	dayfrominf;				//感染至今的天数
	int dayfromill;				//发病至今的天数
};

#define population 50000			//总人口
struct grid map[51][51];
struct individual crowd[population];
int patient = 0;					//患病人数
int carrier = 0;					//携带者人数
int isolate = 0;					//隔离人数
const int DayContact = 1;			//日接触人数（周围几圈）
const float InfRate = 0.006;			//感染率
const float InfRateI = 0.003;		//携带者的感染率
const int MoveRangeH = 3;			//非患者的活动范围
const float CureRate = 0.01;		    //治愈率
const int bed = 1000;				//医院床位
const int HosRecTime = 10;			//医院反应时间


void Initialize(void);
void Spread(void);
void Deteriorate(void);
void Print(void);
void Cure(void);
void SpreadInfected(void);
void Move(void);
void Isolation(void);

int main()
{
	Initialize();
	Print();
	system("pause");
	for (int day = 0; day < 1000; day++)
	{
		SpreadInfected();
		for (int moves = 0; moves < 2; moves++)
		{
			
			Move();
			SpreadInfected();
		}
		

		Spread();
		//Print();
		Deteriorate();
		Cure();
		Isolation();

		
		Print();
		printf("第%d天\t", day);
		//if (day % 15==0)
			//system("pause");
		if ((patient == 0&&carrier==0) || patient == population)
			return 0;
	}

	return 0;
}

void Initialize(void)
{
	for (int i = 1; i < 51; i++)
	{
		for (int j = 1; j < 51; j++)
		{
			struct Node* headsick;
			struct Node* headinfected;
			struct Node* headsusceptible;
			struct Node* headcured;
		}
	}




	srand(time(NULL));
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			map[i][j].sick = 0;
			map[i][j].infected = 0;
			map[i][j].susceptible = 0;
			map[i][j].cured = 0;
			map[i][j].dead = 0;
		}
	}
	int ran1 = 22;//(rand() % 46) + 1;			//1-46
	int ran2 = 22;//(rand() % 46) + 1;
	for (int k = 0; k < population; k++)
	{
		//srand(time(NULL));
		crowd[k].px = rand() % 50 + 1;
		crowd[k].py = rand() % 50 + 1;

		if (crowd[k].px >= ran1&&crowd[k].px <= ran1 + 6 && crowd[k].py >= ran2&&crowd[k].py <= ran2 + 6)
			crowd[k].state = 3 - 2 * (rand() % 2)* (rand() % 2)*(rand() % 2)* (rand() % 2)* (rand() % 2);
		//crowd[k].state = 3 - 2 * (rand() % 2)* (rand() % 2)* (rand() % 2)* (rand() % 2)* (rand() % 2)* (rand() % 2)* ;
		else crowd[k].state = 3;
		crowd[k].dayfrominf = 0;
		crowd[k].latentperiod = rand() % 4 + 7;

		if (crowd[k].state == 1)
		{
			map[crowd[k].px][crowd[k].py].sick++;
			patient++;
		}
		else
			map[crowd[k].px][crowd[k].py].susceptible++;
	
	}
}

void Spread(void)
{

	for (int i = 1; i < 51; i++)
	{
		for (int j = 1; j < 51; j++)
		{
			if (map[i][j].sick != 0)							//先考虑感染者不会传染
			{
				float hearate = 1.0;
				for (int k = 0; k < map[i][j].sick; k++)
				{
					hearate *= (1.0 - InfRate);
				}
				hearate *= 10000;
				
				for (int k = 0; k < population; k++)
				{
					if ((abs(crowd[k].px - i) <= DayContact) && (abs(crowd[k].py - j) <= DayContact) && crowd[k].state == 3)
					{
						int ran = rand() % 10000;
						if (hearate > ran)
							ran = 0;
						else
							ran = 1;

						crowd[k].state = 3 - ran;
						//crowd[k].state = 2;
						if (crowd[k].state == 2)
						{
							map[crowd[k].px][crowd[k].py].infected++;
							carrier++;
						}
					}
				}
			}

			
		}
	}
}

void SpreadInfected(void)			//感染者的传播
{
	srand(time(NULL));
	for (int i = 1; i < 51; i++)
	{
		for (int j = 1; j < 51; j++)
		{

			if (map[i][j].infected != 0)
			{
				float hearate = 1.0;
				for (int k = 0; k < map[i][j].infected; k++)
				{
					hearate *= (1 - InfRateI);
				}
				hearate *= 100000;

				for (int k = 0; k < population; k++)
				{
					if ((abs(crowd[k].px - i) <= DayContact) && (abs(crowd[k].py - j) <= DayContact) && crowd[k].state == 3)
					{
						int ran = rand() % 100000;
						if (hearate > ran)
							ran = 0;
						else
							ran = 1;

						crowd[k].state = 3 - ran;
						if (crowd[k].state == 2)
						{
							map[crowd[k].px][crowd[k].py].infected++;
							carrier++;
						}
					}
				}
			}


		}
	}

}


void Deteriorate(void)
{
	for (int k = 0; k < population; k++)
	{
		if (crowd[k].state == 2)
		{
			crowd[k].dayfrominf++;
			if (crowd[k].latentperiod == crowd[k].dayfrominf)
			{
				crowd[k].state = 1;
				map[crowd[k].px][crowd[k].py].sick++;
				map[crowd[k].px][crowd[k].py].infected--;
				patient++;
				carrier--;

			}
		}
		if (crowd[k].state == 1)
		{
			crowd[k].dayfromill++;
		}
	}
}

void Cure(void)
{
	srand(time(NULL));
	for (int k = 0; k < population; k++)
	{	
		if (crowd[k].state == 6)
		{
			
			int ran = rand() % 1000;
			if (ran > CureRate * 1000)
				ran = 0;
			else
				ran = 1;
			crowd[k].state = 6 - 2 * ran;
			if (crowd[k].state == 4)
			{
				map[crowd[k].px][crowd[k].py].cured++;
				map[crowd[k].px][crowd[k].py].isolated--;
				patient--;
				isolate--;
			}
		}
	}

}

void Move(void)
{
	srand(time(NULL));
	for (int k = 0; k < population; k++)
	{
		if (crowd[k].state != 5 && crowd[k].state != 6)
		{
			if (rand() % 2)
			{
				int movex = (rand() % MoveRangeH)-2;
				int movey = (rand() % MoveRangeH)-2;
				if (crowd[k].state == 2)
					map[crowd[k].px][crowd[k].py].infected--;
				else if (crowd[k].state == 3)
					map[crowd[k].px][crowd[k].py].susceptible--;
				else if (crowd[k].state == 1)
					map[crowd[k].px][crowd[k].py].sick--;
				else
					map[crowd[k].px][crowd[k].py].cured--;
				
				crowd[k].px = (crowd[k].px + movex) % 51;
				if (crowd[k].px < 1)
					crowd[k].px += 50;
				crowd[k].py = (crowd[k].py + movey) % 51;
				if (crowd[k].py < 1)
					crowd[k].py += 50;

				if (crowd[k].state == 2)
					map[crowd[k].px][crowd[k].py].infected++;
				else if (crowd[k].state == 3)
					map[crowd[k].px][crowd[k].py].susceptible++;
				else if (crowd[k].state == 1)
					map[crowd[k].px][crowd[k].py].sick++;
				else
					map[crowd[k].px][crowd[k].py].cured++;
			}
		}
	}
}

void Isolation(void)
{
	for (int k = 0; k < population; k++)
	{
		if (crowd[k].state == 1 && crowd[k].dayfromill >= HosRecTime&&isolate<bed)
		{
			crowd[k].state = 6;
			map[crowd[k].px][crowd[k].py].sick--;
			map[crowd[k].px][crowd[k].py].isolated++;
			isolate++;
		}

	}



}

void Print(void)
{
	system("cls");
	printf("患病率%.4f%%\t",(float)(patient+isolate)/population*100);
	printf("感染率%.4f%%\t", (float)(patient + carrier+isolate) / population * 100);
	printf("隔离人数%d\n", isolate);
	for (int i = 1; i < 51; i++)
	{
		for (int j = 1; j < 51; j++)
		{
			if (map[i][j].sick >= 1)
			{
				printf("\033[41;32;5m%d\033[0m ", map[i][j].sick);
				if (map[i][j].sick < 10)
					printf(" ");
			}
			else if (map[i][j].infected >= 1)
			{
				printf("\033[43;35;5m%d\033[0m ", map[i][j].infected);		//printf("\033[43;35;5m%d\033[0m ", map[i][j].sugar);
				if (map[i][j].infected < 10)
					printf(" ");
			}
			else
			{
				printf("0  ");
			}
		}
		printf("\n");
		
	}
	//system("pause");
}

struct Node *InsCreate(struct Node *head,int i)
{
		struct Node *p = (struct Node *)malloc(sizeof(struct Node));
		p->quantity = i;
		p->next = head;
		head = p;
	
}