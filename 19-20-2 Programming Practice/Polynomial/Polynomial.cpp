#include "Polynomial.h"
#include <iostream>
#include <string.h>
#include <math.h> 
using namespace std;

Polynomial::Polynomial(){
	FunctionName = '\0';
	for( int i=0; i<50; i++ )
		Coefficients[50] = 0.00;
	CoefficientCount = 0;	
}

Polynomial::~Polynomial(){
	FunctionName = '\0';
	for( int i=0; i<50; i++ )
		Coefficients[50] = 0.00;
	CoefficientCount = 0;	
}

float Polynomial::Function(float x){
	float Result = 0.00;
	for( int i=0; i<CoefficientCount; i++ ){
		Result = Result + Coefficients[i]*pow( x, i );
	}
	return Result;	
}

float Polynomial::Newton( float x0 ){
	// return  x0-f(x0)/f'(x0)
	Polynomial DerFunction = Derivation();
	return x0 - Function( x0 ) / DerFunction.Function( x0 );
}

bool Polynomial::IsNull(){
	return CoefficientCount == 0;
}

bool Polynomial::Nameis( char Name ){
	return FunctionName == Name;
}

void Polynomial::Initialization(char Name, int Count, float *Coefs){
	FunctionName = Name;
	CoefficientCount = Count;
	for ( int i=0; i<CoefficientCount; i++ ){
		Coefficients[i] = Coefs[i];
	}
	
	while( Coefficients[CoefficientCount-1] == 0 )
		CoefficientCount--;
}

void Polynomial::Initialization( Polynomial poly ){
	//cout <<"Line = "<<__LINE__<<endl;
	FunctionName = poly.GetName();
	CoefficientCount = poly.GetCount();
	//cout << "CoefficientCount = " <<CoefficientCount<< endl;
	if( CoefficientCount>0 ){
		for ( int i=0; i<CoefficientCount; i++ ){
			Coefficients[i] = poly.GetCoefficient(i);
		}
	}

	while( Coefficients[CoefficientCount-1] == 0 )
		CoefficientCount--;
}

void Polynomial::Initialization( float Coefs ){
	FunctionName = '0';
	CoefficientCount = 1;
	Coefficients[0] = Coefs;
}

//打印 
void Polynomial::Print(){
	if ( CoefficientCount == 0 ){
		cout << "表达式未初始化..."<<endl;
		return; 
	}

	//这段用于查看表达式长度 
	//cout << "Count="<<CoefficientCount<<"\t\t";

	if( FunctionName>=65 && FunctionName<=90 )
		cout << FunctionName << " = ";
		
	bool isZero = true; 
	for( int i=CoefficientCount-1; i>=0; i-- ){
		if( Coefficients[i]==0 )
			continue;
		else if( Coefficients[i]<0 ){
			if( i == 0 ){
				cout<<Coefficients[i];
			}
			else if( i == 1 ){
				if ( Coefficients[i] == -1 )
					cout<<"-x";
				else
					cout<<Coefficients[i]<<"x";
			}
			else{
				if( Coefficients[i] == -1 )
					cout<<"-x^"<<i;
				else
					cout<<Coefficients[i]<<"x^"<<i;
			}
			isZero = false;
		}else{
			if( !isZero )
					cout<<"+";
			
			if( i==0 ){
				cout<<Coefficients[i];
			}	
			else if( i==1 ){
				if( Coefficients[i] == 1 )
					cout<<"x";
				else
					cout<<Coefficients[i]<<"x";
			}
			else{
				if( Coefficients[i] == 1 )
					cout<<"x^"<<i;	
				else
					cout<<Coefficients[i]<<"x^"<<i;
			}
				
			isZero = false;
		}
	}

	if( isZero )
		cout << "0";
	cout << endl;
}

//四则运算 
Polynomial Polynomial::Add( Polynomial poly ){
	Polynomial Result;
	if( poly.IsNull() ){
		return Result;
	}
	
	if( CoefficientCount == 0 )
		return Result;
	
	int ResultCount = 0;
	if( poly.GetCount() >= CoefficientCount )
		ResultCount = poly.GetCount();
	else
		ResultCount = CoefficientCount;
	
	float ResultCoeff[50];
	for ( int i=0; i<ResultCount; i++ ){
		if( i < CoefficientCount )
			ResultCoeff[i] = poly.GetCoefficient( i ) + Coefficients[i] ;
		else
			ResultCoeff[i] = poly.GetCoefficient( i ) + 0;
	}
	
	Result.Initialization( '+', ResultCount, ResultCoeff );
	return Result;
}

