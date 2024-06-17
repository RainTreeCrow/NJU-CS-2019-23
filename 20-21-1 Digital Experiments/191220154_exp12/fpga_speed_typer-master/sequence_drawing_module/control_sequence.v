//controls the plotting of one character
//start the plot with (enable_character_plot)
//address for character and starting x - y coordinate needs to be given
//when finished sends a (ready_to_start_character)

//handshake waits for (ready_to_draw) from pixel drawing
//to know when to increment for next coordinate and colour
module control_sequence (
	input            clk                     , // Clock
	input            rst_n                   , // Asynchronous reset active low
	input            ready_to_draw           ,
	input      [5:0] counter                 ,
	input            enable_character_plot   ,
	input            enable_clear            ,
	output reg       enable_clear_pixels     ,
	output reg       ld_colour               ,
	output reg       enable_counter          ,
	output reg       reset_counter           ,
	output reg       enable_start            ,
	output reg       ld_value                ,
	output reg       next_colour             ,
	output reg       ready_to_start_character
	//output reg [2:0] current_state
);
	reg [2:0] current_state;
	reg [2:0] next_state   ;

	localparam
		S_WAIT_START = 3'd0,
			S_LOAD_INITIAL = 3'd1,
				S_PLOT_PIXEL = 3'd2,
					S_WAIT_PIXEL = 3'd3,
						S_LOAD_NEXT_PIXEL = 3'd4,
							S_RESET_COUNTER = 3'd5,
								S_LOAD_CLEAR = 3'd6,
									S_CLEAR_WAIT = 3'd7;

	always@(posedge clk) begin : proc_current_state
		if(~rst_n) begin
			current_state <= 0;
		end // if(~rst_n)
		else begin
			current_state <= next_state;
		end // end else if(clk_en)
	end // proc_current_state

	always @(*) begin : state_table
		case (current_state)
			S_WAIT_START :
				begin
					if(enable_character_plot)
						next_state = S_LOAD_INITIAL;
					else if (enable_clear)
						next_state = S_LOAD_CLEAR;
					else
						next_state = S_WAIT_START;
				end
			S_LOAD_INITIAL : next_state = S_PLOT_PIXEL;
			S_LOAD_CLEAR   : next_state = S_CLEAR_WAIT;
			S_CLEAR_WAIT   : next_state = (ready_to_draw) ? S_WAIT_START : S_CLEAR_WAIT;
			S_PLOT_PIXEL   : next_state = S_WAIT_PIXEL;
			S_WAIT_PIXEL   :
				begin
					if(ready_to_draw && counter[5:3] >= 3'd5)
						next_state = S_RESET_COUNTER;
					else if(ready_to_draw)
						next_state = S_LOAD_NEXT_PIXEL;
					else
						next_state = S_WAIT_PIXEL;
				end
			S_LOAD_NEXT_PIXEL :
				begin
					next_state = S_PLOT_PIXEL;
				end
			S_RESET_COUNTER : next_state = S_WAIT_START;
		endcase // current_state
	end // state_table

	always@(*)
		begin : enable_signals
			reset_counter            = 1'd0;
			enable_start             = 1'd0;
			ld_value                 = 1'd0;
			enable_counter           = 1'd0;
			ld_colour                = 1'd0;
			next_colour              = 1'd0;
			ready_to_start_character = 1'd0;
			enable_clear_pixels      = 1'd0;
			case (current_state)
				S_WAIT_START : begin
					ready_to_start_character = 1'd1;
				end
				S_RESET_COUNTER : begin
					reset_counter = 1'd1;
				end
				S_LOAD_CLEAR : begin
					enable_clear_pixels = 1'd1;
				end
				S_LOAD_INITIAL : begin
					ld_value  = 1'd1;
					ld_colour = 1'd1;
				end
				S_PLOT_PIXEL : begin
					enable_counter = 1'd1;
					enable_start   = 1'd1;
				end
				S_WAIT_PIXEL : begin

				end
				S_LOAD_NEXT_PIXEL : begin
					next_colour = 1'd1;
				end
			endcase // current_state
		end // enable_signals
endmodule // control_sequence







// input[87:0] sequence
// input num_char
// input draw_sequence

// module control_sequence (
// 	input clk,    // Clock
// 	input clk_en, // Clock Enable
// 	input rst_n,  // Asynchronous reset active low
// 	input draw_en,
// 	input wipe_en,
// 	);

// reg [2:0] current_state;
// reg [2:0] next_state   ;

// localparam
// S_WAIT_NEXTSEQ = 3'd0,
// S_DRAW_CHAR = 3'd1,
// S_LOAD_NEXTCHAR = 3'd2,
// S_WAIT_CHAR = 3'd3,
// //wipe can be set to only wipe defined region on the screen
// S_DRAW_WIPE = 3'd4,
// S_WAIT_WIPE = 3'd5;

// 	always@(posedge clk or negedge rst_n) begin : proc_current_state
// 		if(~rst_n) begin
// 			current_state <= 0;
// 		end else if(clk_en) begin
// 			current_state <= next_state;
// 		end
// 	end

// 	//ready_to_start should be enabled if the character state enteres the waiting
// 	always@(*) begin : proc_next_state
// 		next_state = current_state;
// 		case (current_state)
// 			S_WAIT_NEXTSEQ : begin
// 				if (wipe_en) next_state = S_DRAW_WIPE;
// 				else if (draw_en) next_state = S_DRAW_CHAR;
// 				else next_state = S_WAIT_NEXTSEQ;
// 			end
// 			S_DRAW_CHAR     : next_state = S_WAIT_CHAR;
// 			S_LOAD_NEXTCHAR : next_state = S_LOAD_NEXTCHAR;
// 			S_WAIT_CHAR     : begin
// 				if (draw_counter == 25 && ready_to_start) next_state = S_WAIT_NEXTSEQ;
// 				else if (draw_counter == 25) next_state = S_LOAD_NEXTCHAR;
// 				else next_state = S_WAIT_CHAR;
// 			end
// 			S_DRAW_WIPE : next_state = S_WAIT_WIPE;
// 			S_WAIT_WIPE : next_state = (ready_to_start) ? S_WAIT_NEXTSEQ: S_WAIT_WIPE;
// 			default     : next_state = S_WAIT_NEXTSEQ;
// 			endcase
// 	end

// 	always@(*) begin : enable_signals
// 		enable_clear = 1'b0;

// 		case (current_state)
// 			S_WAIT_NEXTSEQ : begin
// 			end
// 			S_DRAW_CHAR : begin
// 				enable_counter=1'b1;
// 			end
// 			S_LOAD_NEXTCHAR : begin

// 			end
// 			S_WAIT_CHAR : begin
// 			end
// 			S_DRAW_WIPE : begin
// 				enable_clear = 1'b1;
// 			end
// 			S_WAIT_WIPE : begin
// 			end

// endmodule

