module counter(clk,en,clr,out_q1,out_q2,finish);
	input clk;
	input en;
	input clr;
	output reg [3:0] out_q1 = 4'b0000;
	output reg [3:0] out_q2 = 4'b0000;
	output reg finish = 0;
	
always @ (posedge clk or posedge clr)
	if (clr) begin
		out_q1 = 0;
		out_q2 = 0;
	end
	else if (en) begin
		out_q1 <= out_q1 + 1;
		if (out_q1 == 9) begin
			out_q1 <= 0;
			out_q2 <= out_q2 + 1;
		end
		if (out_q1 == 9 && out_q2 == 9) begin
			out_q1 <= 0;
			out_q2 <= 0;
			finish = 1;
		end
		else if (out_q1 == 0 && out_q2 == 0)
			finish = 0;
	end
	else begin
		out_q1 <= out_q1;
		out_q2 <= out_q2;
	end
endmodule
