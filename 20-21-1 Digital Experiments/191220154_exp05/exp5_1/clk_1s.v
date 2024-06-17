module clk_1s(clk,clk_1s);
	input clk;
	output reg clk_1s = 0;
	reg [24:0] count_clk = 1;
	
always @(posedge clk)
	if(count_clk == 25000000)
		begin
			count_clk <= 1;
			clk_1s <= ~clk_1s;
		end
	else
		count_clk <= count_clk + 1;
endmodule
