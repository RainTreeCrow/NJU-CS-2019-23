module clk_1s(clk,clk_1s);

	input clk;
	output reg clk_1s = 0;
	reg [6:0] count_clk = 0;

	always @ (posedge clk) begin
		if(count_clk == 50) begin
			clk_1s <= ~clk_1s;
			count_clk <= 0;
		end
		else count_clk <= count_clk + 1;
	end
	
endmodule
