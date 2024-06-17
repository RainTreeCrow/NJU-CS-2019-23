#include <iostream>
#include <cstdlib> //用于随机函数
#include <string.h> 
using namespace std;

struct Student{
	char *Name;
	int Age;
	char Sex;
	char *Hometown; //具体到省份
	float Height; 	//单位cm
	
	//题干虽然没有这两个字段，但是这是链表的必要连接点 
	Student *Prior;	//前指针：head 前指针为NULL 
	Student *Next;	//后指针: last 后指针为NULL 
};

//如果非要保留题干内容，也可以考虑在创建一个新的“结点”结构体;
//struct Node
//{
//	Student *Data;
//	Student *Prior;
//	Student *Next;	
//}; 
//将学生信息存放在Data字段内容， Prior 和 Next 做为前后结点的前后指针
//但是这样做的话，就违背了题干中的各个函数的参数类型。
//函数原型就必须是如下格式了 
//CreateList( Node *&head);
//DisplayList( Node *head);
//SortList(Node *head);
//DisplayList(Node *head)；
//DeleteList(Node *head)； 


//由于想偷懒，不愿意再调试的时候输入半天内容，所以我随便找了10个名字和5个家乡，用于随机创建结点 
char *ArrayName[10] = { "Emma", "Edith", "Joyce", "May", "Hailey", "Gloria", "Jessie", "Amanda", "Abby", "Lorraine" };
char *ArrayHometown[5] = { "NanChang", "NanJing", "BeiJing", "ShangHai", "GuangZhou" };	

//检查是否有重名的学生，不是题干中的函数，但是偷懒必须付出的代价 
bool CheckSameName( Student *head, char *Name )
{
	if ( head == NULL )
		return false;
	Student *wStudent = head->Next;
	while( wStudent ) 
	{
		if ( !strcmp( wStudent->Name, Name ) )
		{
			return true; 
		}
			
		wStudent = wStudent->Next;
	}
	return false;
}

void CreateList( Student *&head )
{	
	head = new Student();
	head->Name = "*";
	head->Prior = NULL;	
	//当前即将创建的学生结点 
	Student *wCurrent;
	//当前学生的前一结点 
	Student *wPrior = head;	
	
	//创建10个学生信息
	for( int i=0; i<10; i++ ) 
	{
		//开始创建学生信息(输入这么多内容，很难看到测试效果）
		wCurrent = new Student; 
		wCurrent->Name = new char[30];	//名字长度最多30位，这个可以自己随意定义 
		wCurrent->Hometown = new char[30];	//籍贯长度最多30位， 
		//cin >> Current->Name >> Current->Age >> Current->Sex >> Current->Hometown >> Current->Height;
		//所以还是决定偷个懒~哈哈
		//这大括号圈出的范围就是偷懒的代价，你可以用作参考，特别是循环检查重名的部分~ 
		{
			int wPos = rand()%10;
			int wIndex = wPos; 

			bool wFind = true; 
			while( CheckSameName( head, ArrayName[ wIndex ] ) ) 
			{
				wIndex ++;
				if ( wIndex > 9 )
					wIndex = 0;
				if ( wIndex == wPos )
				{
					//找了一圈了没找到可用的名字，所以取个名字叫“NULL”
					strcpy( wCurrent->Name, "NULL" );
					wFind = false;
					break; 
				}
			}
			if ( wFind )
			{
				strcpy( wCurrent->Name , ArrayName[ wIndex ] );
			}
			wCurrent->Age = 20 + rand()%5;	//年龄都在20到24左右 
			wCurrent->Height = 165 + rand()%10;	//身高165以上，都是大长腿~ 
			strcpy( wCurrent->Hometown , ArrayHometown[ rand()%5 ] );
			if( rand()%2 == 0 )
				wCurrent->Sex = 'W'; 
			else
				wCurrent->Sex = 'M';
		}
		
		//以下四行是链表的组成关键点 
		wCurrent->Prior = wPrior;
		wCurrent->Next = NULL;
		wPrior->Next = wCurrent;
		wPrior = wCurrent;

		wCurrent = NULL; 
	}
	
}

