
#pragma once
class Polynomial{
	private:
		char FunctionName;	//多项式名称
		float Coefficients[50];	//多项式系数变量
		int    CoefficientCount;	//多项式系数数量

		float Newton( float x0 );	//牛顿法求近视根 
		
	public:
		Polynomial();
		~Polynomial();
		
		bool IsNull();
		bool Nameis( char Name );
		void Initialization( char Name, int Count, float *Coefs );
		void Initialization( float Coefs );
		void Initialization( Polynomial poly );
		void Print();	//打印表达式
		
		float Function(float x);	//多项式函数
		
		char GetName(){
			return FunctionName;
		}	
	
		int GetCount(){
			return CoefficientCount;
		}
		
		float GetCoefficient( int i ){
			if( i>=0 && i < CoefficientCount )
				return Coefficients[i];
			else
				return 0;
		}
		
		//四则运算 
		Polynomial Add( Polynomial poly );
		Polynomial Sub( Polynomial poly );
		Polynomial Mul( Polynomial poly );
		Polynomial Mul( float data );
		Polynomial Div( Polynomial poly, Polynomial &rema );
	
		float Definite_Integral( float Lower, float Height );	//表达式定积分
		Polynomial Derivation();	//表达式求导
		Polynomial Inverse();	//表达式求逆元
		float Rooting();	//表达式求根
};

