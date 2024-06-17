#include <iostream>
#include <cstdlib> //�����������
#include <string.h> 
using namespace std;

struct Student{
	char *Name;
	int Age;
	char Sex;
	char *Hometown; //���嵽ʡ��
	float Height; 	//��λcm
	
	//�����Ȼû���������ֶΣ�������������ı�Ҫ���ӵ� 
	Student *Prior;	//ǰָ�룺head ǰָ��ΪNULL 
	Student *Next;	//��ָ��: last ��ָ��ΪNULL 
};

//�����Ҫ����������ݣ�Ҳ���Կ����ڴ���һ���µġ���㡱�ṹ��;
//struct Node
//{
//	Student *Data;
//	Student *Prior;
//	Student *Next;	
//}; 
//��ѧ����Ϣ�����Data�ֶ����ݣ� Prior �� Next ��Ϊǰ�����ǰ��ָ��
//�����������Ļ�����Υ��������еĸ��������Ĳ������͡�
//����ԭ�;ͱ��������¸�ʽ�� 
//CreateList( Node *&head);
//DisplayList( Node *head);
//SortList(Node *head);
//DisplayList(Node *head)��
//DeleteList(Node *head)�� 


//������͵������Ը���ٵ��Ե�ʱ������������ݣ��������������10�����ֺ�5�����磬�������������� 
char *ArrayName[10] = { "Emma", "Edith", "Joyce", "May", "Hailey", "Gloria", "Jessie", "Amanda", "Abby", "Lorraine" };
char *ArrayHometown[5] = { "NanChang", "NanJing", "BeiJing", "ShangHai", "GuangZhou" };	

//����Ƿ���������ѧ������������еĺ���������͵�����븶���Ĵ��� 
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
	//��ǰ����������ѧ����� 
	Student *wCurrent;
	//��ǰѧ����ǰһ��� 
	Student *wPrior = head;	
	
	//����10��ѧ����Ϣ
	for( int i=0; i<10; i++ ) 
	{
		//��ʼ����ѧ����Ϣ(������ô�����ݣ����ѿ�������Ч����
		wCurrent = new Student; 
		wCurrent->Name = new char[30];	//���ֳ������30λ����������Լ����ⶨ�� 
		wCurrent->Hometown = new char[30];	//���᳤�����30λ�� 
		//cin >> Current->Name >> Current->Age >> Current->Sex >> Current->Hometown >> Current->Height;
		//���Ի��Ǿ���͵����~����
		//�������Ȧ���ķ�Χ����͵���Ĵ��ۣ�����������ο����ر���ѭ����������Ĳ���~ 
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
					//����һȦ��û�ҵ����õ����֣�����ȡ�����ֽС�NULL��
					strcpy( wCurrent->Name, "NULL" );
					wFind = false;
					break; 
				}
			}
			if ( wFind )
			{
				strcpy( wCurrent->Name , ArrayName[ wIndex ] );
			}
			wCurrent->Age = 20 + rand()%5;	//���䶼��20��24���� 
			wCurrent->Height = 165 + rand()%10;	//���165���ϣ����Ǵ���~ 
			strcpy( wCurrent->Hometown , ArrayHometown[ rand()%5 ] );
			if( rand()%2 == 0 )
				wCurrent->Sex = 'W'; 
			else
				wCurrent->Sex = 'M';
		}
		
		//�����������������ɹؼ��� 
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
		cout << "����û�д������޷���ӡѧ����Ϣ��" << endl;
		return;
	}
	
	//��һ���ű����԰�һ�£�����~ 
	cout << "----------------------------------------------------------" << endl;
	cout << "--                    ѧ��������Ϣ��                    --" << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "--����\t\t����\t�Ա�\t����\t\t���    --" << endl;

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
		cout << "����û�д������޷���ӡ��ѧ��������������" << endl;
		return;
	}
	Student *wPoint = head;
	Student *wStudent;
	char wBuffer[30];	//�ݴ�ռ� 
	while( wPoint )
	{
		wStudent = wPoint->Next;
		while( wStudent )
		{
			if( strcmp( wStudent->Name, wPoint->Name ) < 0 )
			{
				//��ʼ����������ݷ�ʽ
				
				//����������� 
				strcpy( wBuffer, wStudent->Name );
				strcpy( wStudent->Name, wPoint->Name );
				strcpy( wPoint->Name, wBuffer );
				//��������
				int wAge = wStudent->Age;
				wStudent->Age = wPoint->Age;
				wPoint->Age = wAge; 
				//�����Ա�
				char wSex = wStudent->Sex;
				wStudent->Sex = wPoint->Sex;
				wPoint->Sex = wSex; 
				//�������� 
				strcpy( wBuffer, wStudent->Hometown );
				strcpy( wStudent->Hometown, wPoint->Hometown );
				strcpy( wPoint->Hometown, wBuffer );
				//������� 
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
		cout << "����û�д������޷�ִ��ɾ��������" << endl;
		return;
	}
	
	Student *wNext;
	Student *wStudent = head;	
	while( wStudent )
	{
		//�����ͷ�֮ǰ���Һ��¼�~ 
		wNext = wStudent->Next;
	 	
		//�ͷ������ͼ��������ֶ�
		delete []wStudent->Name;
		delete []wStudent->Hometown;
		
		//�Ͽ���ǰ�����������
		wStudent->Prior = NULL;
		wStudent->Next = NULL;	 

		//���ͷ� 
		delete wStudent;
		
		//�¼�׼�����ͷ� 
		wStudent = wNext; 
	}
}

int main( int argc, char** argv )
{
	//����������� 
	Student *whead = NULL;
	cout << "��ʼ����ѧ������ִ��CreateList" <<endl;
	CreateList( whead );
	cout << "��ʼ��ӡѧ����Ϣ��ִ��DisplayList" <<endl;
	DisplayList( whead );
	cout << "��ʼ����������ִ��SortList..." <<endl;
	SortList( whead );
	cout << "�����������Ľ����ִ��SortList..." <<endl;
	DisplayList( whead );
	cout << "���ɾ������ִ��DeleteList..." <<endl;
	DeleteList( whead ); 
} 