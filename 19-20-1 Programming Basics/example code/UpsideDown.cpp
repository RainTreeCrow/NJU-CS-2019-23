#include <iostream>
#include <cstdlib> //用于随机函数
#include <string.h> 
using namespace std;

struct Link{

	int Data;

	//题干虽然没有这两个字段，但是这是链表的必要连接点 
	Link *Prior;	//前指针：head 前指针为NULL 
	Link *Next;	//后指针: last 后指针为NULL 
};

void CreateList( Link *&Head, int Length )
{	
	Head = new Link();
	Head->Data = -1;
	Head->Prior = NULL;	

	Link *wCurrent;
	Link *wPrior = Head;	
	
	for( int i=0; i<Length; i++ ) 
	{

		wCurrent = new Link; 
		wCurrent->Data = rand()%50;
		
		//以下四行是链表的组成关键点 
		wCurrent->Prior = wPrior;
		wCurrent->Next = NULL;
		wPrior->Next = wCurrent;
		wPrior = wCurrent;

		wCurrent = NULL; 
	}
	
}

void DisplayList( Link *Head )
{
	if ( Head == NULL )
	{
		cout << "链表还没有创建！" << endl;
		return;
	}

	Link *wPoint = Head->Next;
	while( wPoint ) 
	{
		cout << wPoint->Data << " ";
		wPoint = wPoint->Next;
	}
	cout << endl;
} 

// 通过指针方式调换链表
void UpsideDownByPoint( Link *Head, int Start, int End )
{
	if ( Start > End )
	{
		cout << "起始位置大于结束位置，无法颠倒排序。" << endl;
		return;
	}	
	
	Link *wStart = NULL; //起始位置的链表指针
	Link *wEnd = NULL;   //结束位置的链表指针

	//开始根据位置编号定位起始位置和结束位置的指针
	int wIndex = 1;
		
	Link *wPoint = Head->Next;
	while( wPoint ) 
	{
		if ( wIndex ==  Start )
			wStart = wPoint;

		if ( wIndex == End )
			wEnd = wPoint;

		wPoint = wPoint->Next;
		wIndex ++;
	}
	
	if( wStart == NULL || wEnd == NULL )
	{
		cout << "起始位置或结束位置超出链表范围，无法颠倒排序。" << endl;
		return;
	} 
	
	//确定颠倒区域的前后位置
	Link *wStartPrior = wStart->Prior;
	Link *wEndNext  = wEnd->Next;
	
	//开始颠倒处理
	wPoint = wStart->Next;
	
	//首部切换
	if ( wEndNext != NULL )
		wEndNext->Prior = wStart;
	wStart->Next = wEndNext;
	
	//内部切换
	Link *wNext;
	while( wPoint ) 
	{
		//区域内指针切换
		wStart->Prior = wPoint;
		wNext  = wPoint->Next;
		wPoint->Next = wStart;
		
			
		wStart = wPoint;
		wPoint = wNext; 
		
		if ( wStart == wEnd )
			break;

	}
	
	//尾部切换
	wStartPrior->Next = wEnd;
	wEnd->Prior = wStartPrior;

}

// 通过数据域方式调换链表
void UpsideDownByData( Link *Head, int Start, int End )
{
	if ( Start > End )
	{
		cout << "起始位置大于结束位置，无法颠倒排序。" << endl;
		return;
	}	
	
	Link *wStart; //起始位置的链表指针
	Link *wEnd;   //结束位置的链表指针

	//开始根据位置编号定位起始位置和结束位置的指针
	int wIndex = 1;
		
	Link *wPoint = Head->Next;
	while( wPoint ) 
	{
		if ( wIndex ==  Start )
			wStart = wPoint;

		if ( wIndex == End )
			wEnd = wPoint;

		wPoint = wPoint->Next;
		wIndex ++;
	}
	
	if( wStart == NULL || wEnd == NULL )
	{
		cout << "起始位置或结束位置超出链表范围，无法颠倒排序。" << endl;
		return;
	} 
	
	
	while( wStart != wEnd && wStart->Prior != wEnd ) 
	{
		int wBuff = wStart->Data;
		wStart->Data = wEnd->Data;
		wEnd->Data = wBuff;

		wStart = wStart->Next;
		wEnd = wEnd->Prior;
	}
	
}


void DeleteList( Link *head )
{
	if ( head == NULL )
	{
		cout << "链表还没有创建，无法执行删除函数。" << endl;
		return;
	}
	
	Link *wNext;
	Link *wPoint = head;	
	while( wPoint )
	{
		//在自释放之前先找好下家~ 
		wNext = wPoint->Next;
		
		//断开与前、后结点的连接
		wPoint->Prior = NULL;
		wPoint->Next = NULL;	 

		//自释放 
		delete wPoint;
		
		//下家准备自释放 
		wPoint = wNext; 
	}
}

int main( int argc, char** argv )
{
	
	int Length, Start, End;
	cout << "按题目要求输入信息，链表长度、起始位置、结束位置：" <<endl;
	cin >> Length >> Start >> End;
	if ( Start > Length || End > Length )
	{
		cout << "起始位置或者结束位置超出链表长度，输入错误！" << endl;
		return 0;
	} 
	 
	Link *whead = NULL;
	cout << "开始创建链表..." <<endl;
	CreateList( whead, Length );
	cout << "链表内容：" <<endl;
	DisplayList( whead );
	cout << "指针切换方式全表颠倒：" <<endl;
	UpsideDownByPoint( whead, 1, Length );
	DisplayList( whead );
	cout << "数据切换方式内部颠倒：" <<endl;
	UpsideDownByData( whead, Start, End );
	DisplayList( whead );
	cout << "最后删除链表,释放指针." <<endl;
	DeleteList( whead ); 
} 
