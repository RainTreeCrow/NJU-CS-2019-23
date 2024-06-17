module shift_register(clk,lin,s,d,q);
	input clk,lin;
	input [2:0] s;
	input [7:0] d;
	output reg [7:0] q = 8'b00000001;
	
always @ (posedge clk)
	case(s)
		0: q <= 0;
		1: q <= d;
		2: q <= {1'b0, q[7:1]};
		3: q <= {q[6:0], 1'b0};
		4: q <= {q[7], q[7:1]};
		5: q <= {lin, q[7:1]};
		6: q <= {q[0], q[7:1]};
		7: q <= {q[6:0], q[7]};
		default: q <= 8'bx;
	endcase
endmodule
