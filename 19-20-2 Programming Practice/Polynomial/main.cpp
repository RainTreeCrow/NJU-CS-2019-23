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

void MoveCursor( Position pos )	//设置光标位置(就是输出显示的开始位置)
{
	COORD Pos = { pos.X*2, pos.Y };
	HANDLE OutPutHandle = GetStdHandle( STD_OUTPUT_HANDLE );//获得标准输出的句柄   
	SetConsoleCursorPosition( OutPutHandle, Pos ); //设置光标位置
}

void Menu( int Width, int Height ){
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	for ( int w=0; w < (Width-6); w++ )
		cout<<"=";
	cout<<"多项式计算机";
	for ( int w=0; w < (Width-6); w++ )
		cout<<"=";
	cout << endl<<endl;
	cout << "     1:输入  2:混合运算  3:求逆元  4:除法(取模)运算  5:求根  6:查看  0:退出"<<endl;
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);	//设置红色
	cout<<"★★多项式计算器★★";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	
	AboutInfoPos.X = (Width-2)/2-2;
	AboutInfoPos.Y = Height/2-2;
	MoveCursor( AboutInfoPos );
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);	//设置红色
	cout<<"作者：张涵之";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	
	AboutInfoPos.X = (Width-2)/2-2;
	AboutInfoPos.Y = Height/2;
	MoveCursor( AboutInfoPos );
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);	//设置蓝色
	cout<<"学号: 191220154";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	
	AboutInfoPos.X = (Width-2)/2-2;
	AboutInfoPos.Y = Height/2+4;
	MoveCursor( AboutInfoPos );
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );	//设置一个杂色 
	cout<<"敲回车键进入";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	
	AboutInfoPos.X = (Width-2)/2-2;
	AboutInfoPos.Y = Height/2+6;
	MoveCursor( AboutInfoPos );
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );	//设置一个杂色 
	cout<<"敲ESC键退出 ";
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
	int Option = 0;			//操作项目 
	int PolyonmialLength;	//多项式长度 
	float Coefficients[50];		//系数字符串
	Polynomial polynomials[26];	//26个字母，每个字母作为一个多项，应该够用了

	char FunctionName; 
	if( isEntry ){
		Menu( 40, 24 );
		while(1){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			cout << "请选择：";
			cin >> Option;
			while(cin.fail())
			{
				cin.clear();
				cin.ignore();
				cout << "输入功能选项错误，请重新选择:"<<endl;
				cin >> Option;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			if ( Option == 1 ){
				cout<< "多项式长度:";
				cin >> PolyonmialLength;
				while(cin.fail())
				{
					cin.clear();
					cin.ignore();
					cout << "输入多项式长度错误，请重新输入:"<<endl;
					cin >> PolyonmialLength;
				}
				
				for( int i=0; i<50; i++ )
					Coefficients[i] = 0;
				
				cout<< "请输入系数:"<<endl; 
				for( int i=PolyonmialLength-1; i>=0; i--){
					cin >> Coefficients[i];
					while(cin.fail())
					{
						cin.clear();
						cin.ignore();
						cout << "输入第"<<PolyonmialLength-i<<"个系数错误，请重新输入:"<<endl;
						cin >> Coefficients[i];
					}
				}
				cout<< "请输入多项式名称A~F(重复名称将被覆盖):"; 
				do{
					cin >> FunctionName;
					if( FunctionName<65 || FunctionName>90 )
						cout<<"多项式名称错误，请输入A~F(重复名称将被覆盖):"<<endl;
				} 
				while( FunctionName<65 || FunctionName>90 );	//函数名称不在26个大写字母范围内则重新输入 
				
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
				char ExpressionStr[128];	//128位表达式长度，足够包含一个超大的表达式了
				char Entry = 'Y';
				while( Entry == 'Y' || Entry == 'y' ) 
				{
					cout<< "请输入表达式(符号标识: 求导:*!; 定积分:$[l,h]; 加:+; 减:-; 乘:* ):"<<endl;
					memset( ExpressionStr, 0x00, sizeof(ExpressionStr) );
					cin>> ExpressionStr;
					Token *Root = Exp.Analysis( ExpressionStr );
					if( NULL == Root ){
						cout<<"输入表达式错误！"<<endl;
					}
					else{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );
						cout<<"表达式：";
						Exp.Print( Root );
						Polynomial poly = Exp.Execute( Root );
						
						if( !poly.IsNull() ){
							cout<<" = ";
							poly.Print();
						}
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
						Exp.Free( Root );
					}
					cout<<"是否继续运行(Y/N):";
					cin >> Entry;
				}
			}else if( Option == 3 ){
				bool Find = false;
				cout<< "请输入多项式名称:";
				cin>> FunctionName;

				for ( int i=0; i<26; i++ ){
					if ( polynomials[i].Nameis( FunctionName ) )
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );
						cout << "逆元为: "<<FunctionName<<"^-1 = ";
						polynomials[i].Inverse().Print();
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
						Find = true; 
						break;
					}	
				}
				if( !Find ){
					cout<< "多项式["<<FunctionName<<"]不存在."<<endl; 
				}
			}else if( Option == 4 ){
				char Dividend, Divisor;	//被除数和除数 
				cout<< "请输入被除数多项式名称:"; 
				cin>> Dividend;
				cout<< "请输入除数多项式名称:"; 
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
					cout<< "多项式["<<Dividend<<"]不存在."<<endl; 
					continue;
				}
				
				if( !FindDivisor ){
					cout<< "多项式["<<Divisor<<"]不存在."<<endl; 
					continue;
				}
								
				Polynomial rema;
				Polynomial Quotient = polynomials[ DividendIndex ].Div( polynomials[ DivisorIndex ], rema );
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );
				cout << "商为: ";
				Quotient.Print();
				cout << "余数: ";
				rema.Print();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			}else if( Option ==5 ){
				cout<< "请输入多项式名称:"; 
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
					cout<< "多项式["<<FunctionName<<"]不存在."<<endl; 
				}
				else{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );
					cout << "多项式:";
					polynomials[RootIndex].Print();
					cout << "实根为：";
					float root = polynomials[RootIndex].Rooting();
					cout << root <<endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				}
			}else if( Option == 6 ){
				cout<< "请输入多项式名称(*显示所有多项式):"; 
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
						cout<< "多项式["<<FunctionName<<"]不存在."<<endl; 
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
				cout<< "无该功能选项!"<<endl; 
			}	
		}
	}
	return 0;
}
