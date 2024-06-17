
//=======================================================
//  This code is generated by Terasic System Builder
//=======================================================

module exp10(

	//////////// CLOCK //////////
	input 		          		CLOCK2_50,
	input 		          		CLOCK3_50,
	input 		          		CLOCK4_50,
	input 		          		CLOCK_50,

	//////////// KEY //////////
	input 		     [3:0]		KEY,

	//////////// SW //////////
	input 		     [9:0]		SW,

	//////////// LED //////////
	output		     [9:0]		LEDR,

	//////////// Audio //////////
	input 		          		AUD_ADCDAT,
	inout 		          		AUD_ADCLRCK,
	inout 		          		AUD_BCLK,
	output		          		AUD_DACDAT,
	inout 		          		AUD_DACLRCK,
	output		          		AUD_XCK,

	//////////// PS2 //////////
	inout 		          		PS2_CLK,
	inout 		          		PS2_CLK2,
	inout 		          		PS2_DAT,
	inout 		          		PS2_DAT2,

	//////////// ADC //////////
	output		          		ADC_CONVST,
	output		          		ADC_DIN,
	input 		          		ADC_DOUT,
	output		          		ADC_SCLK,

	//////////// I2C for Audio and Video-In //////////
	output		          		FPGA_I2C_SCLK,
	inout 		          		FPGA_I2C_SDAT
);



//=======================================================
//  REG/WIRE declarations
//=======================================================

wire clk_i2c;
wire reset,en;
wire [15:0] audiodata;
wire [15:0] freq_out;
wire [15:0] freq;
wire [8:0] volumn;

//=======================================================
//  Structural coding
//=======================================================

assign reset = ~KEY[0];
assign LEDR[8:0] = volumn[8:0];
assign freq = freq_out & {16{en}};

audio_clk u1(CLOCK_50,reset,AUD_XCK,LEDR[9]);
key2note key(CLOCK_50,SW[0],en,freq_out,PS2_CLK,PS2_DAT,volumn);

//I2C part
clkgen #(10000) my_i2c_clk(CLOCK_50,reset,1'b1,clk_i2c);  //10k I2C clock  
I2C_Audio_Config myconfig(clk_i2c,KEY[0],FPGA_I2C_SCLK,FPGA_I2C_SDAT,volumn);
I2S_Audio myaudio(AUD_XCK,KEY[0],AUD_BCLK,AUD_DACDAT,AUD_DACLRCK,audiodata);
Sin_Generator sin_wave(AUD_DACLRCK,KEY[0],freq,audiodata);//

endmodule
