module datapath_sequence (
	input        clk           , // Clock
	input        rst_n         , // Asynchronous reset active low
	input  [7:0] address       ,
	input        ld_colour     ,
	input        next_colour   ,
	input        ld_value      ,
	input        reset_counter ,
	input        enable_counter,
	input  [8:0] x_input       ,
	input  [8:0] y_input       ,
	output [8:0] x             ,
	output [8:0] y             ,
	output [5:0] colour_out    ,
	output [5:0] counter
);

	wire [24:0] colour_data;

char_colour i_char_colour (
	.clk        (clk        ),
	.rst_n      (rst_n      ),
	.colour_data(colour_data),
	.ld_colour  (ld_colour  ),
	.next_colour(next_colour),
	.colour_out (colour_out )
);

char_coordinate i_char_coordinate (
	.clk           (clk           ),
	.rst_n         (rst_n         ),
	.ld_value      (ld_value      ),
	.reset_counter (reset_counter ),
	.enable_counter(enable_counter),
	.x_input       (x_input       ),
	.y_input       (y_input       ),
	.x             (x             ),
	.y             (y             ),
	.counter       (counter       )
);



pixel_decoder i_pixel_decoder (
	.address(address), 
	.colour_data(colour_data)
	);

endmodule

module char_coordinate (
	input            clk           , // Clock
	input            rst_n         , // Asynchronous reset active low
	input            ld_value      ,
	input            reset_counter ,
	input            enable_counter,
	input      [8:0] x_input       ,
	input      [8:0] y_input       ,
	output reg [8:0] x             ,
	output reg [8:0] y             ,
	output reg [5:0] counter
);
	reg [8:0] x_start;
	reg [8:0] y_start;
	always@(posedge clk) begin
		if(~rst_n || reset_counter) begin
			counter <= 0;
			x       <= 0;
			y       <= 0;
		end // if(~rst_n)
		else begin
			//values for a starting coordinate to print the character
			if (ld_value) begin
				x_start <= x_input;
				y_start <= y_input;
				y <= y_input;
				x <= x_input;
			end // if (ld_)
			else if (enable_counter) begin
				if (counter[2:0] == 3'b100) begin
					counter[5:3] <= counter[5:3] +1;
					counter[2:0] <= 0;
				end
				else counter <= counter + 1;
			y <= y_start + (4*counter[5:3]);
			x <= x_start + (4*counter[2:0]);
			end // if (enable_counter)
		end // else
	end // always@(posedge clk)
endmodule // datapath_sequence








//gets next pixel colour on enable
//colour needs to be initially loaded
module char_colour (
	input             clk        , // Clock
	input             rst_n      , // Asynchronous reset active low
	input      [24:0] colour_data,
	input             ld_colour  ,
	input             next_colour,
	output reg [5:0] colour_out
);

	reg [24:0]colour;

	always@(posedge clk) begin
		if(~rst_n) begin
			colour <= 24'd0;
		end
		else if(ld_colour) begin
			colour <= colour_data;
		end
		else if(next_colour) begin
			colour <= (colour<<24'd1);
		end
		colour_out <= (!colour[24]) ? 6'b000000 : 6'b111111;
	end // always@(clk)

endmodule


//acts like memory, when given a address it outputs a character
module pixel_decoder(address,colour_data);
input [7:0]address;
output reg [24:0] colour_data;

always@(*) begin
	case(address)
		//0
		8'h45 : colour_data = 25'b01100_10010_11010_10110_01100;
		//1
		8'h16 : colour_data = 25'b00010_00110_01010_00010_00010;
		//2
		8'h1E : colour_data = 25'b11100_00010_00100_01000_11110;
		//3
		8'h26 : colour_data = 25'b11100_00010_01100_00010_11100;
		//4
		8'h25 : colour_data = 25'b00110_01010_10010_01111_00010;
		//5
		8'h2E : colour_data = 25'b01110_10000_11100_00010_11100;
		//6
		8'h36 : colour_data = 25'b01100_10000_11100_10010_01100;
		//7
		8'h3D : colour_data = 25'b11110_00010_00100_01000_01000;
		//8
		8'h3E : colour_data = 25'b01100_10010_01100_10010_01100;
		//9
		8'h46 : colour_data = 25'b01100_10010_01110_00010_01100;

		//A
		8'h1C : colour_data = 25'b01100_10010_10010_11110_10010;
		//B
		8'h32 : colour_data = 25'b11100_10010_11100_10010_11100;
		//C
		8'h21 : colour_data = 25'b01100_10010_10000_10010_01100;
		//D
		8'h23 : colour_data = 25'b11100_10010_10010_10010_11100;
		//E
		8'h24 : colour_data = 25'b11110_10000_11100_10000_11110;
		//F
		8'h2B : colour_data = 25'b11110_10000_11100_10000_10000;
		//G
		8'h34 : colour_data = 25'b01100_10000_10110_10010_01100;
		//H
		8'h33 : colour_data = 25'b10010_10010_11110_10010_10010;
		//I
		8'h43 : colour_data = 25'b11100_01000_01000_01000_11100;
		//J
		8'h3B : colour_data = 25'b00110_00010_00010_10010_01100;
		//K
		8'h42 : colour_data = 25'b10010_10100_11000_10100_10010;
		//L
		8'h4B : colour_data = 25'b10000_10000_10000_10000_11110;
		//M
		8'h3A : colour_data = 25'b10001_11011_10101_10001_10001;
		//N
		8'h31 : colour_data = 25'b10010_11010_10110_10010_10010;
		//O
		8'h44 : colour_data = 25'b01100_10010_10010_10010_01100;
		//P
		8'h4D : colour_data = 25'b11100_10010_11100_10000_10000;
		//Q
		8'h15 : colour_data = 25'b01100_10010_10010_10010_01111;
		//R
		8'h2D : colour_data = 25'b11100_10010_11100_10010_10010;
		//S
		8'h1B : colour_data = 25'b01110_10000_01100_00010_11100;
		//T
		8'h2C : colour_data = 25'b11111_00100_00100_00100_00100;
		//U
		8'h3C : colour_data = 25'b10010_10010_10010_10010_01100;
		//V
		8'h2A : colour_data = 25'b10010_10010_10010_10100_01000;
		//W
		8'h1D : colour_data = 25'b10001_10001_10101_10101_01010;
		//X
		8'h22 : colour_data = 25'b10010_11010_01100_10110_10010;
		//Y
		8'h35 : colour_data = 25'b10010_10010_11100_00100_01000;
		//Z
		8'h1A : colour_data = 25'b11110_00010_01100_10000_11110;


		//.
		8'h49 : colour_data = 25'b00000_00000_00000_00000_00100;
		//!
		//CORRESPONDING KEYBOARD SCAN CODE FOR F1
		8'h05 : colour_data = 25'b00100_00100_00100_00000_00100;
		//%
		//CORRESPONDING KEYBOARD SCAN CODE FOR F2
		8'h06 : colour_data = 25'b01010_00010_00100_01000_01010;
		//HAPPY FACE
		//CORRESPONDING KEYBOARD SCAN CODE FOR F3
		8'h04 : colour_data = 25'b01010_01010_00000_10001_01110;

		default : colour_data = 25'b00000_00000_00000_00000_00000;
		endcase // address
		end// always@(*)
		endmodule // module
