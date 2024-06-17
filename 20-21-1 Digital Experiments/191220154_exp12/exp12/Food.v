module Food(
	clk,
	random
);

	input clk;
	output [11:0] random;
	reg [11:0] count;

	initial begin
		count = 11'd0;
	end

	always @ (posedge clk) begin
		if (count == 11'd1199)
			count <= 11'd0;
		else
			count <= count + 1'd1;
	end
	
	assign random = count;

endmodule
