module ram_1(clk,we,inaddr,outaddr,din,dout);
	input clk;
	input we;
	input [2:0] inaddr;
	input [2:0] outaddr;
	input [2:0] din;
	output reg [7:0] dout;
	
	reg [7:0] ram [15:0];
	reg [7:0] temp;
	reg flag = 0;

	initial begin
		$readmemh("D:/workspace/exp7_2/mem1.txt",ram,0,15);
	end

	always @(posedge clk) begin
		if (we) begin
			ram[inaddr][2:0] <= din;
			ram[inaddr][7:3] <= 6'b000000;
		end
		if (flag) begin
			dout <= temp;
			flag = 0;
		end
		else begin
			temp <= ram[outaddr];
			flag = 1;
		end
	end
endmodule
