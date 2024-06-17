module Keyboard_Parser_Modifier (
	input        clk               ,
	input        resetn            ,
	input        get_next_character,
	input        enable_next_level ,
	output [7:0] num_char          ,
	output [7:0] comparison_data   ,
	output [95:0] sequence_
);
	wire load_sequence;

Keyboard_Input_Shift i_Keyboard_Input_Shift (
	.clk               (clk               ),
	.sequence_          (sequence_        ),
	.resetn            (resetn            ),
	.load_sequence     (load_sequence     ),
	.get_next_character(get_next_character),
	.comparison_data   (comparison_data   )
);

next_level i_next_level (
	.clk              (clk              ),
	.resetn           (resetn           ),
	.enable_next_level(enable_next_level),
	.load_sequence    (load_sequence    ),
	.sequence_      	(sequence_      ),
	.num_char         (num_char         )
);

endmodule



module Keyboard_Input_Shift (
	input         clk               ,
	input  [95:0] sequence_         ,
	input         resetn            ,
	input         load_sequence     ,
	input         get_next_character,
	output [7:0] comparison_data	  

);

		reg [95:0] sequence_data;

		always @(posedge clk) begin : sequence_left_shift
			if (!resetn) begin
				sequence_data <= 0;
			end
			//get_next_character has higher priority but may cause unwanted effects
			//between level changes where get = 0 and load = 1
			else if (get_next_character) begin
				sequence_data <= (sequence_data<<8);
			end
			else if (load_sequence) begin
				sequence_data <= sequence_;
			end
		end

		assign comparison_data = sequence_data[95:88];
endmodule



