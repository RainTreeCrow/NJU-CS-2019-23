#include <iostream>

#include <cstdlib> //用于随机函数 

using namespace std;

int **p; 

int Calculation( int nPos, int mPos, int n, int m )
{
	int x;
	int max = 0;
	 
	//1横向直线相乘
	x = 1;
	for (int i=0; i<m; i++)
	{
		x = x * p[ nPos ][i];
		cout << p[ nPos ][i] << "*";
	}
	cout << "=" << x << endl;
	if ( x>max )
		max = x; 
	//2纵向直线相乘
	x = 1;
	for (int i=0; i<n; i++) 
	{
		x = x * p[i][ mPos ];
		cout << p[i][ mPos ] << "*";
	}
	cout << "=" << x << endl;
	if ( x>max )
		max = x; 

	//3从左到右对角
	x = 1;
	for(int i=0; i<n; i++)
	{
		int wnpos = nPos+i;
		int wmpos = mPos+i;
		if (wnpos>=n || wmpos>=m)
			continue;
		
		x = x * p[ wnpos ][ wmpos ];
		cout << p[ wnpos ][ wmpos ] << "*";
	}
	cout << "=" << x << endl;
	if ( x>max )
		max = x; 
	
	//4从右到左对角	
	x = 1;
	for(int i=0; i<n; i++)
	{
		int wnpos = nPos+i;
		int wmpos = mPos-i;
		if (wnpos>=n || wmpos<0)
			continue;
		
		x = x * p[ wnpos ][ wmpos ];
		cout << p[ wnpos ][ wmpos ] << "*";
	}
	cout << "=" << x << endl;
	if ( x>max )
		max = x; 
		
	return max;	
}

int main( int argc, char** argv )
{
	int n, m, x, max = 0;
	cout <<"请输入数组阵列的长和宽:"<<endl;
	cout <<"N:";
	cin >> n;
	cout <<"M:";
	cin >> m;
	cout <<"开始创建数组阵列N*M..."<<endl;
	
	p = new int*[n];
	for ( int i=0; i<n; i++ )
		p[i] = new int[m];	
	
	for ( int i=0; i<n; i++ )
		for ( int j=0; j<m; j++ )
			p[i][j] = rand()%10; //偷一下懒(ˇ?ˇ) 不想一个一个的敲数字，所以放一个随机函数 :) 
	
	//打印数组阵列 
	for ( int i=0; i<n; i++ )
	{
		for ( int j=0; j<m; j++ )
		{
			cout << p[i][j] << "\t";
		}
		cout << endl;
	}
	
	cout <<"阵列创建完毕开始计算最大数..."<<endl;
	for ( int i=0; i<n; i++ )
	{
		for ( int j=0; j<m; j++ )
		{
			x = Calculation( i, j, n, m );
			if ( x > max )	
				max = x;
		}
	}
	
	//记得释放创建的数组 
	for(int i = 0; i < n; i++)
		delete[] p[i];
	delete[] p;
	cout <<"最大值是:"<<max<<endl;		
} 
