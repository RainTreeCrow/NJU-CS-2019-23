module snake
	(
		CLOCK_50,						//	On Board 50 MHz
		// Your inputs and outputs here
      SW,
		KEY,
		// The ports below are for the VGA output.  Do not change.
		VGA_CLK,   						//	VGA Clock
		VGA_HS,							//	VGA H_SYNC
		VGA_VS,							//	VGA V_SYNC
		VGA_BLANK_N,						//	VGA BLANK
		VGA_SYNC_N,						//	VGA SYNC
		VGA_R,   						//	VGA Red[9:0]
		VGA_G,	 						//	VGA Green[9:0]
		VGA_B,   						//	VGA Blue[9:0]
		HEX0, 
		HEX1
	);

	input			CLOCK_50;				//	50 MHz
	input   [9:0]   SW;
	input   [3:0]   KEY;

	// Declare your inputs and outputs here
	// Do not change the following outputs
	output			VGA_CLK;   				//	VGA Clock
	output			VGA_HS;					//	VGA H_SYNC
	output			VGA_VS;					//	VGA V_SYNC
	output			VGA_BLANK_N;				//	VGA BLANK
	output			VGA_SYNC_N;				//	VGA SYNC
	output	[9:0]	VGA_R;   				//	VGA Red[9:0]
	output	[9:0]	VGA_G;	 				//	VGA Green[9:0]
	output	[9:0]	VGA_B;   				//	VGA Blue[9:0]
	output [6:0] HEX0, HEX1;
	
	// Create the colour, x, y and writeEn wires that are inputs to the controller.
	wire [2:0] colour;
	wire [7:0] x;
	wire [6:0] y;
	wire [7:0] score;
	wire writeEn;

	// Create an Instance of a VGA controller - there can be only one!
	// Define the number of colours as well as the initial background
	// image file (.MIF) for the controller.
	vga_adapter VGA(
			.resetn(~SW[0]),
			.clock(CLOCK_50),
			.colour(colour),
			.x(x),
			.y(y),
			.plot(writeEn),
			/* Signals for the DAC to drive the monitor. */
			.VGA_R(VGA_R),
			.VGA_G(VGA_G),
			.VGA_B(VGA_B),
			.VGA_HS(VGA_HS),
			.VGA_VS(VGA_VS),
			.VGA_BLANK(VGA_BLANK_N),
			.VGA_SYNC(VGA_SYNC_N),
			.VGA_CLK(VGA_CLK));
		defparam VGA.RESOLUTION = "160x120";
		defparam VGA.MONOCHROME = "FALSE";
		defparam VGA.BITS_PER_COLOUR_CHANNEL = 1;
		defparam VGA.BACKGROUND_IMAGE = "black.mif";

		
	combined u0(
						.CLOCK_50(CLOCK_50),
						.resetn(~SW[0]),
						.level(SW[9:8]),
						.up(~KEY[3]),
						.down(~KEY[2]),
						.left(~KEY[1]),
						.right(~KEY[0]),
						.x_out(x),
						.y_out(y),
						.colour_out(colour),
						.plot(writeEn),
						.score(score)
						);
	
	 hex_decoder H0(
        .hex_digit(score[3:0]), 
        .segments(HEX0)
        );
        
    hex_decoder H1(
        .hex_digit(score[7:4]), 
        .segments(HEX1)
        );
    

endmodule

module combined(CLOCK_50, resetn, level, up, down, left, right, x_out, y_out, colour_out, plot, score);
	input CLOCK_50, resetn, up, down, left, right;
	input [1:0]level;
	wire [7:0]x_in;
	wire [6:0]y_in;
	wire [2:0]colour_in;
	wire ld_x, ld_y, draw, erase;
	wire [7:0]data_x;
	wire [6:0]data_y;
	wire [2:0]data_colour;
	wire [7:0]restart_x;
	wire [6:0]restart_y;
	wire [2:0]restart_colour;
	wire restart;
	reg [23:0]level_rate;
	output [7:0]x_out;
	output [6:0]y_out;
	output [2:0]colour_out;
	output plot;
	output [7:0]score;
	
	always@(*)
		begin
			case(level)
				2'b00: level_rate <= 24'd12500000;
				2'b01: level_rate <= 24'd10000000;
				2'b10: level_rate <= 24'd7500000;
				2'b11: level_rate <= 24'd5000000;
			endcase
		end				

	control u0(
				 .CLOCK_50(CLOCK_50), 
				 .resetn(resetn), 
				 .up(up), 
				 .down(down), 
				 .left(left), 
				 .right(right), 
				 .x_count(x_in), 
				 .y_count(y_in), 
				 .colour(colour_in), 
				 .ld_x(ld_x), 
				 .ld_y(ld_y), 
				 .draw(draw), 
				 .erase(erase), 
				 .plot(plot),
				 .restart(restart),
				 .level_rate(level_rate),
				 .score(score)
				 );
	
				 
	datapath u1(
					.x_in(x_in), 
					.y_in(y_in), 
					.colour_in(colour_in), 
					.clock(CLOCK_50), 
					.resetn(resetn), 
					.ld_x(ld_x), 
					.ld_y(ld_y), 
					.draw(draw), 
					.erase(erase), 
					.x_out(data_x), 
					.y_out(data_y), 
					.colour_out(data_colour)
					);
					
	restart u2(
				  .resetn(resetn), 
				  .clock(CLOCK_50), 
				  .x_out(restart_x), 
				  .y_out(restart_y), 
				  .colour_out(restart_colour)
				  );
	assign colour_out = (restart) ? restart_colour : data_colour;
	assign x_out = (restart) ? restart_x : data_x;
	assign y_out = (restart) ? restart_y : data_y;
