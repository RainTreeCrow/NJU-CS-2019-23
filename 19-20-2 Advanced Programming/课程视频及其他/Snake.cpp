#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;

#define  _ERROR_    -1	 //错误 
#define  _NULL_      0   //没东西 
#define  _SnakeHead_ 1   //蛇头 
#define  _SnakeBody_ 2   //蛇身体 
#define  _SnakeFood_ 3   //食物 
#define  _GAMING_    8   //游戏中 
#define  _SUSPEND_   7   //暂停中
#define  _Obstacle_  9   //障碍物 
#define  _VICTORY_   10  //胜利 

#define  _MoveUp_    1
#define  _MoveLeft_  2
#define  _MoveDown_  3
#define  _MoveRight_ 4

struct Position{
	int X;
	int Y;
};

struct SnakeBody{
	Position Post;
	int BodyType;
	SnakeBody *Next;
}; 

class Map{
	private:
		int Width;
		int Height;
		
		int **MapCanvas; 
	private:
		void PrintGameMap(){
			
			MapCanvas = new int*[ Width ];
			for ( int i=0; i < Width; i++ )
			{
				MapCanvas[i] = new int[ Height ];
			}
		
			for ( int w=0; w < Width; w++ )
			{
				for (int h=0; h < Height; h++)          
			    {
					MapCanvas[w][h] = _NULL_;
			    }
			} 

			//确定上下边框
			for ( int w=0; w < Width; w++ )
			{
				MapCanvas[w][0] = _Obstacle_;
				MapCanvas[w][Height-1] = _Obstacle_;
			}
			
			//确定左右边框
		    for (int h=0; h < Height; h++)          
		    {
				MapCanvas[0][h] = _Obstacle_;
				MapCanvas[Width-1][h] = _Obstacle_;
		    }
		    
		    //确定信息显示边框
		    for (int h=0; h < Height; h++)          
		    {
				MapCanvas[Width-10][h] = _Obstacle_;
		    }
			
			//打印地图，在打印地图前可以随意设置一下地图中的障碍物，现在默认情况下我没有在程序里设置 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			for (int h=0; h < Height; h++)
			{
				for ( int w=0; w < Width; w++ )          
			    {
					//printf("%d",Map[w][h]);
					if( MapCanvas[w][h] == _Obstacle_ )
						cout<<"■";
					else
						cout<<"  ";
					
			    }
			    cout<<endl;
			}
		}

