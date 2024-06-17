module exp7_2(clk,we,inaddr,outaddr,din,hex1_1,hex1_2,hex2_1,hex2_2);
	input clk;
	input we;
	input [2:0] inaddr;
	input [2:0] outaddr;
	input [2:0] din;
	output [6:0] hex1_1;
	output [6:0] hex1_2;
	output [6:0] hex2_1;
	output [6:0] hex2_2;
	
	wire [7:0] dout1;
	wire [7:0] dout2;
	
	ram_1 r1(clk,we,inaddr,outaddr,din,dout1);
	ram_2 r2(clk,din,outaddr,inaddr,we,dout2);
	hex h1_1(dout1[3:0],hex1_1);
	hex h1_2(dout1[7:4],hex1_2);
	hex h2_1(dout2[3:0],hex2_1);
	hex h2_2(dout2[7:4],hex2_2);

endmodule
