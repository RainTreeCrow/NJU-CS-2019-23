module VGA_score (
    input            clk                  , // Clock
    input            resetn               , // Asynchronous reset active low
    input            enable_plot_scorebar ,
    // input  [8:0] x_input , //not needed due to a constant intial x and y
    //input  [8:0] y_input  ,
    input            enable_clear_scorebar,
    output  [8:0] x                    ,
    output  [8:0] y                    ,
    output  [5:0] colour               ,
    output ready_to_plot_scorebar,
    output        writeEn
    );

    wire [ 9:0] counter             ;
    wire [15:0] clear_counter       ;
    wire        ld_white            ;
    wire        ready_to_draw       ;
    wire        ld_block            ;
    wire        enable_counter      ;
    wire        reset_counter       ;
    wire        enable_clear_counter;
    wire        score_increased     ;
    wire [ 5:0] colour_input        ;
    wire [ 8:0] y_input             ;
    wire [ 8:0] x_input             ;
    wire done_white;

    assign ready_to_plot_scorebar = ready_to_draw;
    assign x_input      = 9'd10;
    assign y_input      = 9'd44;
    assign colour_input = 6'b001001;

control_draw i_control_draw (
    .clk                 (clk                  ),
    .resetn              (resetn               ),
    .enable_start        (enable_plot_scorebar ),
    .enable_clear        (enable_clear_scorebar),
    .counter             (counter              ),
    .clear_counter       (clear_counter        ),
    .ld_white            (ld_white             ),
    .ready_to_draw       (ready_to_draw        ),
    .ld_block            (ld_block             ),
    .done_white          (done_white           ),
    .score_increased     (score_increased      ),
    .writeEn             (writeEn              ),
    .enable_counter      (enable_counter       ),
    .reset_counter       (reset_counter        ),
    .enable_clear_counter(enable_clear_counter )
);


datapath_draw i_datapath_draw (
    .clk                 (clk                 ),
    .resetn              (resetn              ),
    .colour_input        (colour_input        ),
    .y_input             (y_input             ),
    .x_input             (x_input             ),
    .ld_block            (ld_block            ),
    .ld_white            (ld_white            ),
    .score_increased     (score_increased     ),
    .done_white          (done_white          ),
    .enable_counter      (enable_counter      ),
    .reset_counter       (reset_counter       ),
    .enable_clear_counter(enable_clear_counter),
    .clear_counter       (clear_counter       ),
    .counter             (counter             ),
    .x                   (x                   ),
    .y                   (y                   ),
    .colour              (colour              )
);


endmodule // VGA_score_drawing

//001001 green bar  
//00b567

//x: 10
//y:44


module control_draw (
    input             clk                 ,
    input             resetn              ,
    input             enable_start        ,
    input             enable_clear        ,
    input      [ 9:0] counter             ,
    input      [15:0] clear_counter       ,
    output reg        ld_white            ,
    output reg score_increased,
    output reg done_white,
    output reg        ready_to_draw       ,
    output reg        ld_block            ,
    output reg        writeEn             ,
    output reg        enable_counter      ,
    output reg        reset_counter       ,
    output reg        enable_clear_counter
);

    reg [4:0] current_state, next_state;
    wire q;
    reg countdown_enable;
    localparam
    S_WAIT_START = 5'd0,
    S_LOAD_VALUES = 5'd1,
    S_LOAD_WHITE = 5'd2,
    S_DRAW_WHITE = 5'd3,
    S_DRAW_BLOCK = 5'd4,
    S_INCREASE_SCORE = 5'd5,
    S_DONE_WHITE = 5'd6,
    S_WAIT_ENABLE = 5'd7;

    // Next state logic aka our state table
    always@(*)
        begin : state_table
            case (current_state)
                S_WAIT_START :
                    begin
                        if (enable_start)
                            next_state = S_LOAD_VALUES;
                        else if (enable_clear)
                            next_state = S_LOAD_WHITE;
                        else
                            next_state = S_WAIT_START;
                    end
                S_LOAD_VALUES : next_state = S_DRAW_BLOCK;
                S_LOAD_WHITE  : next_state = S_DRAW_WHITE;
                S_DRAW_WHITE  : next_state = (clear_counter[15:9] >= 4) ? S_DONE_WHITE : S_DRAW_WHITE;
                S_DRAW_BLOCK  : next_state = (counter[9:5] == 10) ? S_INCREASE_SCORE : S_WAIT_ENABLE;
                S_WAIT_ENABLE : next_state = (q) ? S_DRAW_BLOCK : S_WAIT_ENABLE;
                S_INCREASE_SCORE : next_state = S_WAIT_START;
                S_DONE_WHITE : next_state = S_WAIT_START;
                default       : next_state = S_WAIT_START;
            endcase
        end // state_table

    // Output logic aka all of our datapath control signals
    always @(*)
        begin : enable_signals
            // By default make all our signals 0
            ld_white             = 1'b0;
            ld_block             = 1'b0;
            writeEn              = 1'b0;
            enable_counter       = 1'b0;
            reset_counter        = 1'b0;
            enable_clear_counter = 1'b0;
            ready_to_draw        = 1'b0;
            score_increased = 1'b0;
            done_white = 1'b0;
            countdown_enable = 1'b0;
            case (current_state)
                S_WAIT_START : begin
                    ready_to_draw = 1'b1;
                    reset_counter = 1'b1;
                end
                S_LOAD_VALUES : begin
                    ld_block = 1'b1;
                end
                S_LOAD_WHITE : begin
                    ld_white = 1'b1;
                end
                S_DRAW_WHITE : begin
                    writeEn            = 1'b1;
                    ld_white             = 1'b1;
                    enable_clear_counter = 1'b1;
                end
                S_DRAW_BLOCK : begin
                    writeEn        = 1'b1;
                    enable_counter = 1'b1;
                end
                S_WAIT_ENABLE : begin
                    countdown_enable = 1'b1;
                end
                S_INCREASE_SCORE : begin
                    score_increased = 1'd1;
                end
                S_DONE_WHITE : begin
                    done_white = 1'b1;
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
            .resetn          (resetn          ),
            .clock           (clk             ),
            .q               (q               ),
            .countdown_enable(countdown_enable)
        );

