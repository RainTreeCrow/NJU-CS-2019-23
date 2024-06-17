module adder(cin,a1,b1,carry,result,zero,overflow);
	input cin;
	input [3:0]a1;
	input [3:0]b1;
	output reg carry;
	output reg [3:0]result;
	output reg zero;
	output reg overflow;
	integer i;
	integer b;
	
	always @(cin or a1 or b1) begin
	
		if (cin) begin
			b = (16 - b1) % 16;
			i = !b1[3];
		end
		else begin
			b = b1;
			i = b1[3];
		end
		{carry, result} = a1 + b;
		if (result == 0)
			zero = 1;
		else
			zero = 0;
		overflow = (a1[3]==i) && (result[3]!=a1[3]);
		
	end
endmodule