		void PrintAbout(){
			
			Position AboutInfoPos;
			AboutInfoPos.X = (Width-10)/2-3;
			AboutInfoPos.Y = Height/2-6;
			MoveCursor( AboutInfoPos );
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);	//设置红色
			cout<<"★★一条吃货蛇★★";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			
			AboutInfoPos.X = (Width-10)/2-1;
			AboutInfoPos.Y = Height/2-2;
			MoveCursor( AboutInfoPos );
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);	//设置红色
			cout<<"作者：从前";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			
			AboutInfoPos.X = (Width-10)/2-4;
			AboutInfoPos.Y = Height/2;
			MoveCursor( AboutInfoPos );
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);	//设置蓝色
			cout<<"一个编程爱好者的乐趣:)";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			
			AboutInfoPos.X = (Width-10)/2-2;
			AboutInfoPos.Y = Height/2+4;
			MoveCursor( AboutInfoPos );
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );	//设置一个杂色 
			cout<<"敲回车键开始游戏";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			
			AboutInfoPos.X = (Width-10)/2-2;
			AboutInfoPos.Y = Height/2+6;
			MoveCursor( AboutInfoPos );
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );	//设置一个杂色 
			cout<<"敲ESC键退出游戏 ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		}

	public:
		Map( int wid, int hei ){
			
			Width = wid;
			Height = hei;
			
			PrintGameMap();
		}
		
		~Map(){
			for ( int i=0; i < Width; i++ )
			{
				delete MapCanvas[i];
			}
			delete MapCanvas;
		}
		
		void MoveCursor( Position pos )	//设置光标位置(就是输出显示的开始位置)
		{
			COORD Pos = { pos.X*2, pos.Y };
			HANDLE OutPutHandle = GetStdHandle( STD_OUTPUT_HANDLE );//获得标准输出的句柄   
			SetConsoleCursorPosition( OutPutHandle, Pos ); //设置光标位置
		}
		
		//刷新信息版 
		void RefreshInfoMap( int SnakeLength, int Speed, int Status ){
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE|FOREGROUND_RED);
			Position SnakeLengthInfoPos;
			SnakeLengthInfoPos.X = Width-8;
			SnakeLengthInfoPos.Y = 2;
			MoveCursor( SnakeLengthInfoPos );
			cout<<"蛇长:"<<	SnakeLength;
			
			Position SpeedInfoPos;
			SpeedInfoPos.X = Width-8;
			SpeedInfoPos.Y = 4;
			MoveCursor( SpeedInfoPos );
			cout<<"速度:"<<	Speed;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN|FOREGROUND_RED);
			Position ControlInfoPos;
			ControlInfoPos.X = Width-8;
			ControlInfoPos.Y = Height - 8;
			MoveCursor( ControlInfoPos );
			cout<<"方向键操作";
			
			ControlInfoPos.X = Width-8;
			ControlInfoPos.Y = Height - 10;
			MoveCursor( ControlInfoPos );
			if( Status == _GAMING_ )
				cout<<"回车键暂停";
			else if( Status == _VICTORY_ || Status == _Obstacle_ || Status == _SnakeBody_ )
				cout<<"回车键重玩";
			else 
				cout<<"回车键开始";
			
			ControlInfoPos.X = Width-8;
			ControlInfoPos.Y = Height - 12;
			MoveCursor( ControlInfoPos );
			cout<<"Exc键退出";
			
			ControlInfoPos.X = Width-7;
			ControlInfoPos.Y = Height - 14;
			MoveCursor( ControlInfoPos );
			cout<<"帮  助";
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);

			ControlInfoPos.X = Width-9;
			ControlInfoPos.Y = Height-16;
			MoveCursor( ControlInfoPos );
			cout<<"================";

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			ControlInfoPos.X = Width-8;
			ControlInfoPos.Y = Height - 18;
			MoveCursor( ControlInfoPos );
			cout<<"              "; 
			MoveCursor( ControlInfoPos );
			if( Status == _SUSPEND_ ){
				cout<<"已暂停";
			}else if( Status == _GAMING_ ){
				cout<<"进行中";
			}else if( Status == _VICTORY_ ){
				cout<<"★★Victory★★"; 
			}else if( Status == _Obstacle_ ){
				cout<<"遇到障碍物~"; 
			}else if( Status == _SnakeBody_ ){
				cout<<"吃到自己了~"; 
			}else if( Status == _NULL_ ){
				cout<<"欢迎进入游戏";
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		}
		
		void StartMap(){
			system("cls");
			PrintGameMap();
			RefreshInfoMap( 0, 0, _NULL_ );
		}

		void WelcomeMap(){
			system("cls");
			PrintGameMap();
			PrintAbout();
			RefreshInfoMap( 0, 0, _NULL_ );
		} 

		bool SetFood(){
			Position FoodPos = GetNullPosition();
			
			//当无法放食物时，说明地图已经满了 
			if( FoodPos.X < 0 ){
				return false;
			}
			
			MoveCursor( FoodPos );
			SetValue( FoodPos, _SnakeFood_ );
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			cout << "●";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			return true;
		}
		
		Position GetNullPosition(){
			Position ResultPos, BufferPos;
			BufferPos.X = rand() % (Width-10);
 			BufferPos.Y = rand() % Height;

			ResultPos.X = BufferPos.X;
			ResultPos.Y = BufferPos.Y;
			while( MapCanvas[ResultPos.X][ResultPos.Y] != _NULL_ ){
				ResultPos.X++;
				if( ResultPos.X >= Width-10 ){
					ResultPos.X = 0;
					ResultPos.Y++;
					if( ResultPos.Y >= Height ){
						ResultPos.X = 0;
						ResultPos.Y = 0;
					}
				}
				
				if( ResultPos.X == BufferPos.X && ResultPos.Y == BufferPos.Y )
					break;
			}
		
			if( MapCanvas[ResultPos.X][ResultPos.Y] != _NULL_ )
			{
				//找遍了整张地图都找不到可用的空地了 
				ResultPos.X = -1;
				ResultPos.Y = -1;
			}
			return ResultPos;
		}
		
		void SetValue( Position pos, int value){
			if( pos.X >= Width || pos.X < 0 ) 
				return;
			if( pos.Y >= Height || pos.Y < 0 ) 
				return;
			MapCanvas[pos.X][pos.Y] = value;
		} 
		
		int GetValue( Position pos ){
			if( pos.X >= Width || pos.X < 0 ) 
				return -1;
			if( pos.Y >= Height || pos.Y < 0 ) 
				return -1;
			return MapCanvas[pos.X][pos.Y];
		}
};

