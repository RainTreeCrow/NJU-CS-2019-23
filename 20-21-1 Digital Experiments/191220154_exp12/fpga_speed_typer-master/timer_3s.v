 
//countdown timer, for custom amounts of time
 module timer_3s(clk,q,enable,resetn,enable_next_level,num_char,difficulty);//150M
			input clk;
			input enable_next_level;
			input [7:0] num_char;
			input [1:0] difficulty;
			output reg q;
			input enable;
			input resetn;
			reg [27:0] counter;
			reg [5:0] level_counter;  

			always@(posedge clk) begin
				if(!resetn) begin
					counter <= 27'd0;
					level_counter <= 27'd0;
					q <= 0;
				end
				else if(enable_next_level) begin
					if(difficulty == 1)
						counter <= 27'd100000000 * num_char;
					else if (difficulty == 2)
						counter <= 27'd50000000 * num_char;
					else
						counter <= 27'd10000000 * num_char;
					q <= 0;
				end
				else if (!counter)begin
					if(difficulty == 1)
						counter <= 27'd15000000 * num_char;
					else if (difficulty == 2)
						counter <= 27'd12500000 * num_char;
					else if (difficulty == 3)
						counter <= 27'd10000000 * num_char;
					q <= 1;
				end
				else if (enable)
					counter <= counter-1;
			end
endmodule