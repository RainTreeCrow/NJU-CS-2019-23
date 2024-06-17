module set(en,set_sig,h_m,h,m,s);

	input en;
	input set_sig;
	input h_m;
	output reg [7:0] h = 0;
	output reg [7:0] m = 0;
	output reg [7:0] s = 0;

	always @ (negedge set_sig) begin
		if (en) begin
			if (!h_m) begin
				h <= h + 1;
				if (h == 23)
					h <= 0;
			end
			else begin
				m <= m + 1;
				if (m == 59) begin
					m <= 0;
					h <= h + 1;
					if (h == 23)
						h <= 0;
				end
			end
		end
	end
	
endmodule
