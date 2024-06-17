
//starts plotting based on a input (enable_start)
//when ready to plot sends a (ready_to_draw)
//will auto load the values for x, y, colour

//plots a 4x4 square
//sends (writeEn) to plot on VGA
module control_draw (
    input             clk                 ,
    input             resetn              ,
    input             enable_start        ,
    input             enable_clear        ,
    input      [ 4:0] counter             ,
    input      [15:0] clear_counter       ,
    output reg        ld_black            ,
    output reg        ready_to_draw       ,
    output reg        ld_block            ,
    output reg        writeEn             ,
    output reg        enable_counter      ,
    output reg        reset_counter       ,
    output reg        enable_clear_counter
);

    reg [4:0] current_state, next_state;
    reg countdown_enable;
    wire q;

    localparam
        S_WAIT_START = 5'd0,
            S_LOAD_VALUES = 5'd1,
                S_LOAD_BLACK = 5'd2,
                    S_DRAW_BLACK = 5'd3,
                        S_DRAW_BLOCK = 5'd4,
                        S_WAIT_ENABLE = 5'd5;

    // Next state logic aka our state table
    always@(*)
        begin : state_table
            case (current_state)
                S_WAIT_START :
                    begin
                        if (enable_start)
                            next_state = S_LOAD_VALUES;
                        else if (enable_clear)
                            next_state = S_LOAD_BLACK;
                        else
                            next_state = S_WAIT_START;
                    end
                S_LOAD_VALUES : next_state = S_DRAW_BLOCK;
                S_LOAD_BLACK  : next_state = S_DRAW_BLACK;
                S_WAIT_ENABLE : next_state = (q) ? S_DRAW_BLOCK : S_WAIT_ENABLE;
                S_DRAW_BLACK  : next_state = (clear_counter[15:9] >= 66) ? S_WAIT_START : S_DRAW_BLACK;
                S_DRAW_BLOCK  : next_state = (counter == 5'b10000) ? S_WAIT_START : S_WAIT_ENABLE;
                default       : next_state = S_WAIT_START;
            endcase
        end // state_table

    // Output logic aka all of our datapath control signals
    always @(*)
        begin : enable_signals
            // By default make all our signals 0
            ld_black             = 1'b0;
            ld_block             = 1'b0;
            writeEn              = 1'b0;
            enable_counter       = 1'b0;
            reset_counter        = 1'b0;
            enable_clear_counter = 1'b0;
            ready_to_draw        = 1'b0;
            countdown_enable = 1'b0;
            case (current_state)
                S_WAIT_START : begin
                    ready_to_draw = 1'b1;
                    reset_counter = 1'b1;
                end
                S_LOAD_VALUES : begin
                    ld_block = 1'b1;
                end
                S_WAIT_ENABLE : begin
                    countdown_enable = 1'b1;
                end
                S_LOAD_BLACK : begin
                    ld_black = 1'b1;
                end
                S_DRAW_BLACK : begin
                    writeEn              = 1'b1;
                    ld_black             = 1'b1;
                    enable_clear_counter = 1'b1;
                end
                S_DRAW_BLOCK : begin
                    writeEn        = 1'b1;
                    enable_counter = 1'b1;
                end
                // default:    // don't need default since we already made sure all of our outputs were assigned a value at the start of the always block
            endcase
        end // enable_signals

    // current_state registers
    always@(posedge clk)
        begin : state_FFs
            if(!resetn)
                current_state <= S_WAIT_START;
            else
                current_state <= next_state;
        end // state_FFS

RateDivider i_RateDivider (
    .resetn(resetn),
    .clock(clk), 
    .q(q),
    .countdown_enable(countdown_enable) 
    );

endmodule

module RateDivider(resetn,clock,q,countdown_enable);
input resetn;
input clock;
input countdown_enable;
output reg q;
reg [27:0]counter;
    always @ (posedge clock)
    begin
        if (!resetn) begin
            counter <= 28'd125000;
            q <= 0;
        end
        else if (!counter)
            begin
                counter <= 28'd20000;
                q <= 1; 
            end
        else if (q)
            q <= 0;
        else if (countdown_enable)
            counter <= counter-1;
    end
endmodule




