module exp5_1(clk,en,clr,hex1,hex2,finish);
	input clk;
	input en;
	input clr;
	wire [3:0] out1;
	wire [3:0] out2;
	output [6:0] hex1;
	output [6:0] hex2;
	output finish;
	
	clk_1s c(clk,clk_1s);
	counter ct(clk_1s,en,clr,out1,out2,finish);
	hex h1(out1,hex1);
	hex h2(out2,hex2);
endmodule
