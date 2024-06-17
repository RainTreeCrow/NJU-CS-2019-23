module encode83(x,en,y,s,hex);
	input [7:0]x;
	input en;
	output reg [2:0]y;
	output reg s;
	output reg [6:0]hex;
	integer i;
	
	always @(x or en) begin
		if (en) begin
		
		//y = 0;
		//for( i = 0; i <= 7; i = i+1)
		//	if(x[i] == 1) y = i;
		
		casex (x)
			8'b00000000 : y = 0;
			8'b0000001? : y = 1;
			8'b000001?? : y = 2;
			8'b00001??? : y = 3;
			8'b0001???? : y = 4;
			8'b001????? : y = 5;
			8'b01?????? : y = 6;
			8'b1??????? : y = 7;
			default		: y = 0;
		endcase
		
		end
		else y = 0;
		if (en == 0 | x == 0) s = 0;
		else s = 1;
		case (y)
			3'b000 : hex = 7'b1000000;
			3'b001 : hex = 7'b1111001;
			3'b010 : hex = 7'b0100100;
			3'b011 : hex = 7'b0110000;
			3'b100 : hex = 7'b0011001;
			3'b101 : hex = 7'b0010010;
			3'b110 : hex = 7'b0000010;
			3'b111 : hex = 7'b1111000;
			default: hex = 7'b1111111;
		endcase
	end
endmodule
