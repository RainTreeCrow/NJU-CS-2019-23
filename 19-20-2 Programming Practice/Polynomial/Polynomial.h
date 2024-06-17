
#pragma once
class Polynomial{
	private:
		char FunctionName;	//����ʽ����
		float Coefficients[50];	//����ʽϵ������
		int    CoefficientCount;	//����ʽϵ������

		float Newton( float x0 );	//ţ�ٷ�����Ӹ� 
		
	public:
		Polynomial();
		~Polynomial();
		
		bool IsNull();
		bool Nameis( char Name );
		void Initialization( char Name, int Count, float *Coefs );
		void Initialization( float Coefs );
		void Initialization( Polynomial poly );
		void Print();	//��ӡ���ʽ
		
		float Function(float x);	//����ʽ����
		
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
		
		//�������� 
		Polynomial Add( Polynomial poly );
		Polynomial Sub( Polynomial poly );
		Polynomial Mul( Polynomial poly );
		Polynomial Mul( float data );
		Polynomial Div( Polynomial poly, Polynomial &rema );
	
		float Definite_Integral( float Lower, float Height );	//���ʽ������
		Polynomial Derivation();	//���ʽ��
		Polynomial Inverse();	//���ʽ����Ԫ
		float Rooting();	//���ʽ���
};

