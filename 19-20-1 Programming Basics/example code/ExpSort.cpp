#include <iostream>
#include <cstdlib> //����������� 
using namespace std;

bool ComprFunction( int x ,int y );

void Sort( int d[], int n, bool (*compr)(int x, int y) );

int main( int argc, char** argv )
{
	bool (*compr)(int x, int y);
	compr = ComprFunction;
	int n,a; 
	cout <<"��ȷ��һ������ĳ���:"<<endl;
	cout <<"N:";
	cin  >> n;
	cout <<"����һ������:"<<endl;
	int *d = new int[n];
	for ( int i=0; i<n; i++ )
	{
		//cin >> a; //��͵�����ֹ��� 
		//d[i] = a;
		
		d[i] = rand()%10; //���Ǿ���͵һ����(��?��) ����һ��һ���������֣����Է�һ��������� :)
	}
	
	for ( int i=0; i<n; i++ )
		cout << d[i] << " ";
	cout << endl;	 

	Sort( d, n, compr );
	
	delete[] d;
	return 0;	
}

bool ComprFunction( int x ,int y )
{
	return ( x >= y );
}

void Sort( int d[], int n, bool (*compr)(int x, int y) )
{
		
	if ( compr(3,2) )	
	{
		cout <<"ð����������:"<<endl;
		int buf;
		for ( int i=1; i<n; i++  )
		{
			for( int j=0; j<n-i; j++ )
				if( d[j] > d[j+1] )	
				{
					buf = d[j];
					d[j] = d[j+1];
					d[j+1] = buf;
				}
			
//			for( int i=0; i<n; i++ )
//				cout << d[i] <<" ";
//			cout << endl; 
		}
		
		for( int i=0; i<n; i++ )
			cout << d[i] <<" ";
		cout << endl; 
	}
	
	if( not compr( 2,3 ) ) 
	{
		cout <<"ð����������:"<<endl;
		int buf;
		for ( int i=1; i<n; i++  )
		{
			for( int j=0; j<n-i; j++ )
				if( d[j] < d[j+1] )	
				{
					buf = d[j];
					d[j] = d[j+1];
					d[j+1] = buf;
				}
			
//			for( int i=0; i<n; i++ )
//				cout << d[i] <<" ";
//			cout << endl; 
		}
		
		for( int i=0; i<n; i++ )
			cout << d[i] <<" ";
		cout << endl; 
	} 
}





