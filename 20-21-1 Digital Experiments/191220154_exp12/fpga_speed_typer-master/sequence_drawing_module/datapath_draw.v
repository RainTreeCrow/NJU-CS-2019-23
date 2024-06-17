module datapath_draw (
	input             clk                 ,
	input             resetn              ,
	input      [ 5:0] colour_input        ,
	input      [ 8:0] y_input             ,
	input      [ 8:0] x_input             ,
	input             ld_block            ,
	input             ld_black            ,
	input             enable_counter      ,
	input             reset_counter       ,
	input             enable_clear_counter,
	output reg [15:0] clear_counter       ,
	output reg [ 4:0] counter             ,
	output reg [ 8:0] x                   ,
	output reg [ 8:0] y                   ,
	output reg [ 5:0] colour
);

	reg [8:0] x_start;
	reg [8:0] y_start;
	reg [5:0]colour_buffer;

	// input registers


	// Registers x, y, colour with respective input logic
	always@(posedge clk) begin
		if(!resetn) begin
			x      <= 9'b0;
			y      <= 9'b0;
			colour <= 6'b0;
		end
		else begin
			//resetting the counters for plotting
			if(reset_counter) begin
				counter       <= 5'b0;
				clear_counter <= 16'b0;
			end
			//load the specified coordinate and colour
			if(ld_block) begin
				x_start <= x_input;
				y_start <= y_input;
				x <= x_input;
				y <= y_input;
				colour_buffer  <= colour_input;
			end
			//change lower half to black
			if(ld_black) begin
				x       <= 9'd9;
				y       <= 9'd166;
				//change x_start to 105 to take up the bottom 35 pixels
				x_start <= 9'd9;
				y_start <= 9'd166;
				//black
				colour_buffer  <= 0;
			end
			//incrementing the counter for drawing a square
			if(enable_counter) begin
				counter <= counter + 1;
				x       <= x_start + counter[1:0];
				y       <= y_start + counter[3:2];
				colour   <= colour_buffer;
			end
			//incrementing the counter for clearing screen
			if(enable_clear_counter) begin
				if(clear_counter[8:0] >= 302) begin
					clear_counter[15:9] <= clear_counter[15:9] + 1;
					clear_counter[8:0] <= 0;
				end
				else begin
					clear_counter <= clear_counter + 1;
				end	
				x             <= x_start + clear_counter[8:0];
				y             <= y_start + clear_counter[15:9];
				colour   <= colour_buffer;
			end
		end
	end // always@(posedge clk)
endmodule