module exp5_2(clk,set,clk_alr,h_m,en_alr,sel_timer,en_timer,clr_timer,set_sig,
	hex0,hex1,hex2,hex3,hex4,hex5,alarm);

	input clk;
	input set,clk_alr,h_m,en_alr;
	input sel_timer,en_timer,clr_timer;
	input set_sig;
	
	wire cs,cns;
	wire [7:0] hour [3:0];
	wire [7:0] min [3:0];
	wire [7:0] sec [3:0];
	
	output [6:0] hex0;
	output [6:0] hex1;
	output [6:0] hex2;
	output [6:0] hex3;
	output [6:0] hex4;
	output [6:0] hex5;
	output alarm;

	clk_1s clk1(clk,cs);
	clk_1ns clk2(clk,cns);
	
	set s_alr(set && clk_alr,set_sig,h_m,hour[2],min[2],sec[2]);
	set s_clk(set && !clk_alr,set_sig,h_m,hour[1],min[1],sec[1]);
	clock c(cs,set && !clk_alr,en_alr,hour[1],min[1],sec[1],hour[2],min[2],
		hour[0],min[0],sec[0],alarm);
	timer tim(cns,en_timer,clr_timer,hour[3],min[3],sec[3]);
	
	hex h0(sec[set + set * clk_alr + sel_timer * 3] % 10,hex0);
	hex h1(sec[set + set * clk_alr + sel_timer * 3] / 10,hex1);
	hex h2(min[set + set * clk_alr + sel_timer * 3] % 10,hex2);
	hex h3(min[set + set * clk_alr + sel_timer * 3] / 10,hex3);
	hex h4(hour[set + set * clk_alr + sel_timer * 3] % 10,hex4);
	hex h5(hour[set + set * clk_alr + sel_timer * 3] / 10,hex5);
	
endmodule
