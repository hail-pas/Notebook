mandelbrot: mandelbrot.c
	gcc -ggdb -Wall -O2 -fopenmp $< -o $@ -lm

all:
	@echo 'go run FILE'


# cuda
a.out: mandelbrot.cu
	nvcc -g -O2 $< -o $@
	cuobjdump --dump-ptx a.out > mandelbrot.ptx

run:
	nvprof ./a.out