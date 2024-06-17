#include <iostream>

#include <cstdlib> //����������� 

using namespace std;

int **p; 

int Calculation( int nPos, int mPos, int n, int m )
{
	int x;
	int max = 0;
	 
	//1����ֱ�����
	x = 1;
	for (int i=0; i<m; i++)
	{
		x = x * p[ nPos ][i];
		cout << p[ nPos ][i] << "*";
	}
	cout << "=" << x << endl;
	if ( x>max )
		max = x; 
	//2����ֱ�����
	x = 1;
	for (int i=0; i<n; i++) 
	{
		x = x * p[i][ mPos ];
		cout << p[i][ mPos ] << "*";
	}
	cout << "=" << x << endl;
	if ( x>max )
		max = x; 

	//3�����ҶԽ�
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
	
	//4���ҵ���Խ�	
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
	cout <<"�������������еĳ��Ϳ�:"<<endl;
	cout <<"N:";
	cin >> n;
	cout <<"M:";
	cin >> m;
	cout <<"��ʼ������������N*M..."<<endl;
	
	p = new int*[n];
	for ( int i=0; i<n; i++ )
		p[i] = new int[m];	
	
	for ( int i=0; i<n; i++ )
		for ( int j=0; j<m; j++ )
			p[i][j] = rand()%10; //͵һ����(��?��) ����һ��һ���������֣����Է�һ��������� :) 
	
	//��ӡ�������� 
	for ( int i=0; i<n; i++ )
	{
		for ( int j=0; j<m; j++ )
		{
			cout << p[i][j] << "\t";
		}
		cout << endl;
	}
	
	cout <<"���д�����Ͽ�ʼ���������..."<<endl;
	for ( int i=0; i<n; i++ )
	{
		for ( int j=0; j<m; j++ )
		{
			x = Calculation( i, j, n, m );
			if ( x > max )	
				max = x;
		}
	}
	
	//�ǵ��ͷŴ��������� 
	for(int i = 0; i < n; i++)
		delete[] p[i];
	delete[] p;
	cout <<"���ֵ��:"<<max<<endl;		
} 
