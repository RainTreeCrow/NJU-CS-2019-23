module timer(clk,en,clr,min,s,ns);
	input clk;
	input en;
	input clr;
	output reg [7:0] min = 0;
	output reg [7:0] s = 0;
	output reg [7:0] ns = 0;
	
always @ (posedge clk or posedge clr)
	if (clr) begin
		min = 0;
		s = 0;
		ns = 0;
	end
	else if (en) begin
		ns <= ns + 1;
		if (ns == 99) begin
			ns <= 0;
			s <= s + 1;
			if (s == 59) begin
				s <= 0;
				min <= min + 1;
				if (min == 59)
					min <= 0;
			end
		end
	end
	else begin
		min <= min;
		s <= s;
		ns <= ns;
	end
endmodule
