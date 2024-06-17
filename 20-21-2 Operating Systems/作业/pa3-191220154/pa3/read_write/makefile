all:read_write
read_write:
	gcc -o rw_lock rw_lock.c -pthread
	gcc -o rw_signal rw_signal.c -pthread
clean:
	rm -f rw_lock
	rm -f rw_signal
