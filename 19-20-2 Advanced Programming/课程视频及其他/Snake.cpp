#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;

#define  _ERROR_    -1	 //���� 
#define  _NULL_      0   //û���� 
#define  _SnakeHead_ 1   //��ͷ 
#define  _SnakeBody_ 2   //������ 
#define  _SnakeFood_ 3   //ʳ�� 
#define  _GAMING_    8   //��Ϸ�� 
#define  _SUSPEND_   7   //��ͣ��
#define  _Obstacle_  9   //�ϰ��� 
#define  _VICTORY_   10  //ʤ�� 

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

			//ȷ�����±߿�
			for ( int w=0; w < Width; w++ )
			{
				MapCanvas[w][0] = _Obstacle_;
				MapCanvas[w][Height-1] = _Obstacle_;
			}
			
			//ȷ�����ұ߿�
		    for (int h=0; h < Height; h++)          
		    {
				MapCanvas[0][h] = _Obstacle_;
				MapCanvas[Width-1][h] = _Obstacle_;
		    }
		    
		    //ȷ����Ϣ��ʾ�߿�
		    for (int h=0; h < Height; h++)          
		    {
				MapCanvas[Width-10][h] = _Obstacle_;
		    }
			
			//��ӡ��ͼ���ڴ�ӡ��ͼǰ������������һ�µ�ͼ�е��ϰ������Ĭ���������û���ڳ��������� 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			for (int h=0; h < Height; h++)
			{
				for ( int w=0; w < Width; w++ )          
			    {
					//printf("%d",Map[w][h]);
					if( MapCanvas[w][h] == _Obstacle_ )
						cout<<"��";
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
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);	//���ú�ɫ
			cout<<"���һ���Ի��ߡ��";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			
			AboutInfoPos.X = (Width-10)/2-1;
			AboutInfoPos.Y = Height/2-2;
			MoveCursor( AboutInfoPos );
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);	//���ú�ɫ
			cout<<"���ߣ���ǰ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			
			AboutInfoPos.X = (Width-10)/2-4;
			AboutInfoPos.Y = Height/2;
			MoveCursor( AboutInfoPos );
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);	//������ɫ
			cout<<"һ����̰����ߵ���Ȥ:)";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			
			AboutInfoPos.X = (Width-10)/2-2;
			AboutInfoPos.Y = Height/2+4;
			MoveCursor( AboutInfoPos );
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );	//����һ����ɫ 
			cout<<"�ûس�����ʼ��Ϸ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			
			AboutInfoPos.X = (Width-10)/2-2;
			AboutInfoPos.Y = Height/2+6;
			MoveCursor( AboutInfoPos );
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );	//����һ����ɫ 
			cout<<"��ESC���˳���Ϸ ";
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
		
		void MoveCursor( Position pos )	//���ù��λ��(���������ʾ�Ŀ�ʼλ��)
		{
			COORD Pos = { pos.X*2, pos.Y };
			HANDLE OutPutHandle = GetStdHandle( STD_OUTPUT_HANDLE );//��ñ�׼����ľ��   
			SetConsoleCursorPosition( OutPutHandle, Pos ); //���ù��λ��
		}
		
		//ˢ����Ϣ�� 
		void RefreshInfoMap( int SnakeLength, int Speed, int Status ){
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE|FOREGROUND_RED);
			Position SnakeLengthInfoPos;
			SnakeLengthInfoPos.X = Width-8;
			SnakeLengthInfoPos.Y = 2;
			MoveCursor( SnakeLengthInfoPos );
			cout<<"�߳�:"<<	SnakeLength;
			
			Position SpeedInfoPos;
			SpeedInfoPos.X = Width-8;
			SpeedInfoPos.Y = 4;
			MoveCursor( SpeedInfoPos );
			cout<<"�ٶ�:"<<	Speed;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN|FOREGROUND_RED);
			Position ControlInfoPos;
			ControlInfoPos.X = Width-8;
			ControlInfoPos.Y = Height - 8;
			MoveCursor( ControlInfoPos );
			cout<<"���������";
			
			ControlInfoPos.X = Width-8;
			ControlInfoPos.Y = Height - 10;
			MoveCursor( ControlInfoPos );
			if( Status == _GAMING_ )
				cout<<"�س�����ͣ";
			else if( Status == _VICTORY_ || Status == _Obstacle_ || Status == _SnakeBody_ )
				cout<<"�س�������";
			else 
				cout<<"�س�����ʼ";
			
			ControlInfoPos.X = Width-8;
			ControlInfoPos.Y = Height - 12;
			MoveCursor( ControlInfoPos );
			cout<<"Exc���˳�";
			
			ControlInfoPos.X = Width-7;
			ControlInfoPos.Y = Height - 14;
			MoveCursor( ControlInfoPos );
			cout<<"��  ��";
			
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
				cout<<"����ͣ";
			}else if( Status == _GAMING_ ){
				cout<<"������";
			}else if( Status == _VICTORY_ ){
				cout<<"���Victory���"; 
			}else if( Status == _Obstacle_ ){
				cout<<"�����ϰ���~"; 
			}else if( Status == _SnakeBody_ ){
				cout<<"�Ե��Լ���~"; 
			}else if( Status == _NULL_ ){
				cout<<"��ӭ������Ϸ";
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
			
			//���޷���ʳ��ʱ��˵����ͼ�Ѿ����� 
			if( FoodPos.X < 0 ){
				return false;
			}
			
			MoveCursor( FoodPos );
			SetValue( FoodPos, _SnakeFood_ );
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			cout << "��";
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
				//�ұ������ŵ�ͼ���Ҳ������õĿյ��� 
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
		//��ӡһ���� 
		int PrintSnake( Map *ActiveMap ){
			if (NULL == Head || NULL == ActiveMap)
				return _ERROR_;

			//ͷ����λ�� 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			ActiveMap->MoveCursor( Head->Post );
			cout << "��";

			SnakeBody *Body = Head->Next;
			while( Body ){
				ActiveMap->MoveCursor( Body->Post );
				if( Body->BodyType == _SnakeHead_ )
					cout << "��"; 
				else if( Body->BodyType == _SnakeBody_ )
					cout << "��";
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

			//��һ����ͷ 
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

		//�����߳�����λ�� 
		int HoleOut( Map *ActiveMap ){
			if (NULL == Head || NULL == ActiveMap)
				return _ERROR_;
			
			//�����ʼ���ߵĳ���λ��
			//��������ϵ�ʱ�����ûע��ܿ�ͻ�ң�����������������ͣ�����~ 
			Head->Post = ActiveMap->GetNullPosition();

			SnakeBody *Body = Head->Next;
			while( Body ){
				Body->Post.X = Head->Post.X;
				Body->Post.Y = Head->Post.Y;
				Body = Body->Next;
			}

			return PrintSnake( ActiveMap ); 
		}

		//�ڵ�ͼ���ƶ����ķ���
		int Move( Map *ActiveMap, int Direction ){
			if (NULL == Head || NULL == ActiveMap)
				return _ERROR_;

			//�㼣 
			Position Footprint;
			Footprint.X = Head->Post.X;
			Footprint.Y = Head->Post.Y;
			
			//ͷ����λ�� 
			if( Direction == _MoveUp_ ){
				Head->Post.Y--;
			}else if( Direction == _MoveLeft_ ){
				Head->Post.X--;
			}else if( Direction == _MoveDown_ ){
				Head->Post.Y++;
			}else if( Direction == _MoveRight_ ){
				Head->Post.X++;
			}				

			//Head����һ���ƶ��������˵�ͼ�еĵ�ʲô���� 
			int ResultValue = ActiveMap->GetValue( Head->Post );

			//���¶���������Ӧ�ĵ�ͼ 
			ActiveMap->SetValue( Head->Post, _SnakeHead_ );

			SnakeBody *Body = Head->Next;
			Position BuffPost;
			while( Body ){
				BuffPost.X = Body->Post.X;
				BuffPost.Y = Body->Post.Y;
				
				//Body Ҫ�����㼣�ߣ���Ȼû���㣬���� 
				Body->Post.X = Footprint.X;
				Body->Post.Y = Footprint.Y;
				ActiveMap->SetValue( Body->Post, _SnakeBody_ );
				
				//��ʼ���µ��㼣 
				Footprint.X = BuffPost.X;
				Footprint.Y = BuffPost.Y;
				Body = Body->Next;
			}
			
			PrintSnake( ActiveMap );
			
			//β���㼣���� 
			ActiveMap->MoveCursor(BuffPost);
			cout<< "  ";
			ActiveMap->SetValue( BuffPost, _NULL_ );
			
			return ResultValue;
		}
		
		//����һ�� 
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
		
		//����ߵĳ��� 
		int GetSnakeLength(){
			return SnakeLength;
		}
		
		//���Ƿ����
		bool IsAlive(){
			return Alive;
		}
		
		//�߹���,��¼������ʽ 
		void Dead( int Type ){
			DeadType = Type;
			Alive = false;
		} 
		
		//���������ʽ 
		int DeadReason(){
			return DeadType;
		} 
};


int main(){
	
	//����������� 
	srand((unsigned)time(NULL));
	
	//������ͼ 
	Map *map = new Map( 40, 24 );
	map->WelcomeMap(); 

	while(1){
		if( GetAsyncKeyState(VK_RETURN) && 0x0D ){
			//������Ϸ 
			map->StartMap();
			//����һ��5���� 
			Snake *snake = new Snake( 5 );
			map->RefreshInfoMap( snake->GetSnakeLength(), 0, 1 ); 
			//�߿�ʼ���� 
			snake->HoleOut( map ); 
			//�߳��������ʼ���򲻶� 
			int CtlDir = rand()%4+1;
			//��ͼ���Ƿ���û�Ե���ʳ�� 
			bool HaveFood = false; 
			int speed = 1;
			map->RefreshInfoMap( snake->GetSnakeLength(), speed, _GAMING_ ); 
			//��ʼѭ���ƶ�	
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
			    	//���������Ϸ�У����س�������ô����һ���������ѭ��,��ʾ��ͣ
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

				//�����һ��ʳ�� 
				if( !HaveFood ){
					//�����ʳ��ʧ�ܣ�˵��û�ط����� 
					if( !map->SetFood() ){
						break;
					}else{
						HaveFood = true; 
					}
				}

				//��ÿ�ƶ�һ���������Ķ�����ʲô 
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

			//��ͣ�������ȷ���Ƿ������Ϸ 
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


