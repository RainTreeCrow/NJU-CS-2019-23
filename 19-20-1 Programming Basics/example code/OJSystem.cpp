#include <iostream>
#include <cstdlib> //用于随机函数 

using namespace std;

int main( int argc, char** argv )
{
	int N,M;
	cout <<"请输入队伍数和提交数:"<<endl;
	cin >>N >>M;
	
	//队伍数组 
	int **Queue = new int*[N];
	for ( int i=0; i<N; i++ )
	{
		Queue[i] = new int[3];	//2位数组分别存储队伍编号，答对数量和总耗时
		Queue[i][0] = i+1;	//队伍编号从1到N 
		Queue[i][1] = 0;	//答对数量
		Queue[i][2] = 0; 	//总耗时 
	}
	
	//提交信息数组 
	int **Submit = new int*[M];
	for ( int i=0; i<M; i++ )
		Submit[i] = new int[4];	//4位数组分别存队伍编号，问题编号，提交时间，是否通过
	
	cout <<"输入各队伍的执行情况,队伍编号必须输入1-"<<N<<":"<<endl; 
	for ( int i=0; i<M; i++ )
	{
		 //cin >>Submit[i][0]>>Submit[i][1]>>Submit[i][2]>>Submit[i][3]; //用这个方式进行输入，但是输入的内容太多，决定还是偷个懒:)
 
 		//以下四行代码会随机帮忙填数 
		Submit[i][0] = rand()%N+1;	//队伍编号:随机1-N
		Submit[i][1] = rand()%9+1;	//问题编号:随机1-9
		Submit[i][2] = rand()%100*100;	//提交时间
		Submit[i][3] = rand()%2;	//随机 1 和 0	
	}
		
	
	for ( int i=0; i<M; i++ )
		cout <<"队伍"<<Submit[i][0]<<"提交第"<<Submit[i][1]<<"题，耗时"<<Submit[i][2]<<"，执行结果"<<Submit[i][3]<<endl; 
	
	cout <<"*******************************统计执行情况*******************************"<<endl;
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
		cout <<"队伍"<<Queue[i][0]<<"完成"<<Queue[i][1]<<"道题，耗时"<<Queue[i][2]<<endl;
	
	cout <<"正在进行排队处理..."<<endl;
	
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
	
	cout <<"*******************************排序后的结果*******************************"<<endl; 
	for ( int i=0; i<N; i++ )
		cout <<"队伍"<<Queue[i][0]<<"完成"<<Queue[i][1]<<"道题，耗时"<<Queue[i][2]<<endl;
		
	for(int i = 0; i < N; i++)
		delete[] Queue[i];
	delete[] Queue;	
	
	for(int i = 0; i < M; i++)
		delete[] Submit[i];
	delete[] Submit;	
	
	return 0;	
}
