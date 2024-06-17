#include <iostream>
#include <cstdlib> //����������� 

using namespace std;

int main( int argc, char** argv )
{
	int N,M;
	cout <<"��������������ύ��:"<<endl;
	cin >>N >>M;
	
	//�������� 
	int **Queue = new int*[N];
	for ( int i=0; i<N; i++ )
	{
		Queue[i] = new int[3];	//2λ����ֱ�洢�����ţ�����������ܺ�ʱ
		Queue[i][0] = i+1;	//�����Ŵ�1��N 
		Queue[i][1] = 0;	//�������
		Queue[i][2] = 0; 	//�ܺ�ʱ 
	}
	
	//�ύ��Ϣ���� 
	int **Submit = new int*[M];
	for ( int i=0; i<M; i++ )
		Submit[i] = new int[4];	//4λ����ֱ������ţ������ţ��ύʱ�䣬�Ƿ�ͨ��
	
	cout <<"����������ִ�����,�����ű�������1-"<<N<<":"<<endl; 
	for ( int i=0; i<M; i++ )
	{
		 //cin >>Submit[i][0]>>Submit[i][1]>>Submit[i][2]>>Submit[i][3]; //�������ʽ�������룬�������������̫�࣬��������͵����:)
 
 		//�������д���������æ���� 
		Submit[i][0] = rand()%N+1;	//������:���1-N
		Submit[i][1] = rand()%9+1;	//������:���1-9
		Submit[i][2] = rand()%100*100;	//�ύʱ��
		Submit[i][3] = rand()%2;	//��� 1 �� 0	
	}
		
	
	for ( int i=0; i<M; i++ )
		cout <<"����"<<Submit[i][0]<<"�ύ��"<<Submit[i][1]<<"�⣬��ʱ"<<Submit[i][2]<<"��ִ�н��"<<Submit[i][3]<<endl; 
	
	cout <<"*******************************ͳ��ִ�����*******************************"<<endl;
	for ( int i=0; i<M; i++ )
		for ( int j=0; j<N; j++ )
		{
			if ( Submit[i][0] == Queue[j][0] )
			{
				if( Submit[i][3] != 0 )
					Queue[j][1]++;
				Queue[j][2] = Queue[j][2] + Submit[i][2];			
			}
		}
	
	for ( int i=0; i<N; i++ )
		cout <<"����"<<Queue[i][0]<<"���"<<Queue[i][1]<<"���⣬��ʱ"<<Queue[i][2]<<endl;
	
	cout <<"���ڽ����ŶӴ���..."<<endl;
	
	int buf;
	for ( int i=1; i<N; i++  )
	{
		for( int j=0; j<N-i; j++ )
		{
			if( Queue[j][1] < Queue[j+1][1] )	
			{
				buf = Queue[j][0];
				Queue[j][0] = Queue[j+1][0];
				Queue[j+1][0] = buf;	
				
				buf = Queue[j][1];
				Queue[j][1] = Queue[j+1][1];
				Queue[j+1][1] = buf;
				
				buf = Queue[j][2];
				Queue[j][2] = Queue[j+1][2];
				Queue[j+1][2] = buf;
			}
			else if( Queue[j][1] == Queue[j+1][1] ) 
			{
				if( Queue[j][2] > Queue[j+1][2] )
				{
					buf = Queue[j][0];
					Queue[j][0] = Queue[j+1][0];
					Queue[j+1][0] = buf;	
					
					buf = Queue[j][1];
					Queue[j][1] = Queue[j+1][1];
					Queue[j+1][1] = buf;
					
					buf = Queue[j][2];
					Queue[j][2] = Queue[j+1][2];
					Queue[j+1][2] = buf;
				}	 
			}
		}
	}
	
	cout <<"*******************************�����Ľ��*******************************"<<endl; 
	for ( int i=0; i<N; i++ )
		cout <<"����"<<Queue[i][0]<<"���"<<Queue[i][1]<<"���⣬��ʱ"<<Queue[i][2]<<endl;
		
	for(int i = 0; i < N; i++)
		delete[] Queue[i];
	delete[] Queue;	
	
	for(int i = 0; i < M; i++)
		delete[] Submit[i];
	delete[] Submit;	
	
	return 0;	
}