module next_level (
	input             clk              ,
	input             resetn           ,
	input             enable_next_level,
	output reg        load_sequence    ,
	output reg [95:0] sequence_        ,
	output reg [ 7:0] num_char			  	
);

		reg [2:0] current_state, next_state;
		reg get_sequence;

		localparam
		S_WAIT_START = 3'd0,
		S_LOAD_NEXT  = 3'd1,
		S_LOAD_WAIT	 = 3'd2,
		S_GET_SEQUENCE = 3'd3,
		//3
		ECF 			= 96'h24_21_2B_00_00_00_00_00_00_00_00_00,
		VGA 			= 96'h2A_34_1C_00_00_00_00_00_00_00_00_00,
		//4
		VHDL 			= 96'h2A_33_23_4B_00_00_00_00_00_00_00_00,
		//5
		BAHEN 			= 96'h32_1C_33_24_31_00_00_00_00_00_00_00,
		X2TEGG 			= 96'h1E_2C_24_34_34_00_00_00_00_00_00_00,
		HELLO       	= 96'h33_24_4B_4B_44_00_00_00_00_00_00_00,
		WORLD 			= 96'h1D_44_2D_4B_23_00_00_00_00_00_00_00,
		SKULE 			= 96'h1B_42_3C_4B_24_00_00_00_00_00_00_00,
		//6
		DE1SOC			= 96'h23_24_16_1B_44_21_00_00_00_00_00_00,
		GODIVA 			= 96'h34_44_23_43_2A_1C_00_00_00_00_00_00,
		//7
		QUARTUS 		= 96'h15_3C_1C_2D_2C_3C_1B_00_00_00_00_00,
		PROJECT 		= 96'h4D_2D_44_3B_24_21_2C_00_00_00_00_00,
		VERILOG     	= 96'h2A_24_2D_43_4B_44_34_00_00_00_00_00,
		TORONTO			= 96'h2C_44_2D_44_31_2C_44_00_00_00_00_00,
		DIGITAL 		= 96'h23_43_34_43_2C_1C_4B_00_00_00_00_00,
		SYSTEMS 		= 96'h1B_35_1B_2C_24_3A_1B_00_00_00_00_00,
		FLEMING 		= 96'h2B_4B_24_3A_43_31_34_00_00_00_00_00,
			//8
		MODELSIM 		= 96'h3A_44_23_24_4B_1B_43_3A_00_00_00_00,
		SANDFORD 		= 96'h1B_1C_31_23_2B_44_2D_23_00_00_00_00,
		KEYBOARD 		= 96'h42_24_35_32_44_1C_2D_23_00_00_00_00,
		COMPUTER		= 96'h21_44_3A_4D_3C_2C_24_2D_00_00_00_00,
		//9
		GAILBRAITH		= 96'h34_1C_4B_32_2D_1C_43_2C_33_00_00_00,
		//10
		MECHANICAL 		= 96'h3A_24_21_33_1C_31_43_21_1C_4B_00_00,
		UNIVERSITY  	= 96'h3C_31_43_2A_24_2D_1B_43_2C_35_00_00,
		ELECTRICAL  	= 96'h24_4B_24_21_2C_2D_43_21_1C_4B_00_00,
		//11
		FROSHLEEDUR 	= 96'h2B_2D_44_1B_33_4B_24_24_23_3C_2D_00,
		PROGRAMMING 	= 96'h4D_2D_44_34_2D_1C_3A_3A_43_31_34_00,
		ENGINEERING 	= 96'h24_31_34_43_31_24_24_2D_43_31_34_00,
		CONVOCATION 	= 96'h21_44_31_2A_44_21_1C_2C_43_44_31_00,
		//12
		X5CSEMA5F31C6 	= 96'h2E_21_1B_24_3A_1C_2E_2B_26_16_21_36;
		
	reg [3:0] address;

	always @(*) begin : state_table
		case (current_state)
			S_WAIT_START   : next_state = (enable_next_level) ? S_LOAD_NEXT : S_WAIT_START;
			S_LOAD_NEXT    : next_state = S_LOAD_WAIT;
			S_LOAD_WAIT    : next_state = (enable_next_level) ? S_GET_SEQUENCE : S_LOAD_WAIT;
			S_GET_SEQUENCE : next_state = S_LOAD_NEXT;
			default        : next_state = S_WAIT_START;
		endcase
	end

	always @(*) begin : enable_signals
		load_sequence = 1'd0;
		get_sequence  = 1'b0;
		case (current_state)
			S_GET_SEQUENCE : begin
				get_sequence = 1'b1;
			end
			S_LOAD_NEXT : begin
				load_sequence = 1'd1;
			end
		endcase // current_state
	end

		//reg first=0;
		always @(posedge clk)begin
			if (!resetn)
				address <= 0;
			else if (get_sequence == 1'b1 && resetn  )
				address <= address + 4'b1;
		end
  
	// current_state registers
	always@(posedge clk)
		begin : state_FFs
			if(!resetn)
				current_state <= S_WAIT_START;
			else
				current_state <= next_state;
		end // state_FFS
		
		always @(*) begin
			case(address)
				4'd0 : begin
					sequence_ = ECF;
					num_char  = 8'h03;
				end
				4'd1 : begin
					sequence_ = VGA;
					num_char  = 8'h03;
				end
				4'd2 : begin
					sequence_ = VHDL;
					num_char  = 8'h04;
				end
				4'd3 : begin
					sequence_ = BAHEN;
					num_char  = 8'h05;
				end
				4'd4 : begin
					sequence_ = X2TEGG;
					num_char  = 8'h05;
				end
				4'd5 : begin
					sequence_ = HELLO;
					num_char  = 8'h05;
				end
				4'd6 : begin
					sequence_ = WORLD;
					num_char  = 8'h05;
				end
				4'd7 : begin
					sequence_ = SKULE;
					num_char  = 8'h05;
				end
				4'd8 : begin
					sequence_ = DE1SOC;
					num_char  = 8'h06;
				end
				4'd9 : begin
					sequence_ = GODIVA;
					num_char  = 8'h06;
				end
				4'd10 : begin
					sequence_ = QUARTUS;
					num_char  = 8'h07;
				end
				4'd11 : begin
					sequence_ = PROJECT;
					num_char  = 8'h07;
				end
				4'd12 : begin
					sequence_ = VERILOG;
					num_char  = 8'h07;
				end
				4'd13 : begin
					sequence_ = TORONTO;
					num_char  = 8'h07;
				end
				4'd14 : begin
					sequence_ = DIGITAL;
					num_char  = 8'h07;
				end
				4'd15 : begin
					sequence_ = SYSTEMS;
					num_char  = 8'h07;
				end
				4'd16 : begin
					sequence_ = FLEMING;
					num_char  = 8'h07;
				end
				4'd17 : begin
					sequence_ = MODELSIM;
					num_char  = 8'h08;
				end
				4'd18 : begin
					sequence_ = SANDFORD;
					num_char  = 8'h08;
				end
				4'd19 : begin
					sequence_ = KEYBOARD;
					num_char  = 8'h08;
				end
				4'd20 : begin
					sequence_ = COMPUTER;
					num_char  = 8'h08;
				end
				4'd21 : begin
					sequence_ = GAILBRAITH;
					num_char  = 8'h09;
				end
				4'd22 : begin
					sequence_ = MECHANICAL;
					num_char  = 8'h0A;
				end
				4'd23 : begin
					sequence_ = UNIVERSITY;
					num_char  = 8'h0A;
				end
				4'd24 : begin
					sequence_ = ELECTRICAL;
					num_char  = 8'h0A;
				end
				4'd25 : begin
					sequence_ = FROSHLEEDUR;
					num_char  = 8'h0B;
				end
				4'd26 : begin
					sequence_ = PROGRAMMING;
					num_char  = 8'h0B;
				end
				4'd27 : begin
					sequence_ = ENGINEERING;
					num_char  = 8'h0B;
				end
				4'd28 : begin
					sequence_ = CONVOCATION;
					num_char  = 8'h0B;
				end
				4'd29 : begin
					sequence_ = X5CSEMA5F31C6;
					num_char  = 8'h0C;
				end
				default : begin
					sequence_ = ECF;
					num_char  = 8'h03;
				end
			endcase
		end

endmodule