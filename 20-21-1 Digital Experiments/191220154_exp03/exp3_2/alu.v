module alu(s,a1,b1,result,carry,overflow);
	input [2:0]s;
	input [3:0]a1;
	input [3:0]b1;
	output reg [3:0]result;
	output reg carry;
	output reg overflow;
	integer i;
	integer b;
	
	always @(s or a1 or b1) begin
	
		case (s)
			3'b000 : begin
				b = b1;
				i = b1[3];
				{carry, result} = a1 + b;
				overflow = (a1[3]==i) && (result[3]!=a1[3]);
			end
			3'b001 : begin
				b = (16 - b1) % 16;
				i = !b1[3];
				{carry, result} = a1 + b;
				overflow = (a1[3]==i) && (result[3]!=a1[3]);
			end
			3'b010 : begin
				result = ~a1;
				carry = 0;
				overflow = 0;
			end
			3'b011 : begin
				result = a1 & b1;
				carry = 0;
				overflow = 0;
			end
			3'b100 : begin
				result = a1 | b1;
				carry = 0;
				overflow = 0;
			end
			3'b101 : begin
				result = a1 ^ b1;
				carry = 0;
				overflow = 0;
			end
			3'b110 : begin
				result = 4'b0000;
				if (a1[3]==1 && b1[3]==0) carry = 0;
				else if (a1[3]==0 && b1[3]==1) carry = 1;
				else carry = (a1>b1) ? 1:0;
				overflow = 0;
			end
			3'b111 : begin
				result = 4'b0000;
				if (a1 == b1) carry = 1;
				else carry = 0;
				overflow = 0;
			end
			default : begin
				result = 4'b0000;
				carry = 0;
				overflow = 0;
			end
		endcase
		
	end
endmodule
