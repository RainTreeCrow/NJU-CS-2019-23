module Snake(
	clk,
	ps2_clk,
	ps2_data,
	vga_clk,
	vga_hs,
	vga_vs,
	vga_blank_n,
	vga_r,
	vga_g,
	vga_b,
	hex0,
	hex1,
	game_state,
	game_clock
);

	input clk;									//系统时钟
	input ps2_clk,ps2_data;					//键盘相关
	output vga_clk,vga_hs,vga_vs,vga_blank_n;
	output [7:0] vga_r;
	output [7:0] vga_g;
	output [7:0] vga_b;						//显示器相关
	output [6:0] hex0;
	output [6:0] hex1;						//分数显示		

	wire run;									//开始/暂停
	wire restart;								//重玩
	output game_clock;						//游戏时钟
	wire [1:0] direction;					//方向
	reg [1:0] board [1199:0];				//棋盘格
	reg [11:0] snake [15:0];				//蛇行坐标
	reg [3:0] snake_head_index;			//蛇头指针
	reg [3:0] snake_tail_index;			//蛇尾指针
	reg [11:0] food;							//食物坐标
	wire [11:0] random;						//随机生成坐标
	reg [7:0] score;							//得分  
	integer i;
	integer j;									//循环用计数器
	integer new_head_index;
	integer new_tail_index;					//蛇头尾临时指针
	reg eaten;									//食物是否被吃
	reg dead;									//蛇是否死亡
	reg win;										//游戏是否通关
	output game_state;						//游戏状态（是否进入循环）
	wire reset_game;							//重置游戏信息

	wire nextdata_n;
	wire [7:0] data;
	wire ready;
	wire overflow;								//键盘相关

	wire [9:0] h_addr;
	wire [9:0] v_addr;
	reg [18:0] addr = 19'h0;
	wire out_win_data;
	wire out_lose_data;
	reg [1:0] vga_state;
	reg [23:0] vga_data = 24'hffffff;	//显示器相关
	
	assign game_state = run && !win && !dead;
	//如果玩家没有暂停，没有通关，蛇也没死，游戏时钟恰好经过一秒则进入循环
	assign reset_game = restart;
	//重置游戏信息

	clk_1s c_1s(clk,game_clock);
	clkgen #(25000000) my_clkgen(clk,1'b0,1'b1,vga_clk);
	//游戏时钟和VGA时钟信号的生成
	
	ps2_keyboard ps(clk,1'b1,ps2_clk,ps2_data,data,ready,nextdata_n,overflow);
	kbd_output kbd(clk,ready,overflow,data,direction,nextdata_n,run,restart);
	//从键盘模块获得玩家指令

	Food f(clk,random);
	//通过循环计数器获得随机行列坐标
	
	win_picture wp(addr,clk,out_win_data);
	lose_picture lp(addr,clk,out_lose_data);
	//通关信息显示图片
	vga_ctrl my_vga(vga_clk,1'b0,vga_data,h_addr,v_addr,
		vga_hs,vga_vs,vga_blank_n,vga_r,vga_g,vga_b);
	//显示器控制模块
	
	hex h0(score[3:0],1'b1,hex0);
	hex h1(score[7:4],1'b1,hex1);
	//七段数码管显示分数
	
	always @ (v_addr or h_addr) begin
		if (win) begin
			addr = v_addr + (h_addr - 1) * 512 - 1;
			case (out_win_data)
				1'b1:	vga_data = 24'h00ff00;
				1'b0: vga_data = 24'h000000;
				default : vga_data = 24'hffffff;
			endcase
		end
		else if (dead) begin
			addr = v_addr + (h_addr - 1) * 512 - 1;
			case (out_lose_data)
				1'b1: vga_data = 24'hff0000;
				1'b0: vga_data = 24'h000000;
				default: vga_data = 24'hffffff;
			endcase
		end
		else begin
			vga_state = board[(v_addr >> 4) * 40 + (h_addr >> 4)];
			case (vga_state)
				NULL:		vga_data = 24'h000000;		//黑色，代表空地
				SNAKE:	vga_data = 24'h00ff00;		//绿色，代表蛇
				FOOD:		vga_data = 24'hff0000;		//红色，代表食物
				WALL:		vga_data = 24'h0000ff;		//蓝色，代表墙
				default:	vga_data = 24'hffffff;
			endcase
		end
	end

	localparam
		UP = 2'd0,
		DOWN = 2'd1,
		LEFT = 2'd2,
		RIGHT = 2'd3;
		//方向上下左右
	
	localparam
		NULL = 2'd0,
		SNAKE = 2'd1,
		FOOD = 2'd2,
		WALL = 2'd3;
		//棋盘格信息

	always @ (posedge game_clock) begin
		if (game_state) begin
			new_head_index = (snake_head_index + 1) % 15;
			new_tail_index = (snake_tail_index + 1) % 15;
			//蛇为循环数组
			case (direction)
				UP: begin
					snake[new_head_index] = snake[snake_head_index] - 40;
				end
				DOWN: begin
					snake[new_head_index] = snake[snake_head_index] + 40;
				end
				LEFT: begin
					snake[new_head_index] = snake[snake_head_index] - 1;
				end
				RIGHT: begin
					snake[new_head_index] = snake[snake_head_index] + 1;
				end
			endcase
			//根据方向设置新头的坐标位置
			case (board[snake[new_head_index]])
				NULL: begin
					board[snake[new_head_index]] = SNAKE;
					board[snake[snake_tail_index]] = NULL;
					snake_head_index = new_head_index;
					snake_tail_index = new_tail_index;
				end
				//如果是空的，则旧蛇尾所在地设为空，新蛇头所在地设为蛇
				SNAKE: dead = 1'b1;
				//如果是蛇，说明撞上了自己，蛇死了
				FOOD: begin
					board[snake[new_head_index]] = SNAKE;
					snake_head_index = new_head_index;
					eaten = 1'b1;
					score = score + 1;
					if (score == 10)
						win = 1'b1;
				end
				//如果是食物，则旧蛇尾不变，食物所在地设为蛇，蛇吃掉食物并获得增长
				//如果更新后的蛇头与蛇尾指针下标重合，说明蛇满10节，游戏获胜
				WALL: dead = 1'b1;
				//如果是墙，说明撞到了墙，蛇也死了
			endcase
			if (eaten) begin
			//如果食物被吃则需要重新生成
				if (board[random] == NULL) begin
				//如果生成地为空则放置，否则继续生成
					food = random;
					board[food] = FOOD;
					eaten = 1'b0;
					//放置并修改信息
				end
			end
		end
		if (reset_game) begin
			for (i = 0; i < 1200; i = i + 1)
				board[i] = NULL;
			for (j = 0; j < 40; j = j + 1) begin
				board[j] = WALL;
				board[1160 + j] = WALL;
			end
			for (i = 1; i < 29; i = i + 1) begin
				board[i * 40] = WALL;
				board[i * 40 + 39] = WALL;
			end
			for (j = 10; j < 20; j = j + 1)
				board[400 + j] = WALL;
			for (j = 20; j < 30; j = j + 1)
				board[760 + j] = WALL;
			for (i = 10; i < 20; i = i + 1) begin
				board[i * 40 + 10] = WALL;
				board[i * 40 + 29] = WALL;
			end
			//初始化四周是墙，中间留空
			board[82] = SNAKE;
			board[83] = SNAKE;
			snake_head_index = 4'd1;
			snake_tail_index = 4'd0;
			snake[0] = 11'd82;
			snake[1] = 11'd83;
			//把蛇放在右上角，进行初始化
			eaten = 1'b1;
			dead = 1'b0;
			win = 1'b0;
			score = 8'd0;
			//设置食物被吃（即此时需要随机生成）
			//蛇没死，游戏也没有通关
			//重置游戏信息
		end
	end

endmodule
