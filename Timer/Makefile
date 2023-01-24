all: timer_impl_thread timer_impl_signal

timer_impl_thread:timer_impl_thread.c
	gcc -g -O0 timer_impl_thread.c -o timer_impl_thread 

timer_impl_signal:timer_impl_signal.c
	gcc -g -O0 timer_impl_signal.c -o timer_impl_signal

clean:
	rm timer_impl_thread timer_impl_signal
