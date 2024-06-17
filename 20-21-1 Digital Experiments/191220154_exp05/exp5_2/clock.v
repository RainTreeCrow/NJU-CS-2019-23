module clock(clk,reset,en_alr,in_h,in_m,in_s,alr_h,alr_m,h,m,s,alarm);
	
	input clk;
	input reset;
	input en_alr;
	input [7:0] in_h;
	input [7:0] in_m;
	input [7:0] in_s;
	input [7:0] alr_h;
	input [7:0] alr_m;
	
	output reg [7:0] h;
	output reg [7:0] m;
	output reg [7:0] s;
	output reg alarm = 0;

	always @ (posedge clk) begin
		if (clk) begin
			if (reset)
				s <= in_s + 1;
			else s <= s + 1;
			if (s == 59) begin
				s <= 0;
				if (reset)
					m <= in_m + 1;
				else m <= m + 1;
				if (m == 59) begin
					m <= 0;
					if (reset)
						h <= in_h + 1;
					else h <= h + 1;
					if (h == 23)
						h <= 0;
				end
				else begin
					if (reset)
						h <= in_h;
					else h <= h;
				end
			end
			else begin
				if (reset) begin
					m <= in_m;
					h <= in_h;
				end
				else begin
				m <= m;
				h <= h;
				end
			end
			if (en_alr && h == alr_h && m == alr_m)
				alarm = 1;
			else
				alarm = 0;
		end
		else begin
			if (reset)
				s <= in_s;
			else
				s <= s;
		end
	end
	
endmodule
