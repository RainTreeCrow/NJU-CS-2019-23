#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

#include "Expression.h"

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct Position{
	int X;
	int Y;
};

void MoveCursor( Position pos )	//���ù��λ��(���������ʾ�Ŀ�ʼλ��)
{
	COORD Pos = { pos.X*2, pos.Y };
	HANDLE OutPutHandle = GetStdHandle( STD_OUTPUT_HANDLE );//��ñ�׼����ľ��   
	SetConsoleCursorPosition( OutPutHandle, Pos ); //���ù��λ��
}

void Menu( int Width, int Height ){
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	for ( int w=0; w < (Width-6); w++ )
		cout<<"=";
	cout<<"����ʽ�����";
	for ( int w=0; w < (Width-6); w++ )
		cout<<"=";
	cout << endl<<endl;
	cout << "     1:����  2:�������  3:����Ԫ  4:����(ȡģ)����  5:���  6:�鿴  0:�˳�"<<endl;
	for ( int w=0; w < Width*2; w++ )
		cout<<"=";
	cout << endl;	
}

bool Cover( int Width, int Height ){
	
	Menu( Width, Height ); 
	
	Position AboutInfoPos;
	AboutInfoPos.X = (Width-2)/2-4;
	AboutInfoPos.Y = Height/2-6;
	MoveCursor( AboutInfoPos );
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);	//���ú�ɫ
	cout<<"������ʽ���������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	
	AboutInfoPos.X = (Width-2)/2-2;
	AboutInfoPos.Y = Height/2-2;
	MoveCursor( AboutInfoPos );
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);	//���ú�ɫ
	cout<<"���ߣ��ź�֮";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	
	AboutInfoPos.X = (Width-2)/2-2;
	AboutInfoPos.Y = Height/2;
	MoveCursor( AboutInfoPos );
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);	//������ɫ
	cout<<"ѧ��: 191220154";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	
	AboutInfoPos.X = (Width-2)/2-2;
	AboutInfoPos.Y = Height/2+4;
	MoveCursor( AboutInfoPos );
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );	//����һ����ɫ 
	cout<<"�ûس�������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	
	AboutInfoPos.X = (Width-2)/2-2;
	AboutInfoPos.Y = Height/2+6;
	MoveCursor( AboutInfoPos );
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );	//����һ����ɫ 
	cout<<"��ESC���˳� ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	
	while(1){
		if( GetAsyncKeyState(VK_RETURN) && 0x0D ){
		//	for( int i=0; i<200000000; i++ );
			return true;
		}else if( GetAsyncKeyState(VK_ESCAPE) && 0x1B ){ 
			return false;
		}	
	} 
}


