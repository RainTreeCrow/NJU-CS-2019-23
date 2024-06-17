vlib work
vlog VGA_character_drawing.v
vlog control_draw.v
vlog datapath_draw.v
vlog control_sequence.v
vlog datapath_sequence.v
vsim VGA_character_drawing
log {/*}
add wave {/*}

force {clk} 0 0ns, 1 {5ns} -r 10ns
force {address} 16#21
force {x_input} 000000100
force {y_input} 000000100
force {enable_clear} 0

force {resetn} 0
force {enable_character_plot} 0
run 10ns

force {resetn} 1
force {enable_character_plot} 1
run 10ns

force {enable_character_plot} 0
run 10000ns

