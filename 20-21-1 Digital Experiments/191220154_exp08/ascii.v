module ascii(scancode,caps,ascii);

	input [7:0] scancode;
	input caps;
	output reg [7:0] ascii;
	reg [7:0] code [255:0];

	initial begin
		$readmemh("code2ascii.txt", code, 0, 255); 
	end

	always @ (*) begin
		if (caps && (code[scancode] >= 97 && code[scancode] <= 122))
			ascii <= code[scancode] - 32;
		else ascii <= code[scancode];
	end
	
endmodule