int main(int argc, char** argv) {
	
	bool isEntry = Cover(40,24);
	int Option = 0;			//������Ŀ 
	int PolyonmialLength;	//����ʽ���� 
	float Coefficients[50];		//ϵ���ַ���
	Polynomial polynomials[26];	//26����ĸ��ÿ����ĸ��Ϊһ�����Ӧ�ù�����

	char FunctionName; 
	if( isEntry ){
		Menu( 40, 24 );
		while(1){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			cout << "��ѡ��";
			cin >> Option;
			while(cin.fail())
			{
				cin.clear();
				cin.ignore();
				cout << "���빦��ѡ�����������ѡ��:"<<endl;
				cin >> Option;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			if ( Option == 1 ){
				cout<< "����ʽ����:";
				cin >> PolyonmialLength;
				while(cin.fail())
				{
					cin.clear();
					cin.ignore();
					cout << "�������ʽ���ȴ�������������:"<<endl;
					cin >> PolyonmialLength;
				}
				
				for( int i=0; i<50; i++ )
					Coefficients[i] = 0;
				
				cout<< "������ϵ��:"<<endl; 
				for( int i=PolyonmialLength-1; i>=0; i--){
					cin >> Coefficients[i];
					while(cin.fail())
					{
						cin.clear();
						cin.ignore();
						cout << "�����"<<PolyonmialLength-i<<"��ϵ����������������:"<<endl;
						cin >> Coefficients[i];
					}
				}
				cout<< "���������ʽ����A~F(�ظ����ƽ�������):"; 
				do{
					cin >> FunctionName;
					if( FunctionName<65 || FunctionName>90 )
						cout<<"����ʽ���ƴ���������A~F(�ظ����ƽ�������):"<<endl;
				} 
				while( FunctionName<65 || FunctionName>90 );	//�������Ʋ���26����д��ĸ��Χ������������ 
				
				bool Find = false;
				for ( int i=0; i<26; i++ ){
					if ( polynomials[i].Nameis( FunctionName ) )
					{
						polynomials[i].Initialization( FunctionName, PolyonmialLength, Coefficients );
						Find = true;
						break;
					}	
				}
				
				if( !Find ){
					for ( int i=0; i<26; i++ ){
						if ( polynomials[i].IsNull() )
						{
							polynomials[i].Initialization( FunctionName, PolyonmialLength, Coefficients );
							break;
						}	
					}
				}
			}else if( Option == 2 ){
				Expression Exp;
				for( int i=0; i<26; i++ ){
					//cout <<"Line = "<<__LINE__<<endl;
					Exp.polynomials[i] = polynomials[i];
				}
				char ExpressionStr[128];	//128λ���ʽ���ȣ��㹻����һ������ı��ʽ��
				char Entry = 'Y';
				while( Entry == 'Y' || Entry == 'y' ) 
				{
					cout<< "��������ʽ(���ű�ʶ: ��:*!; ������:$[l,h]; ��:+; ��:-; ��:* ):"<<endl;
					memset( ExpressionStr, 0x00, sizeof(ExpressionStr) );
					cin>> ExpressionStr;
					Token *Root = Exp.Analysis( ExpressionStr );
					if( NULL == Root ){
						cout<<"������ʽ����"<<endl;
					}
					else{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );
						cout<<"���ʽ��";
						Exp.Print( Root );
						Polynomial poly = Exp.Execute( Root );
						
						if( !poly.IsNull() ){
							cout<<" = ";
							poly.Print();
						}
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
						Exp.Free( Root );
					}
					cout<<"�Ƿ��������(Y/N):";
					cin >> Entry;
				}
			}else if( Option == 3 ){
				bool Find = false;
				cout<< "���������ʽ����:";
				cin>> FunctionName;

				for ( int i=0; i<26; i++ ){
					if ( polynomials[i].Nameis( FunctionName ) )
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );
						cout << "��ԪΪ: "<<FunctionName<<"^-1 = ";
						polynomials[i].Inverse().Print();
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
						Find = true; 
						break;
					}	
				}
				if( !Find ){
					cout<< "����ʽ["<<FunctionName<<"]������."<<endl; 
				}
			}else if( Option == 4 ){
				char Dividend, Divisor;	//�������ͳ��� 
				cout<< "�����뱻��������ʽ����:"; 
				cin>> Dividend;
				cout<< "�������������ʽ����:"; 
				cin>> Divisor;
				int  DividendIndex,  DivisorIndex;
				bool FindDividend = false;
				bool FindDivisor  = false;
				for ( int i=0; i<26; i++ ){
					if ( polynomials[i].Nameis( Dividend ) )
					{
						DividendIndex = i;
						FindDividend = true; 
					}
					
					if ( polynomials[i].Nameis( Divisor ) )
					{
						DivisorIndex = i;
						FindDivisor = true; 
					}
					
					if( FindDividend && FindDivisor )
						break;	
				}
				
				if( !FindDividend ){
					cout<< "����ʽ["<<Dividend<<"]������."<<endl; 
					continue;
				}
				
				if( !FindDivisor ){
					cout<< "����ʽ["<<Divisor<<"]������."<<endl; 
					continue;
				}
								
				Polynomial rema;
				Polynomial Quotient = polynomials[ DividendIndex ].Div( polynomials[ DivisorIndex ], rema );
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );
				cout << "��Ϊ: ";
				Quotient.Print();
				cout << "����: ";
				rema.Print();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			}else if( Option ==5 ){
				cout<< "���������ʽ����:"; 
				cin >> FunctionName;
				int RootIndex = 0;
				bool Find = false;
				for ( int i=0; i<26; i++ ){
					if ( polynomials[i].Nameis( FunctionName ) )
					{
						RootIndex = i;
						Find = true; 
						break;
					}
				}
				
				if( !Find ){
					cout<< "����ʽ["<<FunctionName<<"]������."<<endl; 
				}
				else{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );
					cout << "����ʽ:";
					polynomials[RootIndex].Print();
					cout << "ʵ��Ϊ��";
					float root = polynomials[RootIndex].Rooting();
					cout << root <<endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				}
			}else if( Option == 6 ){
				cout<< "���������ʽ����(*��ʾ���ж���ʽ):"; 
				cin>> FunctionName;
				
				if( FunctionName!='*' ){
					bool Find = false;
					
					for ( int i=0; i<26; i++ ){
						if ( polynomials[i].Nameis( FunctionName ) )
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );
							polynomials[i].Print();
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
							Find = true; 
							break;
						}	
					}

					if( !Find ){
						cout<< "����ʽ["<<FunctionName<<"]������."<<endl; 
					}
				}else{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );
					for ( int i=0; i<26; i++ ){
						if ( !polynomials[i].IsNull() )
						{
							polynomials[i].Print();
						}	
					}
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				}
			}else if( Option == 0 ){
				break;
			}else{
				cout<< "�޸ù���ѡ��!"<<endl; 
			}	
		}
	}
	return 0;
}
