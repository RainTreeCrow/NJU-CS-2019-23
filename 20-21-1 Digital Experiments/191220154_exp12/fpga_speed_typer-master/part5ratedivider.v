module part2(SW,CLOCK_50,HEX0);
input CLOCK_50;
input [9:0]SW;
output [6:0]HEX0;

wire enable;
wire [3:0]counterout;

	selector s0(
		.switch(SW[1:0]),
		//.switch(2),
		.clock(CLOCK_50),
		.enable(enable)
		);
	counter4bit c0(
		.enable(enable),
		.q(counterout)
		);
	hexDisplay h0(
		.c(counterout),
		.led(HEX0)
		);
endmodule

module counter4bit(enable,q);
	input enable;
	output reg [3:0]q=0;
	always @(posedge enable)
	begin
		if(q==15)
			q <= 0;
		else
			q <= q+1;
	end
endmodule

module selector(switch,clock,enable);
	input [1:0]switch;
	input clock;
	wire [2:0]q;
	output reg enable;

		RateDivider r3(
			.clock(clock),
			.d(200000000),
			.q(q[2])
			);

		RateDivider r2(
			.clock(clock),
			.d(100000000),
			.q(q[1])
			);

		RateDivider r1(
			.clock(clock),
			.d(50000000),
			.q(q[0])
			);

	always @(*)
		case(switch)
		1:
		enable = q[0];
		2:
		enable = q[1];
		3:
		enable = q[2];
		default:
		enable = clock;
		endcase
endmodule


module RateDivider(clock,d,q);
input clock;
input [27:0]d;
output reg q;
reg [27:0]counter=0;
	always @ (posedge clock)
	begin
		if (!counter)
			begin
				counter <= d-1;
				q <= 1; 
			end
		else if (q)
			q <= 0;
		else
			counter <= counter-1;
	end
endmodule

module hexDisplay(input[3:0]c,output[6:0]led);
	//logicexpressionforsegment6
	assign led[6]=((~c[0]&~c[1]&~c[2]&~c[3])|(~c[0]&~c[1]&~c[2]&c[3])
		|(~c[0]&c[1]&c[2]&c[3])|(c[0]&c[1]&~c[2]&~c[3]));
	//logicexpressionforsegment5
	assign led[5]=((~c[0]&~c[1]&~c[2]&c[3])|(~c[0]&~c[1]&c[2]&~c[3])|(~c[0]&~c[1]&c[2]&c[3])
		|(~c[0]&c[1]&c[2]&c[3])|(c[0]&c[1]&~c[2]&c[3]));
	//logicexpressionforsegment4
	assign led[4]=((~c[0]&~c[1]&~c[2]&c[3])|(~c[0]&~c[1]&c[2]&c[3])|(~c[0]&c[1]&~c[2]&~c[3])
		|(~c[0]&c[1]&~c[2]&c[3])|(~c[0]&c[1]&c[2]&c[3])|(c[0]&~c[1]&~c[2]&c[3]));
	//logicexpressionforsegment3
	assign led[3]=((~c[0]&~c[1]&~c[2]&c[3])|(~c[0]&c[1]&~c[2]&~c[3])|(~c[0]&c[1]&c[2]&c[3])
		|(c[0]&~c[1]&~c[2]&c[3])|(c[0]&~c[1]&c[2]&~c[3])|(c[0]&c[1]&c[2]&c[3]));
	//logicexpressionforsegment2
	assign led[2]=((~c[0]&~c[1]&c[2]&~c[3])|(c[0]&c[1]&~c[2]&~c[3])|(c[0]&c[1]&c[2]&~c[3])
		|(c[0]&c[1]&c[2]&c[3]));
	//logicexpressionforsegment1
	assign led[1]=((~c[0]&c[1]&~c[2]&c[3])|(~c[0]&c[1]&c[2]&~c[3])|(c[0]&~c[1]&c[2]&c[3])
		|(c[0]&c[1]&~c[2]&~c[3])|(c[0]&c[1]&c[2]&~c[3])|(c[0]&c[1]&c[2]&c[3]));
	//logicexpressionforsegment0
	assign led[0]=((~c[0]&~c[1]&~c[2]&c[3])|(~c[0]&c[1]&~c[2]&~c[3])|(c[0]&~c[1]&c[2]&c[3])
		|(c[0]&c[1]&~c[2]&c[3]));
endmodule