module control(
   input clk,					//系统时钟
	input clr,					//清零
	input ps2_clk,
	input ps2_dat,				//键盘模块接口
	output vga_clk,
	output valid,
	output hsync,
	output vsync,
	output [7:0] vga_r,
	output [7:0] vga_g,
	output [7:0] vga_b,		//显示器模块接口
	output [6:0] hex0,
	output [6:0] hex1			//七段数码管
);

	wire [23:0] vga;				//最终颜色数据
	wire [9:0] h_addr;
	wire [9:0] v_addr;			//屏幕坐标
	wire [8:0] font;				//当前字符行点阵
	wire [7:0] vga_addr;			//vga_ram读出数据
	wire [7:0] ascii;				//当前按键的ascii码
	wire [7:0] ascii_out;		//键盘控制器输出值
	wire [7:0] waste;				//没什么用的虚假寄存器
	wire en;							//键盘使能输出
	wire keyboard_clk;			//键盘时钟
	
	reg [23:0] data = 24'hffffff;		//过程中的颜色数据
	reg [11:0] block_addr = 0;			//vga_ram读出地址
	reg [11:0] index = 0;				//vga_ram写入地址
	reg [11:0] ram_index [29:0];		//用于删除的旧坐标寄存器
	reg [11:0] address;					//font_rom读出地址
	reg [11:0] preindex;					//用于删除的旧坐标变量
	reg [7:0] ascii_data;				//vga_ram写入数据
	reg [3:0] times = 0;					//键盘用计数器
	reg flag = 1;							//判断长按的标志
	reg backspace_state = 1;			//删除状态的标志
	reg enter_state = 1;					//回车换行的标志
	
	assign vga_r = vga[23:16];					//红
	assign vga_g = vga[15:8];					//绿
	assign vga_b = vga[7:0];					//蓝
	assign ascii = ascii_out & {8{en}};		//按键时有效

	clkgen #25000000 clk_v(clk,1'b0,1'b1,vga_clk);
	clkgen #20 clk_k(clk,1'b0,1'b1,keyboard_clk);								//生成两种时钟
	key2ascii k(clk,clr,ps2_clk,ps2_dat,en,ascii_out);							//键盘转ascii码
	vga_ctrl v_C(vga_clk,1'b0,data,h_addr,v_addr,hsync,vsync,valid,
		vga[23:16],vga[15:8],vga[7:0]);												//显示器控制
	font_rom f_r(.address(address),.clock(vga_clk),.q(font));				//字符点阵读取
	vga_ram v_r(block_addr,index,vga_clk,keyboard_clk,1'b0,ascii_data,
		1'b0,1'b1,vga_addr,waste);														//屏幕信息存取
		
	hex h0(ascii[3:0],en,hex0);
	hex h1(ascii[7:4],en,hex1);														//七段数码管调试

	always @ (posedge vga_clk) begin
		block_addr = (v_addr >> 4) * 70 + (h_addr / 9);
		address = (vga_addr << 4) + (v_addr % 16);
		if (h_addr < 8) data = 24'h0000000;
		else if (font[(h_addr + 2) % 9] == 1'b1) data = 24'hffffff;
		else data = 24'h000000;
	end

	always @ (negedge keyboard_clk) begin
		if (index < 70) preindex <= 0;
		else preindex <= ram_index[index / 70 - 1];
	end

	always @ (negedge keyboard_clk) begin
		if (ascii != 8'h0) begin
			if (times == 0) begin
				if (ascii == 8'h0d) begin
					 backspace_state <= 0;
					 ram_index[index / 70] <= index + 1;
                index <= index - (index % 70) + 70;
					 enter_state <= 0;
				end
				else if (ascii == 8'h08) begin
					if (backspace_state == 0) begin
						index <= index;
						backspace_state <= 1'b1;
					end
					else begin
						if (index % 70 == 0) index <= preindex;
						else index <= index - 1;
					end
				end
				else begin
					 if (backspace_state || !enter_state) index <= index;
					 else begin
						if ((index + 1) % 70 == 0) ram_index[(index - 1) / 70] <= index;
						index <= index + 1;
					 end
					 backspace_state <= 0;
					 enter_state <= 1;
				end
				times <= times + 1;
			end
			else if (times == 4'd10) begin
				if (ascii == 8'h0d) index <= index - (index % 70) + 69;
				else if (ascii == 8'h08) begin
					if(index % 70 == 0) index <= preindex;
					else index <= index - 1;
				end
				else begin
					if ((index + 1) % 70 == 0) ram_index[(index - 1) / 70] <= index;							
					index <= index + 1;
				end
			end
			else begin
				index <= index;
				times <= times + 1;
			end
			ascii_data <= ascii;
		end
		else begin		  
			index <= index;
			times <= 0;
		end
		if(index >= 2100) index <= 0;
	end

endmodule
