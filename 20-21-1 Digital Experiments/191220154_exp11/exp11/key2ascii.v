module key2ascii(clk,clr,ps2_clk,ps2_dat,en,ascii);

	input clk;
	input clr;
	input ps2_clk;
	input ps2_dat;

	reg [7:0] scancode;
	reg [7:0] times = 0;
	reg caps = 0;
	reg nextdata = 0;
	reg flag = 1;
	wire [7:0] code;
	wire ready,overflow;
	
	output reg en = 1'b1;
	output [7:0] ascii;

	ps2_keyboard p(clk,clr,ps2_clk,ps2_dat,code,ready,nextdata,overflow);
	ascii_ram a(scancode,caps,ascii);

	always @ (posedge clk) begin
		if (ready && nextdata) begin
			nextdata <= 0;
			scancode <= code;
			if (code == 8'h12 || code == 8'h59) caps <= ~caps;
			if (code == 8'hf0) begin
				times <= times + 1;
				flag <= 1;
			end
			else begin
				if (flag) begin
					en <= 0;
					flag <= 0;
					if (code == 8'h58) caps <= ~caps;
				end
				else en <= 1;
			end
		end
		else nextdata <= 1;
	end

endmodule