Polynomial Polynomial::Sub( Polynomial poly ){
	Polynomial Result;
	if( poly.IsNull() ){
		return Result;
	}
	
	if( CoefficientCount == 0 )
		return Result;

	int ResultCount = 0;
	if( poly.GetCount() >= CoefficientCount )
		ResultCount = poly.GetCount();
	else
		ResultCount = CoefficientCount;

	float ResultCoeff[50];
	for ( int i=0; i<ResultCount; i++ ){
		if( i < CoefficientCount )
			ResultCoeff[i] = Coefficients[i] - poly.GetCoefficient( i ) ;
		else
			ResultCoeff[i] = 0 - poly.GetCoefficient( i );
	}

	Result.Initialization( '-', ResultCount, ResultCoeff );
	return Result;
}
Polynomial Polynomial::Mul( Polynomial poly ){
	Polynomial Result;
	if( poly.IsNull() ){
		return Result;
	}
	
	if( CoefficientCount == 0 )
		return Result;
	
	int ResultCount = poly.GetCount() + CoefficientCount-1;
	float ResultCoeff[50];
	for( int i=0; i<ResultCount; i++ )
		ResultCoeff[i] = 0;
	
	for( int i=0; i<poly.GetCount(); i++ ){
		for( int c=0; c<CoefficientCount; c++ ){
			if( ResultCoeff[i+c] != 0 )
				ResultCoeff[i+c] = ResultCoeff[i+c] + poly.GetCoefficient( i ) * Coefficients[c];
			else
				ResultCoeff[i+c] = poly.GetCoefficient( i ) * Coefficients[c];
		}
	}
	
	Result.Initialization( '-', ResultCount, ResultCoeff );
	return Result;
}

Polynomial Polynomial::Mul( float data ){
	for( int i=0; i<CoefficientCount; i++ ){
		Coefficients[i] = Coefficients[i] * data;
	}
}

Polynomial Polynomial::Div( Polynomial poly, Polynomial &rema ){
	Polynomial Quotient;
	if( poly.IsNull() ){
		return Quotient;
	}
	
	if( CoefficientCount == 0 )
		return Quotient;
	
	//竖式算法
	if( poly.GetCount() > CoefficientCount ) {
		cout << "Line = "<<__LINE__<<endl;
		Quotient.Initialization( 0 );
		rema.Initialization( '.', CoefficientCount, Coefficients );
	}else{
		float QuotientCoeff[50];
		for( int i=0; i<50; i++ )
			QuotientCoeff[i] = 0.00;

		cout << "Line = "<<__LINE__<<endl;
		rema.Initialization( '.', CoefficientCount, Coefficients );
		int QuotientCount = rema.GetCount() - poly.GetCount()+1;
		int loop = 0;
		do{
			QuotientCoeff[rema.GetCount() - poly.GetCount()] = rema.GetCoefficient( rema.GetCount()-1 ) / poly.GetCoefficient( poly.GetCount()-1 );
			Quotient.Initialization( '&', QuotientCount, QuotientCoeff );
//			cout <<"Quot=";		//运算过程中打的日志 
//			Quotient.Print();
			
			Polynomial Buff;
			Buff.Initialization( '*', rema.GetCount()-poly.GetCount()+1, QuotientCoeff );
//			cout <<"Buff=";		//运算过程中打的日志 
//			Buff.Print();
			
			rema.Initialization( rema.Sub( Buff.Mul( poly ) ) );
//			cout <<"rema=";		//运算过程中打的日志 
//			rema.Print();	
			
			loop ++;
			if( loop > 10 )
				break;
		}while( rema.GetCount() >= poly.GetCount() );
	}

	return Quotient;
}

//表达式定积分
float Polynomial::Definite_Integral( float Lower, float Height ){	//表达式定积分

	float Sub, Step, Result;
	Sub = ( Function(Lower) + Function(Height) ) / 2 ;
	Step= ( Height - Lower ) / 1000; 	//积分步长，将Lowr到 Height之间的区间分成1000份，份数越大，近似值约接近，但是要考虑float变量的取值范围 
	for(int i=1; i<1000; i++)
		Sub = Sub + Function( Lower + i * Step);
	Result = Sub * Step;
	return Result;
}

//表达式求导 
Polynomial Polynomial::Derivation(){

// 原函数会自导~所以还是调整一下	
//	for( int i=1; i<CoefficientCount; i++ ){
//		Coefficients[i-1] = Coefficients[i]*i;
//	}
//	CoefficientCount--;
	
	float DerCoeff[50];
	for( int i=0; i<=50; i++ )
		DerCoeff[i] = 0; 
	for( int i=1; i<CoefficientCount; i++ )
		DerCoeff[i-1] = Coefficients[i]*i;
	
	Polynomial Result;
	Result.Initialization( 39, CoefficientCount-1, DerCoeff );
	return Result;
}

//表达式求逆元
Polynomial Polynomial::Inverse(){	
	
	float inv[50];
	for( int i=0; i<50; i++ )
		inv[50] = 0.00;
	
	inv[0] = 1/Coefficients[0];
	
	for( int i=1; i<CoefficientCount; i++ ){
		for ( int j=0; j<i; j++ ){
			inv[i] = inv[i] + inv[j]*( 0-Coefficients[i-j]/Coefficients[0] );
		}
	}
	
	Polynomial Result;
	Result.Initialization( FunctionName + 32, CoefficientCount, inv );//名称无意义，只是从大写转成小写 
	return Result;
}

//表达式求根
float Polynomial::Rooting(){
	float x1 = Coefficients[CoefficientCount-1];	//用最大项系数做近似解x0
	float x0 = 0.00;
	do
	{
		x0 = x1;	
		x1 = Newton( x0 );
	}while( Function(x1)>0.00001 );
	
	return x0;
} 
