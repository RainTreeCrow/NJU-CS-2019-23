#include <iostream>

#include <cstdlib> //用于随机函数 

using namespace std;

int *p; 

int Calculation( int iPosition, int n, int m )
{
	int x;
	int max = 0;
	 
	//1横向直线相乘
	x = 1;
	for (int i=0; i<m; i++)
	{
		x = x * p[ i + (iPosition/m) * m ];
		//cout << p[ i + (iPosition/m) * m ] << "*";
	}
	//cout << "=" << x << endl;
	if ( x>max )
		max = x; 
	//2纵向直线相乘
	x = 1;
	for (int i=0; i<n; i++) 
	{
		x = x * p[ iPosition%m + i*m ];
		//cout << p[ iPosition%m + i*m ] << "*";
	}
	//cout << "=" << x << endl;	
	if ( x>max )
		max = x; 

	//3从左到右对角
	x = 1;
	for(int i=0; i<n && i<=m-iPosition%m-1; i++)
	{
		int wpos = (iPosition+i)%m + (iPosition/m + i)*m;
		if (wpos > n*m-1)
			continue;
		
		x = x * p[ wpos ];
		//cout << p[ wpos ] << "*";
	}
	//cout << "=" << x << endl;
	if ( x>max )
		max = x; 
	
	//4从右到左对角	
	x = 1;
	for(int i=0; i<n && i<=iPosition%m ; i++)
	{
		int wpos = (iPosition-i)%m + (iPosition/m + i)*m;
		if (wpos > n*m-1)
			continue;
		x = x * p[ wpos ];
		//cout << p[ wpos ] << "*";
	}
	//cout << "=" << x << endl;
	if ( x>max )
		max = x; 
		
	return max;	
}

int main( int argc, char** argv )
{
	int n, m, i, j, x, max = 0;
	cout <<"请输入数组阵列的长和宽:"<<endl;
	cout <<"N:";
	cin >> n;
	cout <<"M:";
	cin >>m;
	cout <<"开始创建数组阵列N*M..."<<endl;
	p = new int[n*m];
	
	for ( int i=0; i<n; i++ )
		for ( int j=0; j<m; j++ )
		{
			//cin >> p[i*m+j];	//不偷懒就一个一个敲 
			p[i*m+j] = rand()%10; //还是决定偷一下懒(ˇ?ˇ) 不想一个一个的敲数字，所以放一个随机函数 :)
		}
	
	//打印数组阵列 
	for ( int i=0; i<n; i++ )
	{
		for ( int j=0; j<m; j++ )
		{
			cout << p[i*m+j] << "\t";
		}
		cout << endl;
	}
	
	cout <<"阵列创建完毕开始计算最大数..."<<endl;
	for ( int i=0; i<n*m; i++ )
	{
		x = Calculation( i, n, m );
		if ( x > max )	
			max = x;
	}
	
	//记得释放创建的数组 
	delete[] p;
	cout <<"最大值是:"<<max<<endl;		
} 
