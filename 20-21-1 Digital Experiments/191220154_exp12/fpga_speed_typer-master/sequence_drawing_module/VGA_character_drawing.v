module VGA_character_drawing (
	input        clk                     , // Clock
	input        resetn                  , // Asynchronous reset active low
	input  [7:0] address                 ,
	input        enable_character_plot   , // starts plot of character
	input  [8:0] x_input                 ,
	input  [8:0] y_input                 ,
	input        enable_clear            ,
	output [8:0] x                       ,
	output [8:0] y                       ,
	output [5:0] colour                  ,
	output       ready_to_start_character, // plot of character is done
	output       writeEn
	//output [2:0] char_current_state
);
	wire        enable_clear_pixels ;
	wire        enable_start        ;
	wire        enable_counter      ;
	wire [ 4:0] counter             ;
	wire [15:0] clear_counter       ;
	wire        ld_black            ;
	wire        ready_to_draw       ;
	wire        ld_block            ;
	wire        reset_counter       ;
	wire        enable_clear_counter;

	control_draw i_control_draw (
		.clk                 (clk                 ),
		.resetn              (resetn              ),
		.enable_start        (enable_start        ),
		.enable_clear        (enable_clear_pixels ),
		.counter             (counter             ),
		.clear_counter       (clear_counter       ),
		.ld_black            (ld_black            ),
		.ready_to_draw       (ready_to_draw       ),
		.ld_block            (ld_block            ),
		.writeEn             (writeEn             ),
		.enable_counter      (enable_counter      ),
		.reset_counter       (reset_counter       ),
		.enable_clear_counter(enable_clear_counter)
	);

	wire [5:0] colour_input     ;
	wire [5:0] colour_out       ;
	wire [8:0] x_input_from_char;
	wire [8:0] y_input_from_char;
	assign colour_input = colour_out;

	datapath_draw i_datapath_draw (
		.clk                 (clk                 ),
		.resetn              (resetn              ),
		.colour_input        (colour_input        ),
		.y_input             (y_input_from_char   ),
		.x_input             (x_input_from_char   ),
		.ld_block            (ld_block            ),
		.ld_black            (ld_black            ),
		.enable_counter      (enable_counter      ),
		.reset_counter       (reset_counter       ),
		.enable_clear_counter(enable_clear_counter),
		.clear_counter       (clear_counter       ),
		.counter             (counter             ),
		.x                   (x                   ),
		.y                   (y                   ),
		.colour              (colour              )
	);

	wire       ld_colour              ;
	wire       ld_value               ;
	wire       next_colour            ;
	wire [5:0] counter_character      ;
	wire       enable_counter_sequence;
	wire       reset_counter_sequence ;

	control_sequence i_control_sequence (
		.clk                     (clk                     ),
		.rst_n                   (resetn                  ),
		.ready_to_draw           (ready_to_draw           ),
		.counter                 (counter_character       ), // TODO: Check connection ! Signal/port not matching : Expecting logic [5:0]  -- Found logic [4:0]
		.ld_colour               (ld_colour               ),
		.enable_character_plot   (enable_character_plot   ),
		.enable_counter          (enable_counter_sequence ),
		.reset_counter           (reset_counter_sequence  ),
		.enable_start            (enable_start            ),
		.enable_clear            (enable_clear            ),
		.enable_clear_pixels     (enable_clear_pixels     ),
		.ld_value                (ld_value                ),
		.next_colour             (next_colour             ),
		.ready_to_start_character(ready_to_start_character)
		//.current_state           (char_current_state      )
	);

	datapath_sequence i_datapath_sequence (
		.clk           (clk                    ),
		.rst_n         (resetn                 ),
		.address       (address                ),
		.x_input       (x_input                ),
		.y_input       (y_input                ),
		.ld_colour     (ld_colour              ),
		.next_colour   (next_colour            ),
		.ld_value      (ld_value               ),
		.reset_counter (reset_counter_sequence ),
		.enable_counter(enable_counter_sequence),
		.x             (x_input_from_char      ),
		.y             (y_input_from_char      ),
		.counter       (counter_character      ),
		.colour_out    (colour_out             )
	);

endmodule