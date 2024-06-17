module random(clk,hex1,hex2);
	input clk;
	wire clk_1s;
	wire [7:0] result;
	output [6:0] hex1;
	output [6:0] hex2;

	clk_1s c(clk,clk_1s);
	shift_register sr(clk_1s,result[0]^result[2]^result[3]^result[4],
		3'b101,8'b00000000,result);
	hex h1(result[3:0],hex1);
	hex h2(result[7:4],hex2);
endmodule