class Snake{
	public :
		SnakeBody *Head;
		SnakeBody *Tail;
		int SnakeLength;
		bool Alive;
		int DeadType;
	private:
		//打印一条蛇 
		int PrintSnake( Map *ActiveMap ){
			if (NULL == Head || NULL == ActiveMap)
				return _ERROR_;

			//头的新位置 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			ActiveMap->MoveCursor( Head->Post );
			cout << "◆";

			SnakeBody *Body = Head->Next;
			while( Body ){
				ActiveMap->MoveCursor( Body->Post );
				if( Body->BodyType == _SnakeHead_ )
					cout << "◆"; 
				else if( Body->BodyType == _SnakeBody_ )
					cout << "■";
				Body = Body->Next;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			
			return _NULL_;
		}
	public :
		Snake( int Length ){
			Head = NULL;
			if ( Length <= 0  ){
				return;	
			}

			//建一个蛇头 
			Head = new SnakeBody();
			Head->Next = NULL;
			Head->BodyType = _SnakeHead_;
			Tail = Head;
			
			SnakeLength = 1;
			
			for( int i=1; i<Length; i++ ){
				Add();
			}
			
			DeadType = _NULL_;
			Alive = true;
		}

		~Snake(){
			SnakeBody *Body = Head;
			while( Body ){
				Tail = Body->Next;
				delete Body;
				Body = Tail;
			}
		} 

		//设置蛇出洞的位置 
		int HoleOut( Map *ActiveMap ){
			if (NULL == Head || NULL == ActiveMap)
				return _ERROR_;
			
			//随机初始化蛇的出洞位置
			//随机到边上的时候，如果没注意很快就会挂，这个都是命，不解释，哈哈~ 
			Head->Post = ActiveMap->GetNullPosition();

			SnakeBody *Body = Head->Next;
			while( Body ){
				Body->Post.X = Head->Post.X;
				Body->Post.Y = Head->Post.Y;
				Body = Body->Next;
			}

			return PrintSnake( ActiveMap ); 
		}

		//在地图上移动，的方向
		int Move( Map *ActiveMap, int Direction ){
			if (NULL == Head || NULL == ActiveMap)
				return _ERROR_;

			//足迹 
			Position Footprint;
			Footprint.X = Head->Post.X;
			Footprint.Y = Head->Post.Y;
			
			//头的新位置 
			if( Direction == _MoveUp_ ){
				Head->Post.Y--;
			}else if( Direction == _MoveLeft_ ){
				Head->Post.X--;
			}else if( Direction == _MoveDown_ ){
				Head->Post.Y++;
			}else if( Direction == _MoveRight_ ){
				Head->Post.X++;
			}				

			//Head的下一步移动触碰到了地图中的的什么东西 
			int ResultValue = ActiveMap->GetValue( Head->Post );

			//将新东西存入相应的地图 
			ActiveMap->SetValue( Head->Post, _SnakeHead_ );

			SnakeBody *Body = Head->Next;
			Position BuffPost;
			while( Body ){
				BuffPost.X = Body->Post.X;
				BuffPost.Y = Body->Post.Y;
				
				//Body 要沿着足迹走，虽然没有足，哈哈 
				Body->Post.X = Footprint.X;
				Body->Post.Y = Footprint.Y;
				ActiveMap->SetValue( Body->Post, _SnakeBody_ );
				
				//初始化新的足迹 
				Footprint.X = BuffPost.X;
				Footprint.Y = BuffPost.Y;
				Body = Body->Next;
			}
			
			PrintSnake( ActiveMap );
			
			//尾部足迹消除 
			ActiveMap->MoveCursor(BuffPost);
			cout<< "  ";
			ActiveMap->SetValue( BuffPost, _NULL_ );
			
			return ResultValue;
		}
		
		//新增一节 
		void Add(){
			SnakeBody *Body = NULL;
			Body = new SnakeBody();
			Body->BodyType = _SnakeBody_;
			Body->Post.X = Tail->Post.X;
			Body->Post.Y = Tail->Post.Y; 
			Body->Next = NULL;
			Tail->Next = Body;
			Tail = Body;

			SnakeLength++; 
		}
		
		//获得蛇的长度 
		int GetSnakeLength(){
			return SnakeLength;
		}
		
		//蛇是否活着
		bool IsAlive(){
			return Alive;
		}
		
		//蛇挂了,记录死亡方式 
		void Dead( int Type ){
			DeadType = Type;
			Alive = false;
		} 
		
		//获得死亡方式 
		int DeadReason(){
			return DeadType;
		} 
};


int main(){
	
	//种下随机种子 
	srand((unsigned)time(NULL));
	
	//创建地图 
	Map *map = new Map( 40, 24 );
	map->WelcomeMap(); 

	while(1){
		if( GetAsyncKeyState(VK_RETURN) && 0x0D ){
			//进入游戏 
			map->StartMap();
			//创建一条5节蛇 
			Snake *snake = new Snake( 5 );
			map->RefreshInfoMap( snake->GetSnakeLength(), 0, 1 ); 
			//蛇开始出洞 
			snake->HoleOut( map ); 
			//蛇出洞后的起始方向不定 
			int CtlDir = rand()%4+1;
			//地图中是否还有没吃到的食物 
			bool HaveFood = false; 
			int speed = 1;
			map->RefreshInfoMap( snake->GetSnakeLength(), speed, _GAMING_ ); 
			//开始循环移动	
			while( snake->IsAlive() ){
				
				if ( speed == 1 )
					for(int i=0; i<200000000; i++);
				else if ( speed == 2 )
					for(int i=0; i<150000000; i++);
				else if ( speed == 3 )
					for(int i=0; i<100000000; i++);
				else if ( speed == 4 )
					for(int i=0; i<95000000; i++);
				else
					for(int i=0; i<90000000; i++);
				
				if ( GetAsyncKeyState(VK_UP) && 0x8000 )
			   	{
					if ( CtlDir != _MoveDown_ )
						CtlDir = _MoveUp_;
			   	}else if ( GetAsyncKeyState(VK_RIGHT) && 0x8000 )
			  	{
					if ( CtlDir != _MoveLeft_ )
						CtlDir = _MoveRight_;
			    }else if ( GetAsyncKeyState(VK_LEFT) && 0x8000 )
			    {
			    	if ( CtlDir != _MoveRight_ )
						CtlDir = _MoveLeft_;    
			    }else if ( GetAsyncKeyState(VK_DOWN) && 0x8000 )
			    {
			    	if ( CtlDir != _MoveUp_ )
						CtlDir = _MoveDown_;
			    }else if( GetAsyncKeyState(VK_RETURN) && 0x0D ){
			    	//如果正在游戏中，按回车键，那么进入一个永恒的死循环,表示暂停
					map->RefreshInfoMap( snake->GetSnakeLength(), speed, _SUSPEND_ ); 
					while(1){
						if( GetAsyncKeyState(VK_RETURN) && 0x0D	){
							map->RefreshInfoMap( snake->GetSnakeLength(), speed, _GAMING_ ); 
							break; 
						}
					}
			    }else if( GetAsyncKeyState(VK_ESCAPE) && 0x1B ){
					delete snake;
					delete map; 
					return 0;
				} 

				//随机放一个食物 
				if( !HaveFood ){
					//如果放食物失败，说明没地方放了 
					if( !map->SetFood() ){
						break;
					}else{
						HaveFood = true; 
					}
				}

				//蛇每移动一步所遇到的东西是什么 
				switch( snake->Move( map, CtlDir ) ){
					case _NULL_:
						break;
					case _SnakeBody_:
						snake->Dead( _SnakeBody_ );
					case _SnakeFood_:
						snake->Add();
						HaveFood = false;
						if( snake->GetSnakeLength() >= 10 && snake->GetSnakeLength() < 20  )
							speed = 2;
						else if( snake->GetSnakeLength() >= 20 &&  snake->GetSnakeLength() < 25 )
							speed = 3;
						else if( snake->GetSnakeLength() >= 25 &&  snake->GetSnakeLength() < 30  )
							speed = 4;
						else if( snake->GetSnakeLength() >= 30 ) 
							speed = 5;
						map->RefreshInfoMap( snake->GetSnakeLength(), speed, _GAMING_ );
						break; 
					case _Obstacle_:
						snake->Dead( _Obstacle_ );
						break;
					case _ERROR_: 
						cout << "Game Collapse!!! Map or Snake Create Error!";
						delete snake;
						delete map;
						return 0;	
				}
			}

			if( !snake->IsAlive() )
				map->RefreshInfoMap( snake->GetSnakeLength(), speed, snake->DeadReason() );	
			else
				map->RefreshInfoMap( snake->GetSnakeLength(), speed, _VICTORY_ );
			delete snake;

			//暂停，待玩家确定是否继续游戏 
			while(1){
				if( GetAsyncKeyState(VK_RETURN) && 0x0D ){
					map->WelcomeMap();
					for(int i=0; i<200000000; i++);
					break;
				}if( GetAsyncKeyState(VK_ESCAPE) && 0x1B ){
					delete map; 
					return 0;
				}
			}

		}else if( GetAsyncKeyState(VK_ESCAPE) && 0x1B ){
			delete map; 
			return 0;
		}
	}

	delete map;
}


