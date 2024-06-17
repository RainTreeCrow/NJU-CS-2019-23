#include <iostream>
#include <cstdlib> //用于随机函数 
using namespace std;

bool ComprFunction( int x ,int y );

void Sort( int d[], int n, bool (*compr)(int x, int y) );

int main( int argc, char** argv )
{
	bool (*compr)(int x, int y);
	compr = ComprFunction;
	int n,a; 
	cout <<"请确认一个数组的长度:"<<endl;
	cout <<"N:";
	cin  >> n;
	cout <<"创建一个数组:"<<endl;
	int *d = new int[n];
	for ( int i=0; i<n; i++ )
	{
		//cin >> a; //不偷懒就手工敲 
		//d[i] = a;
		
		d[i] = rand()%10; //还是决定偷一下懒(ˇ?ˇ) 不想一个一个的敲数字，所以放一个随机函数 :)
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
		cout <<"冒泡排序正序:"<<endl;
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
		cout <<"冒泡排序逆序:"<<endl;
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





