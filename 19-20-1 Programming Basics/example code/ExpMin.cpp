#include <iostream>
#include <cstdlib> //����������� 
using namespace std;

int *Min( const int a[], int num );

int main( int argc, char** argv )
{
	cout <<"��ȷ��һ������ĳ���:"<<endl;
	cout <<"N:";
	int n,m;
	cin  >> n;
	cout <<"����һ������:"<<endl;
	int *a = new int[n];
	for ( int i=0; i<n; i++ )
	{
//		cin >> m;  //-1���ƽ����Ǹ����ӣ�������Ҫ�ٷ���ָ�����飬���Ծ�������͵һ���� :) 
//		if (m<0)
//			break;
//		a[i] = m;
		
		//���ȡ1~10����	
		a[i] = rand()%10+1; //͵һ����(��?��) ����һ��һ���������֣����Է�һ��������� :)
	}

	for ( int i=0; i<n; i++ )
		cout << a[i] << " ";
	cout << endl;
	
	int *b = Min( a, n );
	
	cout <<"�滻�������:"<<endl; 
	for ( int i=0; i<n; i++ )
		cout << b[i] << " ";
	cout << endl;
	
	delete[] a;
	delete[] b;
	return 0;
}

int *Min( const int a[], int num )
{
	int min = a[0];
	for ( int i=1; i<num; i++  )
	{
		if( a[i] < min )
			min = a[i];	
	}
	
	cout << "��Сֵ:" <<min<<"�����滻."<<endl; 
	
	int *n = new int[num];
	bool isChange = false; 
	for ( int i=0; i<num; i++ )
	{
		if ( a[i] == min && !isChange )
			n[i] = 0;
		else
			n[i] = a[i];
	}
		
	return n;
} 
