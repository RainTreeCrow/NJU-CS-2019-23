module Snake(
	clk,
	clrn,
	ps2_clk,
	ps2_data,
	LED
);

	input clk;
	input clrn;
	input ps2_clk;
	input ps2_data;
	
	output wire [3:0] LED;
	
	wire off;	
	wire ready;
	wire overflow;
	wire nextdata_n;
	wire [7:0] data;
	
	get_keyboard my_get_keyboard(	
						.clk(clk),
						.clrn(clrn),
						.ps2_clk(ps2_clk),
						.ps2_data(ps2_data),
						.data(data),
						.ready(ready),
						.nextdata_n(nextdata_n),
						.overflow(overflow)
	);
	
	kbd_output my_kbd_output(
						.clk(clk),
						.ready(ready),
						.overflow(overflow),
						.data(data),
						.direction(LED[1:0]),
						.nextdata_n(nextdata_n),
						.run(LED[2]),
						.restart(LED[3])
	);
	
endmodule