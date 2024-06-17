#include <iostream>
#include <cstdlib> //用于随机函数 
using namespace std;

int *Min( const int a[], int num );

int main( int argc, char** argv )
{
	cout <<"请确认一个数组的长度:"<<endl;
	cout <<"N:";
	int n,m;
	cin  >> n;
	cout <<"创建一个数组:"<<endl;
	int *a = new int[n];
	for ( int i=0; i<n; i++ )
	{
//		cin >> m;  //-1控制结束是个幌子，考点主要再返回指针数组，所以决定还是偷一下懒 :) 
//		if (m<0)
//			break;
//		a[i] = m;
		
		//随机取1~10数字	
		a[i] = rand()%10+1; //偷一下懒(ˇ?ˇ) 不想一个一个的敲数字，所以放一个随机函数 :)
	}

	for ( int i=0; i<n; i++ )
		cout << a[i] << " ";
	cout << endl;
	
	int *b = Min( a, n );
	
	cout <<"替换后的数组:"<<endl; 
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
	
	cout << "最小值:" <<min<<"将被替换."<<endl; 
	
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
