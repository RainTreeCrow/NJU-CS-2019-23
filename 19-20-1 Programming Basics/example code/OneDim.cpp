#include <iostream>

#include <cstdlib> //����������� 

using namespace std;

int *p; 

int Calculation( int iPosition, int n, int m )
{
	int x;
	int max = 0;
	 
	//1����ֱ�����
	x = 1;
	for (int i=0; i<m; i++)
	{
		x = x * p[ i + (iPosition/m) * m ];
		//cout << p[ i + (iPosition/m) * m ] << "*";
	}
	//cout << "=" << x << endl;
	if ( x>max )
		max = x; 
	//2����ֱ�����
	x = 1;
	for (int i=0; i<n; i++) 
	{
		x = x * p[ iPosition%m + i*m ];
		//cout << p[ iPosition%m + i*m ] << "*";
	}
	//cout << "=" << x << endl;	
	if ( x>max )
		max = x; 

	//3�����ҶԽ�
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
	
	//4���ҵ���Խ�	
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
	cout <<"�������������еĳ��Ϳ�:"<<endl;
	cout <<"N:";
	cin >> n;
	cout <<"M:";
	cin >>m;
	cout <<"��ʼ������������N*M..."<<endl;
	p = new int[n*m];
	
	for ( int i=0; i<n; i++ )
		for ( int j=0; j<m; j++ )
		{
			//cin >> p[i*m+j];	//��͵����һ��һ���� 
			p[i*m+j] = rand()%10; //���Ǿ���͵һ����(��?��) ����һ��һ���������֣����Է�һ��������� :)
		}
	
	//��ӡ�������� 
	for ( int i=0; i<n; i++ )
	{
		for ( int j=0; j<m; j++ )
		{
			cout << p[i*m+j] << "\t";
		}
		cout << endl;
	}
	
	cout <<"���д�����Ͽ�ʼ���������..."<<endl;
	for ( int i=0; i<n*m; i++ )
	{
		x = Calculation( i, n, m );
		if ( x > max )	
			max = x;
	}
	
	//�ǵ��ͷŴ��������� 
	delete[] p;
	cout <<"���ֵ��:"<<max<<endl;		
} 
