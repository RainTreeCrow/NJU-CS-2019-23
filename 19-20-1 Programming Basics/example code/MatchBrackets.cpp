#include <iostream>
#include <string> 	//string �ַ����������� 
#include <string.h> //strlen ���� 

using namespace std;

int main( int argc, char** argv )
{
	
	cout <<"��һ�����ʽ:"<<endl;
	// ���Կ����������ַ�����ȡ���� 
	string Expression;		//1�� string�������Բ����Ƴ��ȣ�
	cin >>Expression;
	int ExpressionLength = Expression.size();
	//char Expression[100];	//2:  ��charָ����Ҫ����ָ�����ȿռ�  
	//cin >>Expression;
	//int ExpressionLength = strlen(Expression)
 
	int wCount = 0;
	int wIndex = 0;
	bool wHaveBrackets = false; 
	cout <<"��ʼƥ������..."<<endl;	
	for( wIndex = 0; wIndex < ExpressionLength; wIndex++ )
	{
		if ( Expression[ wIndex ] == 40 )	//40 ��ASICC���б�ʾ������
		{
			wHaveBrackets = true;
			wCount ++;
		}
		if ( Expression[ wIndex ] == 41 )	//41 ��ASICC���б�ʾ������
		{  
			wHaveBrackets = true;
			wCount --;
		}
	}
	
	if ( !wHaveBrackets )
	{
		cout <<"һ�����Ŷ������룬����ƥ��ɶѽ~"<<endl;
		return 0;		
	}
	
	if (wCount != 0)
		cout <<"������ûƥ����!"<<endl;
	else
		cout <<"�������Ŷ�ƥ������!"<<endl;
	return 0;
}