endmodule



module datapath_draw (
    input             clk                 ,
    input             resetn              ,
    input      [ 5:0] colour_input        ,
    input      [ 8:0] y_input             ,
    input      [ 8:0] x_input             ,
    input             ld_block            ,
    input             ld_white            ,
    input             enable_counter      ,
    input             reset_counter       ,
    input             enable_clear_counter,
    input done_white,
    input score_increased,
    output reg [15:0] clear_counter       ,//
    output reg [ 9:0] counter             ,
    output reg [ 8:0] x                   ,
    output reg [ 8:0] y                   ,
    output reg [ 5:0] colour
);

    reg [8:0] x_start;
    reg [8:0] y_start;
    reg [5:0]colour_buffer;

    // input registers


    // Registers x, y, colour with respective input logic
    always@(posedge clk) begin
        if(!resetn || done_white) begin
            x      <= 9'd10;
            y      <= 9'd44;
            x_start <= 9'd10;
            y_start <= 9'd44;
            colour <= 6'b11_11_11;
            counter       <= 0;
            clear_counter <= 16'b0;
        end
        else begin
            //resetting the counters for plotting
            if(reset_counter) begin
                y_start <= 9'd44;
                counter       <= 0;
                clear_counter <= 16'b0;
            end
            else if (score_increased && x_start<300) begin
                    x_start <= x_start+10;
                end
            //load the specified coordinate and colour
            if(ld_block) begin
                x <= x_start;
                y <= y_start;
                colour_buffer  <= 6'b00_10_01;
            end
            //change lower half to black
            if(ld_white) begin
                x       <= 9'd10;
                y       <= 9'd44;
                //change x_start to 105 to take up the bottom 35 pixels
                x_start <= 9'd10;
                y_start <= 9'd44;
                //black
                colour_buffer  <= 6'b11_11_11;
                colour  <= 6'b11_11_11;
            end
            //incrementing the counter for drawing a square
            if(enable_counter) begin
                if(counter[4:0] >= 4) begin
                    counter[9:5] <= counter[9:5] + 1;
                    counter[4:0] <= 0;
                end
                else begin
                    counter <= counter + 1;
                end
                x       <= x_start + counter[9:5];
                y       <= y_start + counter[4:0];
                colour   <= colour_buffer;
            end
            //incrementing the counter for clearing bar
            if(enable_clear_counter) begin
                if(clear_counter[8:0] >= 300) begin
                    clear_counter[15:9] <= clear_counter[15:9] + 1;
                    clear_counter[8:0] <= 0;
                end
                else begin
                    clear_counter <= clear_counter + 1;
                end 
                x             <= x_start + clear_counter[8:0];
                y             <= y_start + clear_counter[15:9];
                colour   <= colour_buffer;
            end
        end
    end // always@(posedge clk)
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
            counter <= 28'd20000;
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