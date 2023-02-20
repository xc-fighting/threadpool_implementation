test_prog: main.o thread_pool.o
	gcc -o test_prog main.o thread_pool.o shm.o

thread_pool.o: thread_pool.c thread_pool.h
	gcc -c -o thread_pool.o thread_pool.c -lpthread

shm.o: shm.c shm.h
	gcc -c -o shm.o shm.c

main.o: main.c thread_pool.h
	gcc -c -o main.o main.c

clean:
	rm main.o thread_pool.o test_prog 