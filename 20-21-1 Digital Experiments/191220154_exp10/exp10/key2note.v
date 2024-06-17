module key2note(
	input clk,
	input clrn,
	output reg en,
	output reg [15:0] freq,
	inout ps2_clk,
	inout ps2_dat,
	output reg [8:0] volumn
);

	initial begin
		volumn = 9'b000111000;
	end

	wire [7:0] code;
	wire ready,overflow;
	reg nextdata = 0;
	reg flag = 0;
	reg [7:0] scancode;
	
	ps2_keyboard board(clk,clrn,ps2_clk,ps2_dat,code,ready,nextdata,overflow);

	always @ (posedge clk) begin
		if (ready && nextdata == 1'b1) begin
			nextdata <= 0;
			scancode <= code;
			if (code == 8'hf0) flag <= 1;
			else begin
				if (flag) begin
					en <= 0;
					flag <= 0;
					if (code == 8'h41) volumn[6:0] = volumn[6:0] - 9'd1;
					if (code == 8'h49) volumn[6:0] = volumn[6:0] + 9'd1;
				end
				else en <= 1;
			end
		end
		else nextdata <= 1;
	end

	always @(scancode) begin
		case (scancode)
			8'h15	 : freq = 16'd714;
			8'h1d	 : freq = 16'd802;
			8'h24	 : freq = 16'd900;
			8'h2d	 : freq = 16'd954;
			8'h2c	 : freq = 16'd1070;
			8'h35	 : freq = 16'd1201;
			8'h3c	 : freq = 16'd1349;
			8'h43	 : freq = 16'd1429;

			8'h1c  : freq = 16'd757;
			8'h1b  : freq = 16'd850;
			8'h2b  : freq = 16'd1010;
			8'h34  : freq = 16'd1134;
			8'h33  : freq = 16'd1273;
			8'h42  : freq = 16'd1514;
			
			default: freq = 16'd0;
		endcase
	end

endmodule