void DisplayList( Student *head )
{
	if ( head == NULL )
	{
		cout << "链表还没有创建，无法打印学生信息。" << endl;
		return;
	}
	
	//画一下张表来显摆一下，哈哈~ 
	cout << "----------------------------------------------------------" << endl;
	cout << "--                    学生基本信息表                    --" << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "--姓名\t\t年龄\t性别\t籍贯\t\t身高    --" << endl;

	Student *wStudent = head->Next;
	while( wStudent ) 
	{
		cout << "--" << wStudent->Name;
		if ( strlen( wStudent->Name )+2 >= 8 )
			cout << "\t";
		else
			cout << "\t\t";	
		 
		cout << wStudent->Age << "\t" << wStudent->Sex << "\t" << wStudent->Hometown;
		if ( strlen( wStudent->Hometown ) >= 8 )
			cout << "\t";
		else
			cout << "\t\t";	
		cout << wStudent->Height << "(CM) --" << endl;	
		wStudent = wStudent->Next;
	}
	cout << "----------------------------------------------------------" << endl;
} 

void SortList( Student *head )
{
	if ( head == NULL )
	{
		cout << "链表还没有创建，无法打印对学生姓名进行排序。" << endl;
		return;
	}
	Student *wPoint = head;
	Student *wStudent;
	char wBuffer[30];	//暂存空间 
	while( wPoint )
	{
		wStudent = wPoint->Next;
		while( wStudent )
		{
			if( strcmp( wStudent->Name, wPoint->Name ) < 0 )
			{
				//开始交换结点内容方式
				
				//交换结点姓名 
				strcpy( wBuffer, wStudent->Name );
				strcpy( wStudent->Name, wPoint->Name );
				strcpy( wPoint->Name, wBuffer );
				//交换年龄
				int wAge = wStudent->Age;
				wStudent->Age = wPoint->Age;
				wPoint->Age = wAge; 
				//交换性别
				char wSex = wStudent->Sex;
				wStudent->Sex = wPoint->Sex;
				wPoint->Sex = wSex; 
				//交换籍贯 
				strcpy( wBuffer, wStudent->Hometown );
				strcpy( wStudent->Hometown, wPoint->Hometown );
				strcpy( wPoint->Hometown, wBuffer );
				//交换身高 
				int wHeight = wStudent->Height;
				wStudent->Height = wPoint->Height;
				wPoint->Height = wHeight; 
			}
			wStudent = wStudent->Next;
		}
		wPoint = wPoint->Next;	
	}	
}

void DeleteList( Student *head )
{
	if ( head == NULL )
	{
		cout << "链表还没有创建，无法执行删除函数。" << endl;
		return;
	}
	
	Student *wNext;
	Student *wStudent = head;	
	while( wStudent )
	{
		//在自释放之前先找好下家~ 
		wNext = wStudent->Next;
	 	
		//释放姓名和籍贯两格字段
		delete []wStudent->Name;
		delete []wStudent->Hometown;
		
		//断开与前、后结点的连接
		wStudent->Prior = NULL;
		wStudent->Next = NULL;	 

		//自释放 
		delete wStudent;
		
		//下家准备自释放 
		wStudent = wNext; 
	}
}

int main( int argc, char** argv )
{
	//创建链表起点 
	Student *whead = NULL;
	cout << "开始创建学生链表：执行CreateList" <<endl;
	CreateList( whead );
	cout << "开始打印学生信息表：执行DisplayList" <<endl;
	DisplayList( whead );
	cout << "开始按姓名排序：执行SortList..." <<endl;
	SortList( whead );
	cout << "按姓名排序后的结果：执行SortList..." <<endl;
	DisplayList( whead );
	cout << "最后删除链表：执行DeleteList..." <<endl;
	DeleteList( whead ); 
} 