module trigger(clk,clr1,clr2,d1,d2,q1,q2);
	input clk;
	input clr1,clr2;
	input d1,d2;
	output q1;
	output q2;
	myasynchro m1(clk,clr1,d1,q1);
	mysynchro m2(clk,clr2,d2,q2);
endmodule
