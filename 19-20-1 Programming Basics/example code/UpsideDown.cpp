#include <iostream>
#include <cstdlib> //�����������
#include <string.h> 
using namespace std;

struct Link{

	int Data;

	//�����Ȼû���������ֶΣ�������������ı�Ҫ���ӵ� 
	Link *Prior;	//ǰָ�룺head ǰָ��ΪNULL 
	Link *Next;	//��ָ��: last ��ָ��ΪNULL 
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
		
		//�����������������ɹؼ��� 
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
		cout << "����û�д�����" << endl;
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

// ͨ��ָ�뷽ʽ��������
void UpsideDownByPoint( Link *Head, int Start, int End )
{
	if ( Start > End )
	{
		cout << "��ʼλ�ô��ڽ���λ�ã��޷��ߵ�����" << endl;
		return;
	}	
	
	Link *wStart = NULL; //��ʼλ�õ�����ָ��
	Link *wEnd = NULL;   //����λ�õ�����ָ��

	//��ʼ����λ�ñ�Ŷ�λ��ʼλ�úͽ���λ�õ�ָ��
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
		cout << "��ʼλ�û����λ�ó�������Χ���޷��ߵ�����" << endl;
		return;
	} 
	
	//ȷ���ߵ������ǰ��λ��
	Link *wStartPrior = wStart->Prior;
	Link *wEndNext  = wEnd->Next;
	
	//��ʼ�ߵ�����
	wPoint = wStart->Next;
	
	//�ײ��л�
	if ( wEndNext != NULL )
		wEndNext->Prior = wStart;
	wStart->Next = wEndNext;
	
	//�ڲ��л�
	Link *wNext;
	while( wPoint ) 
	{
		//������ָ���л�
		wStart->Prior = wPoint;
		wNext  = wPoint->Next;
		wPoint->Next = wStart;
		
			
		wStart = wPoint;
		wPoint = wNext; 
		
		if ( wStart == wEnd )
			break;

	}
	
	//β���л�
	wStartPrior->Next = wEnd;
	wEnd->Prior = wStartPrior;

}

// ͨ��������ʽ��������
void UpsideDownByData( Link *Head, int Start, int End )
{
	if ( Start > End )
	{
		cout << "��ʼλ�ô��ڽ���λ�ã��޷��ߵ�����" << endl;
		return;
	}	
	
	Link *wStart; //��ʼλ�õ�����ָ��
	Link *wEnd;   //����λ�õ�����ָ��

	//��ʼ����λ�ñ�Ŷ�λ��ʼλ�úͽ���λ�õ�ָ��
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
		cout << "��ʼλ�û����λ�ó�������Χ���޷��ߵ�����" << endl;
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
		cout << "����û�д������޷�ִ��ɾ��������" << endl;
		return;
	}
	
	Link *wNext;
	Link *wPoint = head;	
	while( wPoint )
	{
		//�����ͷ�֮ǰ���Һ��¼�~ 
		wNext = wPoint->Next;
		
		//�Ͽ���ǰ�����������
		wPoint->Prior = NULL;
		wPoint->Next = NULL;	 

		//���ͷ� 
		delete wPoint;
		
		//�¼�׼�����ͷ� 
		wPoint = wNext; 
	}
}

int main( int argc, char** argv )
{
	
	int Length, Start, End;
	cout << "����ĿҪ��������Ϣ�������ȡ���ʼλ�á�����λ�ã�" <<endl;
	cin >> Length >> Start >> End;
	if ( Start > Length || End > Length )
	{
		cout << "��ʼλ�û��߽���λ�ó��������ȣ��������" << endl;
		return 0;
	} 
	 
	Link *whead = NULL;
	cout << "��ʼ��������..." <<endl;
	CreateList( whead, Length );
	cout << "�������ݣ�" <<endl;
	DisplayList( whead );
	cout << "ָ���л���ʽȫ��ߵ���" <<endl;
	UpsideDownByPoint( whead, 1, Length );
	DisplayList( whead );
	cout << "�����л���ʽ�ڲ��ߵ���" <<endl;
	UpsideDownByData( whead, Start, End );
	DisplayList( whead );
	cout << "���ɾ������,�ͷ�ָ��." <<endl;
	DeleteList( whead ); 
} 