endmodule
	
module random_x_counter(CLOCK_50, resetn, random_x);
	input CLOCK_50;
	input resetn;
	output [5:0]random_x;
	reg [5:0]count;
	initial begin
		count = 6'd0;
		end
	always@(posedge CLOCK_50)
		begin
		if (!resetn)
			count <= 6'd0;
		else 
			begin
				if (count == 6'd39)
					count <= 6'd0;
			else
				count <= count + 1'd1;
			end
		end
	assign random_x = count;
endmodule

module random_y_counter(CLOCK_50, resetn, random_y);
	input CLOCK_50;
	input resetn;
	output [4:0]random_y ;
	reg [4:0]count;
	initial begin
		count = 5'd0;
		end
	always@(posedge CLOCK_50)
		begin 
		if (!resetn)
			count <= 5'd0;
		else
			begin
				if (count == 5'd29)
					count <= 5'd0;
				else
					count <= count + 1'd1;
			end
		end
	assign random_y = count;
endmodule

module datapath(x_in, y_in, colour_in, clock, resetn, ld_x, ld_y, draw, erase, x_out, y_out, colour_out);
	input [7:0]x_in;
	input [6:0]y_in;
	input [2:0]colour_in;
	input clock, resetn, ld_x, ld_y, draw, erase;
	output [7:0]x_out;
	output [6:0]y_out;
	output [2:0]colour_out;
	reg [3:0]count;
	initial begin
		count = 4'b0000;
		end
	
	assign x_out = x_in + count[1:0];
	assign y_out = y_in + count[3:2];
	assign colour_out = (draw) ? colour_in : 3'b000;
	
		
	always@(posedge clock)
		begin
			if(!resetn)
				count <= 4'b0000;
			else if(draw || erase)
				begin
					if(count == 4'b1111)
						count <= 4'b0000;
					else
						count <= count + 1'b1;
				end
		end
endmodule

module restart(resetn, clock, x_out, y_out, colour_out);
	input resetn, clock;
	output [7:0]x_out;
	output [6:0]y_out;
	output [2:0]colour_out;
	reg [7:0]x_count;
	reg [6:0]y_count;
	initial
		begin
			x_count = 8'd0;
			y_count = 7'd0;
		end
	
	always@(posedge clock)
		begin
			if(!resetn)
				x_count <= 8'd0;
			else
				begin
					if(x_count == 8'd160)
						x_count <= 8'd0;
					else
						x_count <= x_count + 8'd1;
				end
		end
		
	always@(posedge clock)
		begin
			if(!resetn)
				y_count <= 7'd0;
			else
				begin
					if(y_count == 7'd120)
						y_count <= 7'd0;
					else if(x_count == 8'd0)
						y_count <= y_count + 7'd1;
				end
		end
		
	assign x_out = x_count;
	assign y_out = y_count;
	assign colour_out = 3'b000;
endmodule
	
module control(CLOCK_50, resetn, up, down, left, right, x_count, y_count, colour, ld_x, ld_y, draw, erase, plot, restart, level_rate, score);
	input CLOCK_50, resetn, up, down, left, right;
	input [23:0]level_rate;
	output reg [7:0]x_count;
	output reg [6:0]y_count;
	output reg ld_x, ld_y, draw, erase, plot, restart;
	output reg [2:0] colour;
	reg [1:0]direction; //up:00, down:01, left:10, right:11
	reg [4:0]current_state, next_state;
	reg [14:0] snake[0:127]; //stores postion,i.e., {tail_x, tail_y, body2_x, body2_y, body1_x, body1_y, head_x, head_y}
	reg [14:0] food; //food's postion,i.e., {oldx ,oldy, newx, newy}
	reg [4:0] draw_erase_count;
	reg [23:0] delay_count;
	reg [14:0] restart_count;
	reg collide;
	reg eat;
	reg [6:0]length;
	reg enter_tunnel1;
	reg enter_tunnel2;
	output reg [7:0]score;
	integer index;
	wire [5:0]random_x;
	wire [4:0]random_y;
	wire [7:0]random_food_x;
	wire [6:0]random_food_y;
	assign random_food_x = {random_x, 2'b00};
	assign random_food_y = {random_y, 2'b00};
	
	random_x_counter u0(
							 .CLOCK_50(CLOCK_50),
							 .resetn(resetn),
							 .random_x(random_x)
							 );
	random_y_counter u1(
							 .CLOCK_50(CLOCK_50),
							 .resetn(resetn),
							 .random_y(random_y)
							 );
	
	localparam  START = 5'd0,
					DRAW_HEAD = 5'd1,
					DRAW_BODY1 = 5'd2,
					DRAW_BODY2 = 5'd3,
					DRAW_TAIL = 5'd4,
					DRAW_FOOD = 5'd5,
					WAIT = 5'd6,
					ERASE_TAIL = 5'd7,
					SHIFT = 5'd8,
					UPDATE_POSITION = 5'd9,
					UPDATE_POSITION1 = 5'd10,
					CHECK = 5'd11,
					DRAW_NEW1 = 5'd12,
					DRAW_NEW2 = 5'd13,
					DRAW_NEW3 = 5'd14,
					DRAW_NEW4 = 5'd15,
					UPDATE_HEAD = 5'd16,
					UPDATE_FOOD = 5'd17,
					DELAY = 5'd18,
					RESTART = 5'd19,
					DRAW_OBSTACLE1 = 5'd20,
					DRAW_OBSTACLE2 = 5'd21,
					DRAW_TUNNEL1 = 5'd22,
					DRAW_TUNNEL2 = 5'd23;
	
	initial begin
		snake[0] = {8'd60, 7'd60};
		snake[1] = {8'd56, 7'd60};
		snake[2] = {8'd52, 7'd60};
		snake[3] = {8'd48, 7'd60};
		for (index = 4; index < 128; index = index +1) begin
			snake[index] = {8'd48, 7'd60};
		end
		food = {8'd80, 7'd40};
		collide = 0;
		eat = 0;
		length = 7'd4;
		score = 7'd0;
		direction = 2'b11;
		current_state = START;
		draw_erase_count = 5'b0;
		delay_count = 24'b0;
		restart = 0;
	end
	
	always @(*)
		begin: states
			case (current_state)
				START: next_state = DRAW_HEAD;
				DRAW_HEAD: next_state = (draw_erase_count == 5'd21) ? DRAW_BODY1 : DRAW_HEAD;
				DRAW_BODY1: next_state = (draw_erase_count == 5'd21) ? DRAW_BODY2 : DRAW_BODY1;
				DRAW_BODY2: next_state = (draw_erase_count == 5'd21) ? DRAW_TAIL : DRAW_BODY2;
				DRAW_TAIL: next_state = (draw_erase_count == 5'd21) ? DRAW_FOOD : DRAW_TAIL;
				DRAW_FOOD: next_state = (draw_erase_count == 5'd21) ? DRAW_OBSTACLE1 : DRAW_FOOD;
				DRAW_OBSTACLE1: next_state = (draw_erase_count == 5'd21) ? DRAW_OBSTACLE2 : DRAW_OBSTACLE1;
				DRAW_OBSTACLE2: next_state = (draw_erase_count == 5'd21) ? DRAW_TUNNEL1 : DRAW_OBSTACLE2;
				DRAW_TUNNEL1: next_state = (draw_erase_count == 5'd21) ? DRAW_TUNNEL2 : DRAW_TUNNEL1;
				DRAW_TUNNEL2: next_state = (draw_erase_count == 5'd21) ? WAIT : DRAW_TUNNEL2;
				WAIT: next_state = (|{up, down, left, right}) ? ERASE_TAIL : WAIT;
				ERASE_TAIL: next_state = (draw_erase_count == 5'd21) ? SHIFT : ERASE_TAIL;
				SHIFT: next_state = UPDATE_POSITION;
				UPDATE_POSITION: next_state = UPDATE_POSITION1;
				UPDATE_POSITION1: next_state = CHECK;
				CHECK: if (collide) 
							next_state = RESTART;
						 else if (eat)
							next_state = DRAW_NEW1;
						 else 
							next_state = UPDATE_HEAD;
				DRAW_NEW1: next_state = (draw_erase_count == 5'd21) ? DRAW_NEW2 : DRAW_NEW1;
				DRAW_NEW2: next_state = (draw_erase_count == 5'd21) ? DRAW_NEW3 : DRAW_NEW2;
				DRAW_NEW3: next_state = (draw_erase_count == 5'd21) ? DRAW_NEW4 : DRAW_NEW3;
				DRAW_NEW4: next_state = (draw_erase_count == 5'd21) ? UPDATE_HEAD : DRAW_NEW4;
				UPDATE_HEAD: next_state = (draw_erase_count == 5'd21) ?UPDATE_FOOD : UPDATE_HEAD;
				UPDATE_FOOD: next_state = (draw_erase_count == 5'd21) ? DELAY : UPDATE_FOOD;
				DELAY: next_state = (delay_count == level_rate) ? ERASE_TAIL : DELAY;
				RESTART: next_state = (restart_count == 15'd20000) ? START: RESTART;
				default: next_state = DRAW_HEAD;
			endcase
		end
	
		always@(posedge CLOCK_50)
		begin
			if(up && direction != 2'b01) 
				direction <= 2'b00;
			else if(down && direction != 2'b00)
				direction <= 2'b01;
			else if(left && direction != 2'b11)
				direction <= 2'b10;
			else if(right && direction != 2'b10)
				direction <= 2'b11;
			if (current_state == UPDATE_POSITION)  
					begin
					case(direction)
						2'b00: if(snake[1][6:0] == 7'd0)
									collide = 1;
								 else if(snake[1] == {8'd120, 7'd24})
									snake[0] <= {8'd20, 7'd96};
								 else if(snake[1] == {8'd20, 7'd104})
									snake[0] <= {8'd120, 7'd16};
								 else
									snake[0] <= {snake[1][14:7], snake[1][6:0] - 7'd4};
						2'b01: if(snake[1][6:0] == 7'd116)
									collide = 1;
								 else if(snake[1] == {8'd120, 7'd16})
									snake[0] <= {8'd20, 7'd104};
								 else if(snake[1] == {8'd20, 7'd96})
									snake[0] <= {8'd120, 7'd24};
								 else
									snake[0] <= {snake[1][14:7], snake[1][6:0] + 7'd4};
						2'b10: if(snake[1][14:7] == 8'd0)
									collide = 1;
								 else if(snake[1] == {8'd124, 7'd20})
									snake[0] <= {8'd16, 7'd100};
								 else if(snake[1] == {8'd24, 7'd100})
									snake[0] <= {8'd116, 7'd20};
								 else
									snake[0] <= {snake[1][14:7] - 8'd4, snake[1][6:0]};
						2'b11: if(snake[1][14:7] == 8'd156)
									collide = 1;
								 else if(snake[1] == {8'd116, 7'd20})
									snake[0] <= {8'd24, 7'd100};
								 else if(snake[1] == {8'd16, 7'd100})
									snake[0] <= {8'd124, 7'd20};
								 else
									snake[0] <= {snake[1][14:7] + 8'd4, snake[1][6:0]};
					endcase
					end
			if (current_state == SHIFT) begin
				for (index = 0; index < 126; index = index + 1) begin
					snake[index + 1] <= snake[index];
				end
			end
			if (current_state == UPDATE_POSITION1) begin
				for (index = 1; index < length; index = index + 1) begin
					if (snake[index] == snake[0])
						collide = 1;
				end
				if (snake[0] == {8'd20, 7'd20} || snake[0] == {8'd100, 7'd100})
					collide = 1;
				if(snake[0] == food) begin
					eat = 1;
					score <= score + 8'd1;
					length <= length + 7'd4;
					food <= {random_food_x, random_food_y};
					end
				end
			if (current_state == DRAW_NEW1)
				eat = 0;
			if (current_state == RESTART) begin
						snake[0] = {8'd60, 7'd60};
						snake[1] = {8'd56, 7'd60};
						snake[2] = {8'd52, 7'd60};
						snake[3] = {8'd48, 7'd60};
						for (index = 4; index < 128; index = index +1) begin
							snake[index] = {8'd48, 7'd60};
						end
						food <= {8'd80, 7'd40};
						collide = 0;
						eat = 0;
						length <= 7'd4;
						score <= 7'd0;
						direction <= 2'b11;
				end
		end
	
	always@(*)
		begin: signals 
			ld_x = 1'b0;
			ld_y = 1'b0;
			erase = 1'b0;
			draw = 1'b0;
			plot = 1'b0;
			restart = 1'b0;
			
			case(current_state)
				START: begin
					colour <= 3'b010;
					end
					
				DRAW_HEAD: begin
					ld_x = 1'b1;
					ld_y = 1'b1;
					draw = 1'b1;
					plot = 1'b1;
					x_count <= snake[0][14:7];
					y_count <= snake[0][6:0];
					end
					
				DRAW_BODY1: begin
					ld_x = 1'b1;
					ld_y = 1'b1;
					draw = 1'b1;
					plot = 1'b1;
					x_count <= snake[1][14:7];
					y_count <= snake[1][6:0];
					end
					
				DRAW_BODY2: begin
					ld_x = 1'b1;
					ld_y = 1'b1;
					draw = 1'b1;
					plot = 1'b1;
					x_count <= snake[2][14:7];
					y_count <= snake[2][6:0];
					end
					
				DRAW_TAIL: begin
					ld_x = 1'b1;
					ld_y = 1'b1;
					draw = 1'b1;
					plot = 1'b1;
					x_count <= snake[3][14:7];
					y_count <= snake[3][6:0];
					end
				DRAW_FOOD: begin
					ld_x = 1'b1;
					ld_y = 1'b1;
					draw = 1'b1;
					plot = 1'b1;
					x_count <= food[14:7];
					y_count <= food[6:0];
					colour <= 3'b110;
					end
				DRAW_OBSTACLE1: begin
					ld_x = 1'b1;
					ld_y = 1'b1;
					draw = 1'b1;
					plot = 1'b1;
					x_count <= 8'd20;
					y_count <= 7'd20;
					colour <= 3'b100;
					end
				DRAW_OBSTACLE2: begin
					ld_x = 1'b1;
					ld_y = 1'b1;
					draw = 1'b1;
					plot = 1'b1;
					x_count <= 8'd100;
					y_count <= 7'd100;
					colour <= 3'b100;
					end
				DRAW_TUNNEL1: begin
					ld_x = 1'b1;
					ld_y = 1'b1;
					draw = 1'b1;
					plot = 1'b1;
					x_count <= 8'd120;
					y_count <= 7'd20;
					colour <= 3'b111;
					end
				DRAW_TUNNEL2: begin
					ld_x = 1'b1;
					ld_y = 1'b1;
					draw = 1'b1;
					plot = 1'b1;
					x_count <= 8'd20;
					y_count <= 7'd100;
					colour <= 3'b111;
					end
				ERASE_TAIL: begin
					ld_x = 1'b1;
					ld_y = 1'b1;
					erase = 1'b1;
					plot = 1'b1;
					x_count <= snake[length - 7'd1][14:7];
					y_count <= snake[length - 7'd1][6:0];
					end
				DRAW_NEW1: begin
					ld_x = 1'b1;
					ld_y = 1'b1;
					draw = 1'b1;
					plot = 1'b1;
					x_count <= snake[length - 7'd4][14:7];
					y_count <= snake[length - 7'd4][6:0];
					colour <= 3'b010;
					end
				DRAW_NEW2: begin
					ld_x = 1'b1;
					ld_y = 1'b1;
					draw = 1'b1;
					plot = 1'b1;
					x_count <= snake[length - 7'd3][14:7];
					y_count <= snake[length - 7'd3][6:0];
					colour <= 3'b010;
					end
				DRAW_NEW3: begin
					ld_x = 1'b1;
					ld_y = 1'b1;
					draw = 1'b1;
					plot = 1'b1;
					x_count <= snake[length - 7'd2][14:7];
					y_count <= snake[length - 7'd2][6:0];
					colour <= 3'b010;
					end
				DRAW_NEW4: begin
					ld_x = 1'b1;
					ld_y = 1'b1;
					draw = 1'b1;
					plot = 1'b1;
					x_count <= snake[length - 7'd1][14:7];
					y_count <= snake[length - 7'd1][6:0];
					colour <= 3'b010;
					end
				UPDATE_HEAD: begin
					ld_x = 1'b1;
					ld_y = 1'b1;
					draw = 1'b1;
					plot = 1'b1;
					x_count <= snake[0][14:7];
					y_count <= snake[0][6:0];
					colour <= 3'b010;
					end
				UPDATE_FOOD: begin
					ld_x = 1'b1;
					ld_y = 1'b1;
					draw = 1'b1;
					plot = 1'b1;
					x_count <= food[14:7];
					y_count <= food[6:0];
					colour <= 3'b110;
					end
				RESTART: begin
					restart = 1'b1;
					plot = 1'b1;
					end
			endcase
		end	
		
	always@(posedge CLOCK_50)
		begin
			if(current_state == START)
				draw_erase_count <= 5'd0;
			else if(current_state != START && current_state != WAIT && current_state != UPDATE_POSITION && 
						current_state != DELAY && current_state != SHIFT && current_state != UPDATE_POSITION1 && 
						current_state != CHECK)
				begin
					if (draw_erase_count == 5'd21)
						draw_erase_count <= 5'd0;
					else
						draw_erase_count <= draw_erase_count + 1'd1;
				end
		end
	
	always@(posedge CLOCK_50)
		begin
			if(current_state == START)
				delay_count <= 24'd0;
			else if(current_state == DELAY)
				begin
					if (delay_count == level_rate)
						delay_count <= 24'd0;
					else
						delay_count <= delay_count + 1'd1;
				end
		end
		
	always@(posedge CLOCK_50)
		begin
			if(current_state == START)
				restart_count <= 15'd0;
			else if(current_state == RESTART)
				begin
					if (restart_count == 15'd20000)
						restart_count <= 15'd0;
					else
						restart_count <= restart_count + 1'd1;
				end
		end
	
	always @(posedge CLOCK_50)
		begin 
        if(!resetn)
            current_state <= START;
        else
            current_state <= next_state;
		end 
	
endmodule

module hex_decoder(hex_digit, segments);
    input [3:0] hex_digit;
    output reg [6:0] segments;
   
    always @(*)
        case (hex_digit)
            4'h0: segments = 7'b100_0000;
            4'h1: segments = 7'b111_1001;
            4'h2: segments = 7'b010_0100;
            4'h3: segments = 7'b011_0000;
            4'h4: segments = 7'b001_1001;
            4'h5: segments = 7'b001_0010;
            4'h6: segments = 7'b000_0010;
            4'h7: segments = 7'b111_1000;
            4'h8: segments = 7'b000_0000;
            4'h9: segments = 7'b001_1000;
            4'hA: segments = 7'b000_1000;
            4'hB: segments = 7'b000_0011;
            4'hC: segments = 7'b100_0110;
            4'hD: segments = 7'b010_0001;
            4'hE: segments = 7'b000_0110;
            4'hF: segments = 7'b000_1110;   
            default: segments = 7'h7f;
        endcase
endmodule

module vga_adapter(
			resetn,
			clock,
			colour,
			x, y, plot,
			/* Signals for the DAC to drive the monitor. */
			VGA_R,
			VGA_G,
			VGA_B,
			VGA_HS,
			VGA_VS,
			VGA_BLANK,
			VGA_SYNC,
			VGA_CLK);
 
	parameter BITS_PER_COLOUR_CHANNEL = 1;
	/* The number of bits per colour channel used to represent the colour of each pixel. A value
	 * of 1 means that Red, Green and Blue colour channels will use 1 bit each to represent the intensity
	 * of the respective colour channel. For BITS_PER_COLOUR_CHANNEL=1, the adapter can display 8 colours.
	 * In general, the adapter is able to use 2^(3*BITS_PER_COLOUR_CHANNEL ) colours. The number of colours is
	 * limited by the screen resolution and the amount of on-chip memory available on the target device.
	 */	
	
	parameter MONOCHROME = "FALSE";
	/* Set this parameter to "TRUE" if you only wish to use black and white colours. Doing so will reduce
	 * the amount of memory you will use by a factor of 3. */
	
	parameter RESOLUTION = "320x240";
	/* Set this parameter to "160x120" or "320x240". It will cause the VGA adapter to draw each dot on
	 * the screen by using a block of 4x4 pixels ("160x120" resolution) or 2x2 pixels ("320x240" resolution).
	 * It effectively reduces the screen resolution to an integer fraction of 640x480. It was necessary
	 * to reduce the resolution for the Video Memory to fit within the on-chip memory limits.
	 */
	
	parameter BACKGROUND_IMAGE = "background.mif";
	/* The initial screen displayed when the circuit is first programmed onto the DE2 board can be
	 * defined useing an MIF file. The file contains the initial colour for each pixel on the screen
	 * and is placed in the Video Memory (VideoMemory module) upon programming. Note that resetting the
	 * VGA Adapter will not cause the Video Memory to revert to the specified image. */


	/*****************************************************************************/
	/* Declare inputs and outputs.                                               */
	/*****************************************************************************/
	input resetn;
	input clock;
	
	/* The colour input can be either 1 bit or 3*BITS_PER_COLOUR_CHANNEL bits wide, depending on
	 * the setting of the MONOCHROME parameter.
	 */
	input [((MONOCHROME == "TRUE") ? (0) : (BITS_PER_COLOUR_CHANNEL*3-1)):0] colour;
	
	/* Specify the number of bits required to represent an (X,Y) coordinate on the screen for
	 * a given resolution.
	 */
	input [((RESOLUTION == "320x240") ? (8) : (7)):0] x; 
	input [((RESOLUTION == "320x240") ? (7) : (6)):0] y;
	
	/* When plot is high then at the next positive edge of the clock the pixel at (x,y) will change to
	 * a new colour, defined by the value of the colour input.
	 */
	input plot;
	
	/* These outputs drive the VGA display. The VGA_CLK is also used to clock the FSM responsible for
	 * controlling the data transferred to the DAC driving the monitor. */
	output [9:0] VGA_R;
	output [9:0] VGA_G;
	output [9:0] VGA_B;
	output VGA_HS;
	output VGA_VS;
	output VGA_BLANK;
	output VGA_SYNC;
	output VGA_CLK;

	/*****************************************************************************/
	/* Declare local signals here.                                               */
	/*****************************************************************************/
	
	wire valid_160x120;
	wire valid_320x240;
	/* Set to 1 if the specified coordinates are in a valid range for a given resolution.*/
	
	wire writeEn;
	/* This is a local signal that allows the Video Memory contents to be changed.
	 * It depends on the screen resolution, the values of X and Y inputs, as well as 
	 * the state of the plot signal.
	 */
	
	wire [((MONOCHROME == "TRUE") ? (0) : (BITS_PER_COLOUR_CHANNEL*3-1)):0] to_ctrl_colour;
	/* Pixel colour read by the VGA controller */
	
	wire [((RESOLUTION == "320x240") ? (16) : (14)):0] user_to_video_memory_addr;
	/* This bus specifies the address in memory the user must write
	 * data to in order for the pixel intended to appear at location (X,Y) to be displayed
	 * at the correct location on the screen.
	 */
	
	wire [((RESOLUTION == "320x240") ? (16) : (14)):0] controller_to_video_memory_addr;
	/* This bus specifies the address in memory the vga controller must read data from
	 * in order to determine the colour of a pixel located at coordinate (X,Y) of the screen.
	 */
	
	wire clock_25;
	/* 25MHz clock generated by dividing the input clock frequency by 2. */
	
	wire vcc, gnd;
	
	/*****************************************************************************/
	/* Instances of modules for the VGA adapter.                                 */
	/*****************************************************************************/	
	assign vcc = 1'b1;
	assign gnd = 1'b0;
	
	vga_address_translator user_input_translator(
					.x(x), .y(y), .mem_address(user_to_video_memory_addr) );
		defparam user_input_translator.RESOLUTION = RESOLUTION;
	/* Convert user coordinates into a memory address. */

	assign valid_160x120 = (({1'b0, x} >= 0) & ({1'b0, x} < 160) & ({1'b0, y} >= 0) & ({1'b0, y} < 120)) & (RESOLUTION == "160x120");
	assign valid_320x240 = (({1'b0, x} >= 0) & ({1'b0, x} < 320) & ({1'b0, y} >= 0) & ({1'b0, y} < 240)) & (RESOLUTION == "320x240");
	assign writeEn = (plot) & (valid_160x120 | valid_320x240);
	/* Allow the user to plot a pixel if and only if the (X,Y) coordinates supplied are in a valid range. */
	
	/* Create video memory. */
	altsyncram	VideoMemory (
				.wren_a (writeEn),
				.wren_b (gnd),
				.clock0 (clock), // write clock
				.clock1 (clock_25), // read clock
				.clocken0 (vcc), // write enable clock
				.clocken1 (vcc), // read enable clock				
				.address_a (user_to_video_memory_addr),
				.address_b (controller_to_video_memory_addr),
				.data_a (colour), // data in
				.q_b (to_ctrl_colour)	// data out
				);
	defparam
		VideoMemory.WIDTH_A = ((MONOCHROME == "FALSE") ? (BITS_PER_COLOUR_CHANNEL*3) : 1),
		VideoMemory.WIDTH_B = ((MONOCHROME == "FALSE") ? (BITS_PER_COLOUR_CHANNEL*3) : 1),
		VideoMemory.INTENDED_DEVICE_FAMILY = "Cyclone II",
		VideoMemory.OPERATION_MODE = "DUAL_PORT",
		VideoMemory.WIDTHAD_A = ((RESOLUTION == "320x240") ? (17) : (15)),
		VideoMemory.NUMWORDS_A = ((RESOLUTION == "320x240") ? (76800) : (19200)),
		VideoMemory.WIDTHAD_B = ((RESOLUTION == "320x240") ? (17) : (15)),
		VideoMemory.NUMWORDS_B = ((RESOLUTION == "320x240") ? (76800) : (19200)),
		VideoMemory.OUTDATA_REG_B = "CLOCK1",
		VideoMemory.ADDRESS_REG_B = "CLOCK1",
		VideoMemory.CLOCK_ENABLE_INPUT_A = "BYPASS",
		VideoMemory.CLOCK_ENABLE_INPUT_B = "BYPASS",
		VideoMemory.CLOCK_ENABLE_OUTPUT_B = "BYPASS",
		VideoMemory.POWER_UP_UNINITIALIZED = "FALSE",
		VideoMemory.INIT_FILE = BACKGROUND_IMAGE;
		
	vga_pll mypll(clock, clock_25);
	/* This module generates a clock with half the frequency of the input clock.
	 * For the VGA adapter to operate correctly the clock signal 'clock' must be
	 * a 50MHz clock. The derived clock, which will then operate at 25MHz, is
	 * required to set the monitor into the 640x480@60Hz display mode (also known as
	 * the VGA mode).
	 */
	
	vga_controller controller(
			.vga_clock(clock_25),
			.resetn(resetn),
			.pixel_colour(to_ctrl_colour),
			.memory_address(controller_to_video_memory_addr), 
			.VGA_R(VGA_R),
			.VGA_G(VGA_G),
			.VGA_B(VGA_B),
			.VGA_HS(VGA_HS),
			.VGA_VS(VGA_VS),
			.VGA_BLANK(VGA_BLANK),
			.VGA_SYNC(VGA_SYNC),
			.VGA_CLK(VGA_CLK)				
		);
		defparam controller.BITS_PER_COLOUR_CHANNEL  = BITS_PER_COLOUR_CHANNEL ;
		defparam controller.MONOCHROME = MONOCHROME;
		defparam controller.RESOLUTION = RESOLUTION;

endmodule

module vga_address_translator(x, y, mem_address);

	parameter RESOLUTION = "320x240";
	/* Set this parameter to "160x120" or "320x240". It will cause the VGA adapter to draw each dot on
	 * the screen by using a block of 4x4 pixels ("160x120" resolution) or 2x2 pixels ("320x240" resolution).
	 * It effectively reduces the screen resolution to an integer fraction of 640x480. It was necessary
	 * to reduce the resolution for the Video Memory to fit within the on-chip memory limits.
	 */

	input [((RESOLUTION == "320x240") ? (8) : (7)):0] x; 
	input [((RESOLUTION == "320x240") ? (7) : (6)):0] y;	
	output reg [((RESOLUTION == "320x240") ? (16) : (14)):0] mem_address;
	
	/* The basic formula is address = y*WIDTH + x;
	 * For 320x240 resolution we can write 320 as (256 + 64). Memory address becomes
	 * (y*256) + (y*64) + x;
	 * This simplifies multiplication a simple shift and add operation.
	 * A leading 0 bit is added to each operand to ensure that they are treated as unsigned
	 * inputs. By default the use a '+' operator will generate a signed adder.
	 * Similarly, for 160x120 resolution we write 160 as 128+32.
	 */
	wire [16:0] res_320x240 = ({1'b0, y, 8'd0} + {1'b0, y, 6'd0} + {1'b0, x});
	wire [15:0] res_160x120 = ({1'b0, y, 7'd0} + {1'b0, y, 5'd0} + {1'b0, x});
	
	always @(*)
	begin
		if (RESOLUTION == "320x240")
			mem_address = res_320x240;
		else
			mem_address = res_160x120[14:0];
	end
endmodule

module vga_controller(	vga_clock, resetn, pixel_colour, memory_address, 
		VGA_R, VGA_G, VGA_B,
		VGA_HS, VGA_VS, VGA_BLANK,
		VGA_SYNC, VGA_CLK);
	
	/* Screen resolution and colour depth parameters. */
	
	parameter BITS_PER_COLOUR_CHANNEL = 1;
	/* The number of bits per colour channel used to represent the colour of each pixel. A value
	 * of 1 means that Red, Green and Blue colour channels will use 1 bit each to represent the intensity
	 * of the respective colour channel. For BITS_PER_COLOUR_CHANNEL=1, the adapter can display 8 colours.
	 * In general, the adapter is able to use 2^(3*BITS_PER_COLOUR_CHANNEL) colours. The number of colours is
	 * limited by the screen resolution and the amount of on-chip memory available on the target device.
	 */	
	
	parameter MONOCHROME = "FALSE";
	/* Set this parameter to "TRUE" if you only wish to use black and white colours. Doing so will reduce
	 * the amount of memory you will use by a factor of 3. */
	
	parameter RESOLUTION = "320x240";
	/* Set this parameter to "160x120" or "320x240". It will cause the VGA adapter to draw each dot on
	 * the screen by using a block of 4x4 pixels ("160x120" resolution) or 2x2 pixels ("320x240" resolution).
	 * It effectively reduces the screen resolution to an integer fraction of 640x480. It was necessary
	 * to reduce the resolution for the Video Memory to fit within the on-chip memory limits.
	 */
	
	//--- Timing parameters.
	/* Recall that the VGA specification requires a few more rows and columns are drawn
	 * when refreshing the screen than are actually present on the screen. This is necessary to
	 * generate the vertical and the horizontal syncronization signals. If you wish to use a
	 * display mode other than 640x480 you will need to modify the parameters below as well
	 * as change the frequency of the clock driving the monitor (VGA_CLK).
	 */
	parameter C_VERT_NUM_PIXELS  = 10'd480;
	parameter C_VERT_SYNC_START  = 10'd493;
	parameter C_VERT_SYNC_END    = 10'd494; //(C_VERT_SYNC_START + 2 - 1); 
	parameter C_VERT_TOTAL_COUNT = 10'd525;

	parameter C_HORZ_NUM_PIXELS  = 10'd640;
	parameter C_HORZ_SYNC_START  = 10'd659;
	parameter C_HORZ_SYNC_END    = 10'd754; //(C_HORZ_SYNC_START + 96 - 1); 
	parameter C_HORZ_TOTAL_COUNT = 10'd800;	
		
	/*****************************************************************************/
	/* Declare inputs and outputs.                                               */
	/*****************************************************************************/
	
	input vga_clock, resetn;
	input [((MONOCHROME == "TRUE") ? (0) : (BITS_PER_COLOUR_CHANNEL*3-1)):0] pixel_colour;
	output [((RESOLUTION == "320x240") ? (16) : (14)):0] memory_address;
	output reg [9:0] VGA_R;
	output reg [9:0] VGA_G;
	output reg [9:0] VGA_B;
	output reg VGA_HS;
	output reg VGA_VS;
	output reg VGA_BLANK;
	output VGA_SYNC, VGA_CLK;
	
	/*****************************************************************************/
	/* Local Signals.                                                            */
	/*****************************************************************************/
	
	reg VGA_HS1;
	reg VGA_VS1;
	reg VGA_BLANK1; 
	reg [9:0] xCounter, yCounter;
	wire xCounter_clear;
	wire yCounter_clear;
	wire vcc;
	
	reg [((RESOLUTION == "320x240") ? (8) : (7)):0] x; 
	reg [((RESOLUTION == "320x240") ? (7) : (6)):0] y;	
	/* Inputs to the converter. */
	
	/*****************************************************************************/
	/* Controller implementation.                                                */
	/*****************************************************************************/

	assign vcc =1'b1;
	
	/* A counter to scan through a horizontal line. */
	always @(posedge vga_clock or negedge resetn)
	begin
		if (!resetn)
			xCounter <= 10'd0;
		else if (xCounter_clear)
			xCounter <= 10'd0;
		else
		begin
			xCounter <= xCounter + 1'b1;
		end
	end
	assign xCounter_clear = (xCounter == (C_HORZ_TOTAL_COUNT-1));

	/* A counter to scan vertically, indicating the row currently being drawn. */
	always @(posedge vga_clock or negedge resetn)
	begin
		if (!resetn)
			yCounter <= 10'd0;
		else if (xCounter_clear && yCounter_clear)
			yCounter <= 10'd0;
		else if (xCounter_clear)		//Increment when x counter resets
			yCounter <= yCounter + 1'b1;
	end
	assign yCounter_clear = (yCounter == (C_VERT_TOTAL_COUNT-1)); 
	
	/* Convert the xCounter/yCounter location from screen pixels (640x480) to our
	 * local dots (320x240 or 160x120). Here we effectively divide x/y coordinate by 2 or 4,
	 * depending on the resolution. */
	always @(*)
	begin
		if (RESOLUTION == "320x240")
		begin
			x = xCounter[9:1];
			y = yCounter[8:1];
		end
		else
		begin
			x = xCounter[9:2];
			y = yCounter[8:2];
		end
	end
	
	/* Change the (x,y) coordinate into a memory address. */
	vga_address_translator controller_translator(
					.x(x), .y(y), .mem_address(memory_address) );
		defparam controller_translator.RESOLUTION = RESOLUTION;


	/* Generate the vertical and horizontal synchronization pulses. */
	always @(posedge vga_clock)
	begin
		//- Sync Generator (ACTIVE LOW)
		VGA_HS1 <= ~((xCounter >= C_HORZ_SYNC_START) && (xCounter <= C_HORZ_SYNC_END));
		VGA_VS1 <= ~((yCounter >= C_VERT_SYNC_START) && (yCounter <= C_VERT_SYNC_END));
		
		//- Current X and Y is valid pixel range
		VGA_BLANK1 <= ((xCounter < C_HORZ_NUM_PIXELS) && (yCounter < C_VERT_NUM_PIXELS));	
	
		//- Add 1 cycle delay
		VGA_HS <= VGA_HS1;
		VGA_VS <= VGA_VS1;
		VGA_BLANK <= VGA_BLANK1;	
	end
	
	/* VGA sync should be 1 at all times. */
	assign VGA_SYNC = vcc;
	
	/* Generate the VGA clock signal. */
	assign VGA_CLK = vga_clock;
	
	/* Brighten the colour output. */
	// The colour input is first processed to brighten the image a little. Setting the top
	// bits to correspond to the R,G,B colour makes the image a bit dull. To brighten the image,
	// each bit of the colour is replicated through the 10 DAC colour input bits. For example,
	// when BITS_PER_COLOUR_CHANNEL is 2 and the red component is set to 2'b10, then the
	// VGA_R input to the DAC will be set to 10'b1010101010.
	
	integer index;
	integer sub_index;
	
	always @(pixel_colour)
	begin		
		VGA_R <= 'b0;
		VGA_G <= 'b0;
		VGA_B <= 'b0;
		if (MONOCHROME == "FALSE")
		begin
			for (index = 10-BITS_PER_COLOUR_CHANNEL; index >= 0; index = index - BITS_PER_COLOUR_CHANNEL)
			begin
				for (sub_index = BITS_PER_COLOUR_CHANNEL - 1; sub_index >= 0; sub_index = sub_index - 1)
				begin
					VGA_R[sub_index+index] <= pixel_colour[sub_index + BITS_PER_COLOUR_CHANNEL*2];
					VGA_G[sub_index+index] <= pixel_colour[sub_index + BITS_PER_COLOUR_CHANNEL];
					VGA_B[sub_index+index] <= pixel_colour[sub_index];
				end
			end	
		end
		else
		begin
			for (index = 0; index < 10; index = index + 1)
			begin
				VGA_R[index] <= pixel_colour[0:0];
				VGA_G[index] <= pixel_colour[0:0];
				VGA_B[index] <= pixel_colour[0:0];
			end	
		end
	end

endmodule

module vga_pll (
	clock_in,
	clock_out);

	input	  clock_in;
	output	  clock_out;

	wire [5:0] clock_output_bus;
	wire [1:0] clock_input_bus;
	wire gnd;
	
	assign gnd = 1'b0;
	assign clock_input_bus = { gnd, clock_in }; 

	altpll	altpll_component (
				.inclk (clock_input_bus),
				.clk (clock_output_bus)
				);
	defparam
		altpll_component.operation_mode = "NORMAL",
		altpll_component.intended_device_family = "Cyclone II",
		altpll_component.lpm_type = "altpll",
		altpll_component.pll_type = "FAST",
		/* Specify the input clock to be a 50MHz clock. A 50 MHz clock is present
		 * on PIN_N2 on the DE2 board. We need to specify the input clock frequency
		 * in order to set up the PLL correctly. To do this we must put the input clock
		 * period measured in picoseconds in the inclk0_input_frequency parameter.
		 * 1/(20000 ps) = 0.5 * 10^(5) Hz = 50 * 10^(6) Hz = 50 MHz. */
		altpll_component.inclk0_input_frequency = 20000,
		altpll_component.primary_clock = "INCLK0",
		/* Specify output clock parameters. The output clock should have a
		 * frequency of 25 MHz, with 50% duty cycle. */
		altpll_component.compensate_clock = "CLK0",
		altpll_component.clk0_phase_shift = "0",
		altpll_component.clk0_divide_by = 2,
		altpll_component.clk0_multiply_by = 1,		
		altpll_component.clk0_duty_cycle = 50;
		
	assign clock_out = clock_output_bus[0];

endmodule
