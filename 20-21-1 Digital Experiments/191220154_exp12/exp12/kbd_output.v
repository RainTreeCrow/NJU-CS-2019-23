module kbd_output(
	clk,
	ready,			//"ready" from [get_keyboard]
	overflow,		//"overflow" from [get_keyboard]
	data,				//input keyboard
	direction,		//Crawling Direction		
	nextdata_n,		//"nextdata_n" to [get_keyboard]
	run,				//"run" to current process
	restart			//"restart"
);

	input clk;
	input ready;
	input overflow;
	input [7:0] data;

	output reg [1:0] direction = 2'b11;
	output reg nextdata_n;
	output reg run = 0;
	output reg restart = 0;	

	reg off = 0;	
	reg [6:0] count_clk = 0;
	reg clk_my = 0;

	always @ (posedge clk) begin
		if (count_clk == 100) begin
			count_clk <= 0;
			clk_my <= ~clk_my;
		end
		else
			count_clk <= count_clk + 1;
	end

	always @ (posedge clk_my) begin
		if (ready) begin
			if((data == 8'h1d || data == 8'h1c || data == 8'h1b ||
				data == 8'h23 || data == 8'h29 || data == 8'h5a)
				&& off == 1'b1) off <= 1'b0;
			else if (off == 1'b0) begin
				case (data)
					8'h1d: begin
						if (direction != 2'b01)
							direction <= 2'b00;
						restart <= 1'b0;
					end								//up	
					8'h1b: begin
						if (direction != 2'b00)
							direction <= 2'b01;
						restart <= 1'b0;
					end								//down
					8'h1c: begin
						if (direction != 2'b11)
							direction <= 2'b10;
						restart <= 1'b0;
					end								//left
					8'h23: begin
						if (direction != 2'b10)
							direction <= 2'b11;
						restart <= 1'b0;
					end								//right
					8'h29: begin
						run <= ~run;
						restart <= 1'b0;
					end								//run
					8'h5a: begin
						run <= run;
						restart <= 1'b1;
						direction = 2'b11;
					end								//restart
					8'hf0: begin
						run <= run;
						restart <= 1'b0;
						off <= 1'b1;
					end
					default:	begin
						run <= run;	
						restart <= 1'b0;
					end
				endcase
			end					
			nextdata_n <= 0;
		end				
		else	nextdata_n <= 1;
	end

endmodule
