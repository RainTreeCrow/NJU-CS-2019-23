vlib work
vlog VGA_score.v
vsim VGA_score
log {/*}
add wave {/*}



force {clk} 0 0ns, 1 {5ns} -r 10ns

force {enable_plot_scorebar} 0
force {resetn} 0
run 10ns

force {resetn} 1
run 10ns

force {enable_clear_scorebar} 1
run 10ns

force {enable_clear_scorebar} 0
run 100ns

force {enable_plot_scorebar} 1
run 10ns

force {enable_plot_scorebar} 0
run 1000000ns

force {enable_plot_scorebar} 1
run 10ns


force {enable_plot_scorebar} 0
run 1000ns

force {enable_plot_scorebar} 1
run 10ns

force {enable_plot_scorebar} 0
run 1000ns

