module mysynchro(clk,clr,d,q);
	input clk;
	input clr;
	input d;
	output reg q;
	
always @ (posedge clk)
	if (clr==1) q <= 0;
	else q <= d;
endmodule
