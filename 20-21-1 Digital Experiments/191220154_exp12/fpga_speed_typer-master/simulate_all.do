vlib work

vlog Keyboard_Reader.v
vlog Keyboard_Parser_Modifier.v
vlog timer_3s.v
vlog ./sequence_drawing_module/VGA_sequence_drawing.v
	vlog  ./sequence_drawing_module/VGA_character_drawing.v
	vlog  ./sequence_drawing_module/datapath_sequence.v
	vlog  ./sequence_drawing_module/control_sequence.v
	vlog  ./sequence_drawing_module/control_draw.v
	vlog  ./sequence_drawing_module/datapath_draw.v

vsim Keyboard_Reader
log {/*}
add wave {/*}

force {CLOCK_50} 0 0ns, 1 {5ns} -r 10ns

force {ps2_key_pressed} 0
force {ps2_key_data} 16#1e
force {KEY[0]} 0
run 10ns

force {KEY[0]} 1
run 410ns

#press the 1 key
force {ps2_key_pressed} 1
force {ps2_key_data} 16#1e
run 20ns

force {ps2_key_pressed} 0
run 10ns

force {ps2_key_pressed} 0
force {ps2_key_data} 16#1e
run 100ns

force {ps2_key_pressed} 1
force {ps2_key_data} 16#5a
run 20ns

force {ps2_key_pressed} 0
run 50000ns

force {ps2_key_pressed} 1
force {ps2_key_data} 16#24
run 30ns

force {ps2_key_pressed} 1
force {ps2_key_data} 16#21
run 50ns

force {ps2_key_pressed} 1
force {ps2_key_data} 16#2b
run 50ns

force {ps2_key_pressed} 0
run 1000ns

force {ps2_key_pressed} 1
force {ps2_key_data} 16#5a
run 20ns

force {ps2_key_pressed} 0
force {ps2_key_data} 16#5a
run 50000ns

force {ps2_key_pressed} 1
force {ps2_key_data} 16#2a
run 30ns

force {ps2_key_pressed} 1
force {ps2_key_data} 16#34
run 50ns

force {ps2_key_pressed} 1
force {ps2_key_data} 16#1c
run 50ns

force {ps2_key_pressed} 0
run 1000ns

force {ps2_key_pressed} 1
force {ps2_key_data} 16#5a
run 1000ns






