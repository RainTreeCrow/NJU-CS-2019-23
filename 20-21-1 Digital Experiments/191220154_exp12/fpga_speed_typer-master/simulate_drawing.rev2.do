vlib work
vlog VGA_sequence_drawing.v
vlog VGA_character_drawing.v
vlog control_draw.v
vlog datapath_draw.v
vlog control_sequence.v
vlog datapath_sequence.v
vsim VGA_sequence_drawing
log {/*}
add wave {/*}

force {clk} 0 0ns, 1 {5ns} -r 10ns
force {num_char} 16#3
force {sequence_} 16#11111111111111111
force {x_start} 000000100
force {y_start} 000000100
force {enable_clear} 0

force {resetn} 0
force {plot_sequence} 0
run 10ns

force {resetn} 1
force {plot_sequence} 1
run 10ns

force {plot_sequence} 0
run 10000ns

